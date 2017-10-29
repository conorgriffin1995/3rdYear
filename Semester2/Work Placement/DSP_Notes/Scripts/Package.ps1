function Build-NugetPackage {
    <#
    .SYNOPSIS
    For CI use only.  Builds a nuget package from source, using metadata in artifact.yml.
    #>
    [CmdletBinding()]
    param(
        [string] $Description,
        [string] $ReleaseNotes,
        [string] $Author,
        [switch] $CI
    )

    Push-GitTopLevel -CI:$CI
    $yml = Parse-BuildYml

    new-item  -type Directory -force "tmp\lib"
    foreach($framework in $yml.publish.nuget_package.lib.Keys) {
        $zipFile = "$($yml.publish.nuget_package.id).$framework.nuget.zip"
        if(Test-Path($zipFile)) {
            UnZip-Dir $zipFile "tmp\lib\$framework"
        }

        #unzip symbols
        $symbolsZipFile = "$($yml.publish.nuget_package.id).$framework.symbols.zip"
        if(Test-Path($symbolsZipFile)) {
            new-item  -type Directory -force "symbols"
            UnZip-Dir $symbolsZipFile "symbols\$framework"
        }
    }
    $zipFile = "$($yml.publish.nuget_package.id).Content.nuget.zip"
    if(Test-Path($zipFile)) {
        UnZip-Dir $zipFile "tmp\content\Tools\$($yml.publish.nuget_package.id)"
    }

    Write-Output "---"
    Write-Output " Package Name:    $($yml.publish.nuget_package.id)"
    Write-Output " Package Version: $($yml.version)"
    Write-Output " Package lib:"
    foreach($framework in $yml.publish.nuget_package.lib.Keys) {
        Write-Output "  - $framework`:"
        foreach($project in $yml.publish.nuget_package.lib.$framework) {
            Write-Output "    - $project"
        }
    }
    Write-Output " Package Content:"
    foreach($content in $yml.publish.nuget_package.content) {
        Write-Output "  - $content"
    }
    Write-Output " Package Dependencies:"
    foreach($dependency in $yml.publish.nuget_package.dependencies) {
        Write-Output "  - $dependency"
    }
    Write-Output "---"

    Write-Output "**CREATING NUSPEC**"
    Push-Location 'tmp'
    #Write-Output "$NugetExe spec"
    & $NugetExe spec
    $nuspecFile = "$($yml.publish.nuget_package.id).nuspec"
    Rename-Item -Path Package.nuspec -newname $nuspecFile

    Write-Output "**UPDATING NUSPEC**"
    $id = $yml.publish.nuget_package.id
    if(!$Author) {
        if($yml.publish.nuget_package.author) {
            $Author = $yml.publish.nuget_package.author
        } else {
            $Author = 'DSP'
        }
    }
    $owner = 'DSP'
    if(!$Description) {
        if($yml.description -eq 'PLACEHOLDER DESCRIPTION') {
            $Description = 'No description available..'
        } else {
            $Description = $yml.description
        }
    }
    $version = $yml.version
    $date = Get-Date
    if(!$ReleaseNotes) {
        $ReleaseNotes = "Version $version of $id. Built on $Date"
    }

    [xml]$nuspec = Get-Content $nuspecFile
    $nuspec.package.metadata.RemoveChild($nuspec.SelectSingleNode('package/metadata/licenseUrl')) | Out-Null
    $nuspec.package.metadata.RemoveChild($nuspec.SelectSingleNode('package/metadata/projectUrl')) | Out-Null
    $nuspec.package.metadata.RemoveChild($nuspec.SelectSingleNode('package/metadata/iconUrl')) | Out-Null
    $nuspec.package.metadata.RemoveChild($nuspec.SelectSingleNode('package/metadata/tags')) | Out-Null

    $nuspec.package.metadata.id = "$id"
    $nuspec.package.metadata.version = "$version"
    $nuspec.package.metadata.authors = $Author
    $nuspec.package.metadata.owners = $owner
    $nuspec.package.metadata.description = $Description
    $nuspec.package.metadata.releasenotes = $ReleaseNotes
    if($yml.publish.nuget_package.dependencies) {
        foreach($dependency in $yml.publish.nuget_package.dependencies) {
            $dependencyId = ($dependency -split [Regex]::Escape(';'))[0]
            $dependencyVersion = ($dependency -split [Regex]::Escape(';'))[1]
            $newDependency = $nuspec.package.metadata.dependencies.AppendChild($nuspec.CreateElement("dependency"))
            $newDependency.SetAttribute("id", $dependencyId)
            $newDependency.SetAttribute("version", $dependencyVersion)
        }
    }
    $nuspec.package.metadata.dependencies.RemoveChild($nuspec.SelectSingleNode("package/metadata/dependencies/dependency[@id = 'SampleDependency']")) | Out-Null

    $nuspecFilePath = Resolve-Path $nuspecFile
    $nuspec.Save($nuspecFilePath)

    Write-Output '**BUILDING PACKAGE**'
    & $NugetExe pack $nuspecFile

    Pop-Location
    Copy-Item -Path ".\tmp\*" -Destination ".\" -Include *.nupkg
}