function Publish-NugetPackage {
    <#
    .SYNOPSIS
    ## For CI use only.
    #>
    [CmdletBinding()]
    param(
        [Parameter(ParameterSetName = "CI")][switch]$CI
    )

    Push-GitTopLevel -CI:$CI
    $yml = Parse-BuildYml
    $nupkg = "$($yml.publish.nuget_package.id).$($yml.version).nupkg"
    if(!(Test-Path ".\$nupkg")) {
        throw "$nupkg not found. Run Build-NugetPackage to create package file"
    }

    Write-Output "---"
    Write-Output " Nupkg:         $nupkg"
    Write-Output " Nuget Server:  $NugetServer"
    Write-Output " Nuget Staging: $NugetStaging"
    Write-Output "---"

    if($yml.publish.deploy -ne 'true') {
        Write-Output "Deploy switch not set in publish section of artifact.yml. Package will not be published to server."
        if($CI) {
            # Set build to unstable
        }
        exit 0
    }
    
    $publishDir = "Publish"
    Create-DirIfRequired $publishDir
    Copy-Item -Path ".\$nupkg" -Destination $publishDir
    
    if($CI) {
        Publish-FromCI
        Publish-Symbols  "Symbols" -packageName $nupkg         
    } 
}

function Publish-FromCI {
    <#
    .SYNOPSIS
    For CI use only
    #>
    [CmdletBinding()]
    param()

    if(!(Is-Master))
    {
       New-WIPFeedIfNeeded $env:GIT_BRANCH      
       Register-WIPNugetFeed -name $env:GIT_BRANCH      
       $nugetFeed = Get-WIPFeedPath $env:GIT_BRANCH

        #if on a dev branch, allow republishing a package
        $packagePath = "$nugetFeed\$($yml.publish.nuget_package.id)\$($yml.version)"
        if(Test-Path $packagePath){
            Write-Host "Deleting WIP package $packagePath so that it can be re-published"
            Remove-Item $packagePath -Recurse 
        }

    }
    else {
        $nugetFeed = $NugetServer
    }

    $cmd = "$NugetExe init $publishDir $nugetFeed -verbosity detailed"
    Write-Verbose "Executing: $cmd" 
    Invoke-Expression $cmd

    if(!$?){
        write-warning "nuget command failed"
    }

    Write-Output "Published Version $($yml.version) of $($yml.publish.nuget_package.id) to $nugetFeed"

    if(!(Is-Master)){
        Unregister-WIPNugetFeed -name $env:GIT_BRANCH
    }
}

function Publish-Symbols {
    <#
    .SYNOPSIS
    Short description
    #>
    [CmdletBinding()]
    param(
        [string] $SymbolsFolder,
        [string] $PackageName
    )

    write-host "package name $packageName"
    $packageName = [System.IO.Path]::GetFileNameWithoutExtension($packageName)
    $dest = "$symStore\$packageName" 

    New-Item -Force -ItemType Directory $dest

    gci -rec $symbolsFolder\*.pdb|%{
        write-host "publishing symbol: $($_.Name) to $dest"
        cp $_.FullName $dest -Force
    }
}

