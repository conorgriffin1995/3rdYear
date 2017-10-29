param(
    [string] $TemplateDir = "$PSScriptRoot\..\Templates",
    [string] $OutputPath = ".\GroovyOutput",
    [string] $BuildTemplate = "$TemplateDir\Build.tpl",
    [string] $RunTestsTemplate = "$TemplateDir\RunTests.tpl",
    [string] $PackageTemplate = "$TemplateDir\Package.tpl",
    [string] $MergeTemplate = "$TemplateDir\Merge.tpl",
    [string] $PromoteTemplate = "$TemplateDir\Promote.tpl",
    [string] $UnitTestTemplate = "$TemplateDir\UnitTest.tpl",
    [string] $FolderTemplate = "$TemplateDir\Folder.tpl"
)


######################################################################################################################
# internal function only.
function Render-Template {
    <#
    .SYNOPSIS
    Helper function.

    .DESCRIPTION
    Converts .tpl files to .groovy files using EPS.  These groovy files are then processed by the
    Job DSL Jenkins plugin.
    #>
    [CmdletBinding()]
    param(
        [string] $JobName,
        [string] $Template,
        [string] $GroovyFileName
    )

    Write-Output "Rendering Template: $Template (Job Name: $JobName). To '$GroovyFileName.groovy'"
    $outputFile = EPS-Render -File $Template
    $outputFile | Out-File -Encoding "Default" "$GroovyFileName.groovy"
}

######################################################################################################################
function Create-NugetPipeline {
    <#
    .SYNOPSIS
    For CI use only.  Creates CI pipeline for "artifact" repo.
    #>
    [CmdletBinding()]
    param(
        [switch] $CI,
        [string] $branch
    )
    if(!$CI) {
        $Env:TeamProject = Read-Host "TeamProject"
        $Env:ProjectRepository = Read-Host "ProjectRepository"
    }

    Push-GitTopLevel -CI:$CI

    if($branch){
        Set-CurrentBranch $branch
    }

    write-host "env git brnach: $env:git_branch"

    $yml = Parse-BuildYml
    # Store Variables

    if($yml.compile.vm_requirement) {
        $vmRequirement = $yml.compile.vm_requirement
    }
    if($yml.dll -eq 'true') {
        $dll = $true
    } else { 
        $dll = $false 
    }
    if($yml.unit_test.unit_test_projects) {
        $unitTest = $true
    } else { 
        $unitTest = $false 
    }
    if($yml.integ_test.integ_test_projects) {
        $integTest = $true
    } else { 
        $integTest = $false 
    }
    if($yml.publish.publish_as -like '*nugetpackage*') {
        $nugetPackage = $true
    } else { $nugetPackage = $false }
    if($yml.publish.deploy -eq 'true') {
        $deploy = $true
    } else { $deploy -eq $false }
    
    # Used for Sandcastle and FxCop
    $fxFound =@(@($yml.publish.nuget_package.lib.keys)|?{$_ -ne "content"})[0]
    if($fxFound){
        $hasCodeToCompile = $true
    }else{
        $hasCodeToCompile = $false
    }
    if(!$yml.sandcastle){
        $Sandcastle = $true
    } elseif ($yml.sandcastle -eq 'true'){
        $Sandcastle = $true
    } elseif ($yml.sandcastle -eq 'false'){
        $Sandcastle = $false
    }

    if(!$yml.docs){
        $HasDocs = $false
    }elseif ($yml.docs -eq 'true'){
        $HasDocs = $true
    }elseif ($yml.docs -eq 'false'){
        $HasDocs = $false
    }

    $IsDocsOnly = Is-DocsOnly $yml
    $pipelinePath = "$global:componentsRoot/$Env:TeamProject/$Env:ProjectRepository" 
    

    # Debug Info
    # *Infer solution from file, not yaml
    Write-Output ""
    Write-Output "-----PIPELINE-CONFIG-----"
    Write-Output " TeamProject:        $Env:TeamProject"
    Write-Output " ProjectRepository:  $Env:ProjectRepository"
    Write-Output " Branch:             $branch"
    Write-Output " UnitTest:           $unitTest"
    Write-Output " IntegTest:          $integTest"
    Write-Output " FxCop:              $hasCodeToCompile"
    Write-Output " NugetPackage:       $nugetPackage"
    Write-Output " Dll:                $dll"
    Write-Output " PipelinePath:       $pipelinePath"
    Write-Output " Deploy:             $deploy"
    Write-Output " Solution:           $($yml.solution)"
    Write-Output " Package:            $($yml.publish.nuget_package.id)"
    Write-Output " Version:            $($yml.version)"
    Write-Output " Platform:           $($yml.compile.platform)"
    Write-Output " BuildConfiguration: $($yml.compile.configuration)"
    Write-Output " VMRequirement:      $($yml.compile.vm_requirement)"
    Write-Output " IsDocsOnly:         $IsDocsOnly"
    Write-Output " HasDocs:            $HasDocs"
    Write-Output " Sandcastle:         $Sandcastle"
    Write-Output "-------------------------"
    Write-Output ""

    Write-Output "Preparing Templates..."
    if(!(Test-Path($OutputPath))) {
        New-Item -path . -name "GroovyOutput" -type directory | Out-Null
    }
    
    $jobNum = 1
    # Build
    $buildJob = "$(Get-JobNum $jobNum) Build $Env:ProjectRepository"
    $jobNum++
    # Tests
    $runTestsJob = "$(Get-JobNum $jobNum) Run Tests"
    # UnitTests
    $unitTestJobs = @()
    if($unitTest) {
        if($yml.unit_test.unit_test_categories) {
            $unitTestCategories = $true
            $testNum = 1
            foreach($test in @($yml.unit_test.unit_test_categories)) {
                $num ="$(Get-JobNum $jobNum).$(Get-JobNum $testNum)"
                $unitTestJobs += "$num $Env:ProjectRepository UnitTest - $test"
                $testNum++
                $unitTestJobs
            }
        } else {
            $num ="$(Get-JobNum $jobNum).$(Get-JobNum 1)"
            $unitTestJobs += "$num $Env:ProjectRepository UnitTest"
        }
        $unitTestJobs
    }
    $jobNum++
    # Package
    if($nugetPackage -or $HasDocs) {
        $packageJob = "$(Get-JobNum $jobNum) Publish $Env:ProjectRepository Package"
        $jobNum++
    }
    # View
    $deletePipelineJob = "$pipelinePath/0 Delete Branch Pipeline"

    Write-Host "Rendering Templates..."
    # Build
    $jobName = "$pipelinePath/$branch/$buildJob"
    Render-Template $jobName $BuildTemplate "$OutputPath\Build"
    # Tests
    $jobName = "$pipelinePath/$branch/$runTestsJob"
    Render-Template $jobName $RunTestsTemplate "$OutputPath\RunTests"
    # UnitTests
    $id = 1
    foreach($job in $unitTestJobs) {
        $jobName = "$pipelinePath/$branch/$job"
        Render-Template $jobName $UnitTestTemplate "$OutputPath\UniTest$id"
        $id++
    }

        # Package
    $jobName = "$pipelinePath/$branch/$packageJob"
    Render-Template $jobName $PackageTemplate "$OutputPath\Package"

}

######################################################################################################################
# Run from CI only
function Delete-NugetPipeline {
    <#
    .SYNOPSIS
    Run from CI only. Deletes pipeline
    #>
    [CmdletBinding()]
    param()

    $jenkinsInstallDir = $Env:JENKINS_HOME
    $cliDir = "$jenkinsInstallDir\war\WEB-INF\"
    $branchJobsDir = "$jenkinsInstallDir\jobs\$Env:TeamProject\jobs\$Env:ProjectRepository\jobs\$Env:Branch\jobs"
    $folder = "$pipelinePath/$Env:Branch"

    $cliUsername = $Env:CliUsername -replace [Regex]::Escape("welfare\"), ""

    if(!$Env:Branch) {
        throw "No branch found. Aborting..."
    }

    Write-Output "         Parameters"
    Write-Output "-------------------"
    Write-Output "CliUsername:       $cliUsername"
    Write-Output "JenkinsInstallDir: $jenkinsInstallDir"
    Write-Output "cliDir:            $cliDir"
    Write-Output "BranchJobsDir:     $BranchJobsDir"
    Write-Output "Folder:            $Folder"
    Write-Output ""

    $jobsToDelete = Get-ChildItem $branchJobsDir

    Push-Location $cliDir
    Write-Output "Setting credentials for cli..."
    java -jar jenkins-cli.jar -s $Env:JENKINS_URL login --username $CliUsername --password $Env:CliPassword
    java -jar jenkins-cli.jar -s $Env:JENKINS_URL who-am-i

    Write-Output "Deleting branch: $Env:Branch"
    Write-Output "The following jobs will be deleted.."
    foreach($job in $jobsToDelete) {
        Write-Output "  - $job"
    }

    java -jar jenkins-cli.jar -s $Env:JENKINS_URL delete-job $folder
    java -jar jenkins-cli.jar -s $Env:JENKINS_URL logout
    Pop-Location

    Write-Output "`nDeleting remote branch: ready/$Env:Branch"
    git config --global credential.helper wincred
    git push origin --delete ready/$Env:Branch
}

function Run-SeedAllJobs {
    <#
    .SYNOPSIS
    For REM use only.  Loops over all TFS/git repos, and sets up a CI pipeline for each.
    #>
    [CmdletBinding()]
    param()

    Get-TFSGitRepositoriesAll | 
    Where-Object{Test-PipelineDslDrivenRepo $_.ApiUrl} | 
    Export-Csv DslRepos.csv #Exporting just to get a csv output in the workspace (i.e. to inspect)

    Import-Csv DslRepos.csv |
        Generate-AllPipelines
}

function Run-SeedJob {
    <#
    .SYNOPSIS
    For CI use only. Creates a pipeline for a "BOMi artifact" repo
    
    .DESCRIPTION
    This job is called by the 'Seed BomiArtifact Pipeline' admin job in Jenkins
    Requires thay $Env:TeamProject and $Env:ProjectRepository are both set
    #>
    [CmdletBinding()]
    param(
        [string] $Branch
    )

    if((!$Env:TeamProject) -or !($Env:ProjectRepository)) {
        throw "TeamProject and ProjectRepository Parameters need to be set!!"
    }

    if(!$branch)
    {
        $branch = "master"
    }

    Write-Host "TeamProject: $Env:TeamProject"
    Write-Host "Repository:  $Env:ProjectRepository"

    Generate-Pipeline "$global:componentsRoot\\$Env:TeamProject\\$Env:ProjectRepository" -branch $branch
}

function Run-SeedBranchJob {
    <#
    .SYNOPSIS
    For CI use only. Creates a pipeline for a specific branch of a "BOMi artifact" repo
    
    .DESCRIPTION
    This job is invoked in the first job of a pipeline to create the remaining jobs, taking acount of
    the artifact.yml in the particular branch being built
    #>
    [CmdletBinding()]
    param(
        [string] $Branch
    )

    if((!$Env:TeamProject) -or !($Env:ProjectRepository)) {
        throw "TeamProject and ProjectRepository Parameters need to be set!!"
    }

    if(!$branch)
    {
        $branch = "master"
    }

    Write-Host "TeamProject: $Env:TeamProject"
    Write-Host "Repository:  $Env:ProjectRepository"

    Generate-BranchPipeline "$global:componentsRoot\\$Env:TeamProject\\$Env:ProjectRepository" -branch $branch
}

function Generate-Pipeline {
    <#
    .SYNOPSIS
    Generate Pipeline
    #>
    [CmdletBinding()]
    param(
        [string] $ProjectsGroovyOutPath,
        [string] $Branch
    )

    #repeat for each template to render
    if(!$branch)
    { 
        throw "$branch parameter is required"
    }

    foreach($tpl in (Get-ChildItem "$PSScriptRoot\..\Templates\Seed\*.tpl"))
    {
        New-Item -Type Directory -Force "$OutputPath\$projectsGroovyOutPath" #ensure parent folder exists

        $tplNoExtension = [System.IO.Path]::GetFileNameWithoutExtension($tpl.Name)

        Render-Template `
         -JobName "Seed Nuget->$global:componentsRoot >> $Env:TeamProject >> $Env:ProjectRepository" `
         -Template $tpl.FullName -GroovyFileName "$OutputPath\$projectsGroovyOutPath\$tplNoExtension" 
    }
}

function Generate-BranchPipeline {
    <#
    .SYNOPSIS
    Generate Pipeline
    #>
    [CmdletBinding()]
    param(
        [string] $ProjectsGroovyOutPath,
        [string] $Branch
    )
        
    #repeat for each template to render
    if(!$branch)
    { 
        throw "$branch parameter is required"
    }

    $tpl = Get-Item "$PSScriptRoot\..\Templates\Seed\GetPipeline.tpl"
    Write-Host $tpl.FullName

    &notepad $tpl.FullName

    New-Item -Type Directory -Force "$OutputPath\$projectsGroovyOutPath" #ensure parent folder exists

    $tplNoExtension = [System.IO.Path]::GetFileNameWithoutExtension($tpl.Name)

    Render-Template `
     -JobName "Seed Nuget->$global:componentsRoot >> $Env:TeamProject >> $Env:ProjectRepository" `
     -Template $tpl.FullName -GroovyFileName "$OutputPath\$projectsGroovyOutPath\$tplNoExtension" 
}

function Generate-AllPipelines{
    Param(
        [Parameter(ValueFromPipeline)]
        $dslRepos
    )

    process{
        # set both variables for Templates
        $Env:TeamProject = $_.ProjectName
        $Env:ProjectRepository = $_.RepoName

        Generate-Pipeline -projectsGroovyOutPath "$componentsRoot\\$Env:TeamProject\\$Env:ProjectRepository" -branch "master"
    }
}

function Test-PipelineDslDrivenRepo{
    <#
    .SYNOPSIS
    For CI use only.
    #>
    Param(
        [string] $apiUri,
        [Parameter(Mandatory=$false)]
        [string] $ymlFileName
    )

    if(!$ymlFileName){
        $ymlFileName = "artifact.yml"
    }

    Test-TFSGitItem  "$apiUri/items?api-version=2.0&scopePath=$ymlFileName"
}

function Get-JobNum {
    [CmdletBinding()]
    param(
        [int] $JobNum
    )

    if($JobNum -lt 10) {
        return "0$JobNum"
    } else {
        return "$JobNum"
    }
}
