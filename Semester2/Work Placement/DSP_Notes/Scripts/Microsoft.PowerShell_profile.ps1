#
# REM modules
#
$dbReleaseUNCPath='\\vssdmrelease\Release\DbRelease'

Set-ExecutionPolicy "Unrestricted"

if (!(test-path 'Z:\')){
	net use Z: $dbReleaseUNCPath            
}

#########################Setting up PSModule path ##########################

if(Test-Path 'env:\USE_LOCAL_REM'){
	$rem_modules_path = 'c:\git\ReleaseEngineering\BuildScripts\PSModules;c:\git\ReleaseEngineering\BuildScripts\PSModules\ThirdParty'
}
else {
	$rem_modules_path = 'Z:\powershell\Modules\'
}

if (!($($ENV:PSModulePath).contains($rem_modules_path))){$ENV:PSModulePath+=";$rem_modules_path"}

############################################################################

#
# TFS module
#
$global:tfs = @{
    root_url    = 'http://vssdmlivetfs:8080/tfs'
    collection  = 'BomiLiveTFS'
    project     = 'ReleaseEngineering'
}

Import-Module -Name CredentialManager
Import-Module -Name TFS
Import-Module -Name TFS2

Import-Module -Name BomiAllInOneV2 -DisableNameChecking
Import-Module -Name BomiArtifact   -DisableNameChecking

echo "To use Get-TFS commands, logon using:"
echo ""
echo "`$global:tfs.credential  = Get-Credential"
echo ""


#
# *nix equivalents
#
function which($name)
{
    Get-Command $name | Select-Object -ExpandProperty Definition
}

#
# useful aliases
#
function gs { @(git status $args) }
function gsbp { @(git status --branch --porcelain $args) }


# Default Dir
cd c:\git

#Repos Root
$Env:ReposRoot = "C:\Git"


$global:tfs = @{
	root_url    = 'http://vssdmlivetfs:8080/tfs'
	collection  = 'BomiLiveTFS'
	project     = 'ReleaseEngineering'
}


function log {
                [CmdletBinding()]
                param(
					[string] $Log
                )

                Write-Host ">: $Log" -ForegroundColor DarkGray
}


#=================== shortcut functions ===================

function gx{
	gitextensions
}

function module{
	Remove-Module -Name BomiArtifact
	Import-Module -Name BomiArtifact
}