function Build-NugetSolution {
    <#
    .SYNOPSIS
    Builds Visual Studio solution using msbuild, using metadata in artifact.yml.

    .DESCRIPTION
    Builds Visual Studio solution using msbuild, restoring prerequisite nuget packages beforehand.
    The built assemblies are versioned as per artifact.yml (AssemblyVersion.[cs|vb] is updated first).

    .PARAMETER Package
    For CI use only; packages up the build DLLs as zip file for use later on in the CI pipeline.  What is zipped up depends on the artifact.yml file. Developers should typically NOT set this flag.

    .PARAMETER NoWarnings
    Switch to suppress any warning messages in the build output (errors are still shown via

    .PARAMETER CI
    Switch indicating whether running within a CI context.  Developers should typically NOT set this flag.

    .NOTES
    This script assumes it is run in the directory containing the artifact.yml file.

    .LINK
    https://msdn.microsoft.com/en-us/library/ms164311.aspx#Switches
    #>
    [CmdletBinding()]
    param(
        [switch] $Package,
        [switch] $NoWarnings,
        [switch] $CI,
        [Parameter(Mandatory=$false)]
        [string]$WorkingDirectory
    )

    if(!$WorkingDirectory){
        $WorkingDirectory = Convert-Path .
    }

    if($CI) {
       Restore-Workspace -CI:$CI
    }

    pushd $WorkingDirectory
    Write-Output "WorkingDirectory      :   $WorkingDirectory"

    $yml = Parse-BuildYml 
    $solution = Get-Solution
    Set-AssemblyVersion -Path . -Version $yml.version 
    
    # Calling Add-DocFile function to add XML fie to bin\release folders
    # The XML file is needed to generate Sandcastle documenttation off of
    Add-DocFile -WorkingDirectory $WorkingDirectory
    

    Write-Output "---"
    Write-Output " Compiling `| Nuget Package `| $solution"
    Write-Output "---"

    Register-WIPNugetFeedIfNeeded
    
    Restore-NugetPackages -Solution (Resolve-Path $solution)
    $msBuildArgs = @("$solution",
                        '/m',
                        '/p:GenerateDocumentation=False',
                        '/nr:false',
                        '/p:DebugType=pdbonly',
                        "/p:Platform=$($yml.compile.platform)",
                        "/p:configuration=$($yml.compile.configuration)",
                        "/verbosity:$($yml.compile.verbosity)"
    )
    $yml.compile.targets | % {
        $msBuildArgs += "/t:$_"
    }
    if($NoWarnings) {
        $msBuildArgs += "/clp:ErrorsOnly"
    }

    Write-Output "$MSBuildExe $msBuildArgs"
    & $MSBuildExe $msBuildArgs

    if(!$?) {
        throw "Build Failed!"
    }

    if($Package) {
        if($yml.unit_test.unit_test_projects) {
            Write-Output 'UnitTest project(s) detected. Packaging...'
            foreach($project in @($yml.unit_test.unit_test_projects)) {
                $projectPath  = Resolve-Path $project
                Zip-Dir $projectPath "$project.zip"
            }
        }
        if($yml.integ_test.integ_test_assemblies) {
            Write-Output "IntegTest project(s) detected."
        }
        if($yml.publish.nuget_package.lib) {
            foreach($framework in $yml.publish.nuget_package.lib.Keys) {
                $zipFile = "$($yml.publish.nuget_package.id).$framework.nuget.zip"
                $symbolsZipFile = "$($yml.publish.nuget_package.id).$framework.symbols.zip"
                foreach($entry in $yml.publish.nuget_package.lib.$framework) {
                    $project = ($entry -split [Regex]::Escape(';'))[0]
                    $item = ($entry -split [Regex]::Escape(';'))[1]
                    $symbols = [System.IO.Path]::GetFileNameWithoutExtension($item) +  ".pdb"

                    $projectDir = (Get-Item (Resolve-Path (ls -Recurse -Include $project))).Directory.FullName
                    if(!($projectDir -and (Test-Path $projectDir))){
                        throw "Project file not found $project not found ${projectDir}. Check yml file entry: ${entry}"
                    }
                    Zip-Dir "$projectDir\bin\$($yml.compile.configuration)\$item" $zipFile

                    #including debug symbols
                    $item = ($entry -split [Regex]::Escape(';'))[1]
                    Write-Output "zipping $symbols"
                    Zip-Dir "$projectDir\bin\$($yml.compile.configuration)\$symbols" $symbolsZipFile
                }
            }
        }
        if($yml.publish.nuget_package.content) {
          foreach($entry in $yml.publish.nuget_package.lib.$framework) {
            Write-Warning "entry: $entry"
            $project = ($entry -split [Regex]::Escape(';'))[0]
            $item = ($entry -split [Regex]::Escape(';'))[1]
            $projectDir = (Get-Item (Resolve-Path (ls -Recurse -Include $project))).Directory.FullName
            if(!($projectDir -and (Test-Path $projectDir))){
                throw "Project file not found $project not found ${projectDir}. Check yml file entry: ${entry}"
            }
            Zip-Dir "$projectDir\bin\$($yml.compile.configuration)\$item" $zipFile
          }
        }
    }
}

function Build-NugetFromDll {
    <#
    .SYNOPSIS
    For CI use only.  Packages up a "raw" DLL as a nuget package.

    .DESCRIPTION
    Some of the SDM applications have dependencies on 3rdparty DLLs that are not available as nuget packages, and for
    which we do not have the source code.  In order that these can be consumed as nuget packages, these DLLs are being
    repackaged.  This function supports this using metadata taken from the artifact.yml file.
    #>
    [CmdletBinding()]
    param(
        [switch] $Package,
        [switch] $NoWarnings,
        [switch] $CI
    )

    if($CI) {
       Restore-Workspace -CI:$CI
    }

    $yml = Parse-BuildYml 
    $projectExt = Get-ProjectExtension


    Write-Output "---"
    Write-Output " Zipping `| Nuget Package "
    Write-Output "---"
   

    if($Package) {
        if($yml.publish.nuget_package.lib) {
            foreach($framework in $yml.publish.nuget_package.lib.Keys) {
                $zipFile = "$($yml.publish.nuget_package.id).$framework.nuget.zip"
                foreach($entry in $yml.publish.nuget_package.lib.$framework) {
                    $dllFullName = $entry
                    if(!($dllFullName -and (Test-Path $dllFullName))){
                        throw "DLL ${dllFullName} not found. Check yml file entry."
                    }                 
                    Zip-Dir ".\$dllFullName" $zipFile
                }
            }
        }
    }
}
