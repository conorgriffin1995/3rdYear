function Build-SandcastleDocs() {
     <#
    .SYNOPSIS
    Builds Sandcastle documentation (html and .chm) using centrally-managed templates.

    .DESCRIPTION
    Builds Sandcastle documentation (HTML and .chm) using centrally-managed templates, and (within a CI context) zips up generated site.  For developers, also allows the generated HTML website to be previewed.

    Requires the following settings in artifact.yml:

    sandcastle_docs:
        - projectname.csproj/vbproj

    Building and previewing the documentation locally requires installation of Sandcastle Help File Builder.
    https://github.com/EWSoftware/SHFB/releases


    .PARAMETER WorkingDirectory
    The root directory for the repo.  Defaults to the current directory.


    .PARAMETER TemplateDirectory
    The directory where the Sandcastle template resides (.\ReleaseEngineering\BuildScripts\Sandcastle)

    .PARAMETER CI
    Switch indicating whether running within a CI context; developers should typically NOT set this flag.


    .PARAMETER ProjectRepository
    Required only if running in a CI context, specifies the project repository being built, from which a zip file is created.  Developers should typically ignore this setting.

    .EXAMPLE
    PS C:\> Build-SandcastleDocs -ProjectRepository MyCoolRepo

    #>
    [CmdletBinding()]
    param(
        [Parameter(Mandatory=$false)]
        [string]$WorkingDirectory,
        [Parameter(Mandatory=$false)]
        [string]$TemplateDirectory,
        [Parameter(Mandatory=$false)]
        [string]$ProjectRepository
    )
    
    if(!$WorkingDirectory){
        $WorkingDirectory=Convert-Path .
    }

    if(!$TemplateDirectory) {
        $TemplateDirectory = resolve-path "$PSScriptRoot\..\..\..\Sandcastle"
    }
    Write-Output ""
    Write-Verbose "STEP 1 Copying Sandcastle Template"
    Write-Output ""

    Write-Output " WorkingDirectory  :   $WorkingDirectory"
    Write-Output " TemplateDirectory :   $TemplateDirectory"
    Write-Output " CI                :   $CI"
    Write-Output ""

    Copy-SandcastleTemplate -WorkingDirectory $WorkingDirectory `
                            -TemplateDirectory $TemplateDirectory

    Write-Output ""
    Write-Verbose "STEP 2 Add Documentation Source to .shfbproj"
    Write-Output ""

    Add-DocSource -WorkingDirectory $WorkingDirectory
    
    Write-Output ""
    Write-Verbose "STEP 3 Build Sandcastle Solution"
    Write-Output ""

    pushd Sandcastle
    $solution = Get-Solution

    $msBuildArgs = @("$solution",
                        '/m',
                        '/p:GenerateDocumentation=false',
                        '/nr:false',
                        '/p:DebugType=pdbonly',
                        "/p:Platform=Any CPU",
                        "/p:configuration=Release",
                        "/verbosity:normal")


    Write-Output "---"
    Write-Output " Compiling `| Sandcastle Solution `| $solution"
    Write-Output "---"

    Write-Output "Executing : $MSBuildExe $msBuildArgs"
    & $MSBuildExe $msBuildArgs

    if(!$?) {
           throw "Build Failed!"
    }
    
    #
    # packaging
    #
    Rename-Item .\Help "Sandcastle"
    mkdir $ProjectRepository
    Move-Item Sandcastle $ProjectRepository
    Zip-Dir -Directory .\$ProjectRepository  -ZipFile "$ProjectRepository.docs.zip"
    cp "$ProjectRepository.docs.zip" ..
    
    popd
}

# Copy over Sandcastle template to $WorkingDirectory
function Copy-SandcastleTemplate(){
    [CmdletBinding()]
    param(
        [Parameter(Mandatory=$true)]
        [string]$WorkingDirectory,
        [Parameter(Mandatory=$true)]
        [string]$TemplateDirectory
    )

    Write-Output "Copying Template to:"
    mkdir Sandcastle

    # Copy over all files
    $from = $TemplateDirectory
    $to = $WorkingDirectory
    Get-ChildItem -Path $from | Copy-Item -Destination "$to\Sandcastle" -Recurse

}

# Add XML <DocumentationSource> for each project in solution to the Sandcastle project
function Add-DocSource(){
    [CmdletBinding()]
    param(
        [Parameter(Mandatory=$true)]
        [string]$WorkingDirectory
    )

    pushd $WorkingDirectory
    Write-Output "WorkingDirectory      :   $WorkingDirectory"
    $yml = Parse-BuildYml "$WorkingDirectory\artifact.yml" -SkipVerification
    $path = "$WorkingDirectory\Sandcastle\Sandcastle.shfbproj"
    $xml = [xml](Get-Content $path);
    $msBuildNamespace = "http://schemas.microsoft.com/developer/msbuild/2003"
    $Docsource = $xml.Project.PropertyGroup[0].AppendChild($xml.CreateElement("DocumentationSources",$msBuildNamespace))
    
    # Loop to get the project path to add as a <DocumentationSource> to Sandcastle.shfbproj Project
    # Retrieve the projects from the framework in the yml
    $Framework = @($yml.publish.nuget_package.lib.keys)[0]
    foreach($Project in @($yml.publish.nuget_package.lib[$Framework]|%{
        ($_ -split ";")[0]
    })){
        $match = gci -Recurse "$Project"
        if($match.length -eq 0){
            throw "$Project not found"
        }else{
            $pathToProject = $match.FullName
            write-host "$pathToProject"
        }

        # Adding <DocumentationSource>
        $DocsourceChild = $Docsource.AppendChild($xml.CreateElement("DocumentationSource",$msBuildNamespace))
        $DocsourceChild.SetAttribute("sourceFile","$pathToProject") 
        Write-Output "Adding    :   $pathToProject to <DocumentationSources>"
    }
    $xml.Save($path)
    popd
}

# Add XML file to <DocumentationFile> to each project in solution
function Add-DocFile(){
    [CmdletBinding()]
    param(
        [Parameter(Mandatory=$true)]
        [string]$WorkingDirectory
    )
    Write-Output ""
    Write-Output "Adding XML to Documentation File to Projects"
    pushd $WorkingDirectory
    Write-Output "WorkingDirectory      :   $WorkingDirectory"
    $yml = Parse-BuildYml "$WorkingDirectory\artifact.yml" -SkipVerification
    
    # Loop through each project in yml
    # Retrieve the projects from the framework in the yml
    $Framework = @($yml.publish.nuget_package.lib.keys)[0]
    foreach($Project in @($yml.publish.nuget_package.lib[$Framework]|%{
        ($_ -split ";")[0]
    })){
        $path = gci -Recurse "$Project"
        # Get project name without .csproj, will be changed to .XML
        $projectName = [IO.Path]::GetFileNameWithoutExtension($Project)
        
        Write-Output "Project Name          :   $projectName" 
        Write-Output "Path                  :   $path"
        $xml = [xml](Get-Content $path);
        $msBuildNamespace = "http://schemas.microsoft.com/developer/msbuild/2003"

        # Removing <DocumentationFile> if it exists --> (then manually adding it to Release Build)
        foreach($PropertyGroup in $xml.Project.PropertyGroup){
            $n = $PropertyGroup.Item('DocumentationFile')
            if($n){
                $PropertyGroup.RemoveChild($n)
            }
        }

        # Adding <DocumentationFile> to project
        $docFile = $xml.Project.PropertyGroup[2].AppendChild($xml.CreateElement("DocumentationFile",$msBuildNamespace))
        $file = "bin\Release\$projectName.XML"
        $xml.Project.PropertyGroup[2].DocumentationFile = $file
  
        $xml.Save($path)
        Write-Output "Adding $file in <DocumentationFile> to $Project"
    }
    popd
}
