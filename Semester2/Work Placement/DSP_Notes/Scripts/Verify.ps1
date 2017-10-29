function Verify-Yml {
    <#
    .SYNOPSIS
    Verify that yml file meets certain requirements
    #>
    [CmdletBinding()]
    param(
        $Yml
    )

    # Violations
    return $true
    $violation = $false
    $versionViolation = $false

    $version = $Yml.version
    $packageID = $Yml.publish.nuget_package.id

     
    Write-Verbose "Verifying version is greater than server version:"
    if(!(Is-Master))
    {
      Write-Host "Not a master branch. Skipping version validation"
    }
    elseif (Is-DocsOnly $yml){
      Write-Host "Docs Only project. Skipping version validation"
    }
    else
    {
        $serverVersion = Get-NugetPackageVersion $packageID
        Write-Verbose "Version: $version  |  ServerVersion: $serverVersion"
        if((Get-GreatestVersion @($version, $serverVersion)) -eq $serverVersion) {
            $violation = $true
            $versionViolation = $true   
        }
    }


    Write-Host "`nVerify"
    Write-Host "-------------"
    Display-VerifyResults "Version" $versionViolation
    Write-Host "-------------"

    if($violation) {
        throw "Yml violations detected. See the above for 'X'"
    }
}

function Display-VerifyResults {
    <#
    .SYNOPSIS
    Short description
    #>
    [CmdletBinding()]
    param(
        [string] $Category,
        [bool] $Violation
    )

    Write-Host -NoNewline "$Category`:    ".PadLeft(10, ' ')
    if($Violation) { Write-Host -ForegroundColor Red "X" } else { Write-Host -ForegroundColor Green "O" }
}