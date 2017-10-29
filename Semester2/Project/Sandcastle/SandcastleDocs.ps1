function Build-SandcastleDocs() {
    [CmdletBinding()]
    param(
        [Parameter(Mandatory=$false)]
        [string]$WorkingDirectory,
        [Parameter(Mandatory=$false)]
        [string]$TemplateDirectory,
        [Parameter(Mandatory=$false)]
        [switch]$CI,
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
    Write-Warning "STEP 1 Copying Sandcastle Template"
    Write-Output ""

    Write-Output " WorkingDirectory  :   $WorkingDirectory"
    Write-Output " TemplateDirectory :   $TemplateDirectory"
    Write-Output " CI                :   $CI"
    Write-Output ""

    if($CI) {
        Write-Output ""
    }

    Copy-SandcastleTemplate -WorkingDirectory $WorkingDirectory `
                            -TemplateDirectory $TemplateDirectory

    Write-Output ""
    Write-Warning "STEP 2 Add Documentation Source to .shfbproj"
    Write-Output ""

    Add-DocSource -WorkingDirectory $WorkingDirectory
    
    Write-Output ""
    Write-Warning "STEP 3 Build Sandcastle Solution"
    Write-Output ""

    Set-Location .\Sandcastle
    $solution = Get-Solution

    Write-Output "---"
    Write-Output " Compiling `| Sandcastle Solution `| $solution"
    Write-Output "---"

    & $MSBuildExe $solution

    if(!$?) {
        throw "Build Failed!"
    }
    
    #
    # packaging
    #
    if ($CI) {
        Zip-Dir -Directory .\Help  -ZipFile "$projectRepository.docs.zip"
        cp "$projectRepository.docs.zip" ..
        popd
    }
    cd..
    Remove-Item -Force -Recurse Sandcastle 
}

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
    #copy over all files
    $from = $TemplateDirectory
    $to = $WorkingDirectory
    Get-ChildItem -Path $from | Copy-Item -Destination "$to\Sandcastle" -Recurse
}

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
    $ProjectToAdd=@($yml.sandcastle_docs)

    #Loop to get project path to add as a <DocumentationSource> to Sandcastle Project
    foreach($ProjectToAdd in @($yml.sandcastle_docs)){
        $match = gci -Recurse "$ProjectToAdd"
        if($match.length -eq 0){
            throw "$ProjectToUpdate not found"
        }else{
            $pathToProject = $match.FullName
        }
        $DocsourceChild = $Docsource.AppendChild($xml.CreateElement("DocumentationSource",$msBuildNamespace))
        $DocsourceChild.SetAttribute("sourceFile","$pathToProject") 
        Write-Output "Adding    :   $pathToProject to <DocumentationSources>"
    }
    $xml.Save($path)
    popd
}

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
    $ProjectToUpdate=@($yml.sandcastle_docs)
    foreach($ProjectToUpdate in @($yml.sandcastle_docs)){
        $match = gci -Recurse "$ProjectToUpdate"
        if($match.length -eq 0){
            throw "$ProjectToUpdate not found"
        }else{
            $path = $match.FullName
        }
        $v = [IO.Path]::GetFileNameWithoutExtension($ProjectToUpdate)
        Write-Output "Project Name          :   $v" 
        Write-Output "Path                  :   $path"
        $xml = [xml](Get-Content $path);
        $msBuildNamespace = "http://schemas.microsoft.com/developer/msbuild/2003"

        #Removing <DocumentationFile> if it exists --> (then manually adding it to Release Build)
        foreach($PropertyGroup in $xml.Project.PropertyGroup){
            $n = $PropertyGroup.Item('DocumentationFile')
            if($n){
                $PropertyGroup.RemoveChild($n)
            }
        }

        #Adding <DocumentationFile> to project
        $docFile = $xml.Project.PropertyGroup[2].AppendChild($xml.CreateElement("DocumentationFile",$msBuildNamespace))
        $file = "bin\Release\$v.XML"
        $xml.Project.PropertyGroup[2].DocumentationFile = $file
  
        $xml.Save($path)
        Write-Output "Adding $file in <DocumentationFile> to $ProjectToUpdate"
    }
    popd
}
