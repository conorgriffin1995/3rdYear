function Run-CodeAnalysis(){
	<#
	.SYNOPSIS 
	Builds FXCOP which analyzes managed code assemblies using one dll file at a time
	
	.DESCRIPTION
	Builds FXCOP which analyzes managed code assemblies and reports information about the assemblies, such as possible design, performance, localization and security improvements. For developers, also allows the generated XML file to be previewed.
	For developers, also allows the generated XML files to be previewed

	.PARAMETER WorkingDirectory
    The root directory for the repo.  Defaults to the current directory.

	.PARAMETER TemplateDirectory
    The directory where the FxCop template resides (.\ReleaseEngineering\BuildScripts\FxCop)
	
	.PARAMETER CI
    Switch indicating whether running within a CI context; developers should typically NOT set this flag.

	.MKDIR XML
    create a folder and move all generted xml files to this xml folder
	#>
	param(
		[Parameter(Mandatory=$false)]
		[string]$WorkingDirectory,
		[Parameter(Mandatory=$false)]
        [string]$TemplateDirectory,
		[Parameter(Mandatory=$false)]
		[switch]$CI
	)
	if(!$WorkingDirectory){
			$WorkingDirectory=Convert-Path .
	}
						
		
	if(!$TemplateDirectory) {
        $TemplateDirectory = resolve-path "$PSScriptRoot\..\..\..\FxCop"
    }

	Write-Output ""
    Write-Verbose "STEP 1 Copying FxCop Template"
    Write-Output ""

	Write-Output " WorkingDirectory  :   $WorkingDirectory"
    Write-Output " TemplateDirectory :   $TemplateDirectory"
    Write-Output " CI                :   $CI"
    Write-Output ""
	$yml = Parse-BuildYml
	if($CI) {
        Write-Output ""
    }

	Copy-FxCopTemplate	-WorkingDirectory $WorkingDirectory `
                       	-TemplateDirectory $TemplateDirectory	

	Write-Output "WorkingDirectory      :   $WorkingDirectory"
	
	Write-Output ""
    Write-Verbose "STEP 2 Add Targets to the FxCop XML file"
    Write-Output ""

	Write-Output "Copying XML Files to XML folder"
	mkdir xml	
	
	$path = "$WorkingDirectory\FxCop\fxcopRule.FxCop"	
    $xml = [xml](Get-Content $path);
	$TargetXML = $xml.FxCopProject.AppendChild($xml.CreateElement("Targets"))

	# Loop to get the project path to add as a <DocumentationSource> to Sandcastle.shfbproj Project
    # Retrieve the projects from the framework in the yml
    $Framework = @($yml.publish.nuget_package.lib.keys)[0]

	foreach($project in @($yml.publish.nuget_package.lib[$Framework]|%{
        ($_ -split ";")[0]
    })){
		write-output "$project"
		$proName = [System.IO.Path]::GetFileNameWithoutExtension($project)
		$dllName = "$proName.dll"
		$getPath = ls -Recurse -Include "$dllName"
		$assemblyPath = $getPath.FullName[0]

    	$msBuildNamespace = "http://schemas.microsoft.com/developer/msbuild/2003"
		# looks through the xml file for the fxcopRule project and adds targets for each dll that it ran the rules against  
		# Adding <Targets>
		$TargetXML = $xml.FxCopProject.AppendChild($xml.CreateElement("Targets"))
		$TargetChild = $TargetXML.AppendChild($xml.CreateElement("Target"))
		$TargetChild.SetAttribute("Name","$assemblyPath") 
		
		Write-Output "Adding     : $assemblyPath to <Target>"
		$TargetChild.SetAttribute("Analyze","True")
		Write-Output "Setting    :   Analyze to True"
		$TargetChild.SetAttribute("AnalyzeAllChildren","True")
		Write-Output "Setting    :   AnalyzeAllChildren to True"
		$xml.Save($path)
		
		#executing the command against the fxcopcmd.exe file and the path where the fxcop project is with the set of rules and the dll files and outputs the result into an xml file
		& $Global:fxcopcmd /p:`"$path`" /file:`"$assemblyPath`" /out:`"$proName.xml`"

		$xmlName = "$proName.xml"
		#move the xml files created for each project into XML folder, an xml file gets generated only if the dll had bad codeing standards 
		if(test-path $xmlName){
			move-item $xmlName xml
		}
		
	}

	#This loops through the xml folder for xml files and ouputs the results to the xml file name with an extention called error when ever it finds an error or any other condition passed into it
	$files = Get-ChildItem xml
	for ($i=0; $i -lt $files.count; $i++) {
		#$outfile = $files[$i].FullName + "Error"
 		Get-Content $files[$i].FullName | Where-Object { ($_ -match 'CriticalError' ) } #| set-Content $outfile
		Write-Warning "Level=CriticalError, pipeline will bypass this for now, but code should be refactored by developer.."
	}		 
	
	#
	# packaging
	#
	if($CI){
		zip-dir -directory .\xml -zipFile "fxCop.zip"
	}
}

# Copy over FxCop template to $WorkingDirectory
function Copy-FxCopTemplate(){
    [CmdletBinding()]
    param(
        [Parameter(Mandatory=$true)]
        [string]$WorkingDirectory,
        [Parameter(Mandatory=$true)]
        [string]$TemplateDirectory
    )

    Write-Output "Copying Template to:"
    mkdir FxCop

    # Copy over all files
    $from = $TemplateDirectory
    $to = $WorkingDirectory
    Get-ChildItem -Path $from | Copy-Item -Destination "$to\FxCop" -Recurse
}



