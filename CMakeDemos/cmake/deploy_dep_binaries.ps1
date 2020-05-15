[cmdletbinding()]
param([string]$targetBinary, [string]$installedDirsHint, [string]$tlogFile, [string]$copiedFilesLog)

##动态库所在路径数组
$binaryDirs = $installedDirsHint.Split(";")
$g_searched = @{ }
 
# Ensure we create the copied files log, even if we don't end up copying any files
if ($copiedFilesLog) {
    Set-Content -Path $copiedFilesLog -Value "" -Encoding Ascii
}

function findBinaryDir([string]$target) {
    return $binaryDirs | Where-Object { Test-Path "$_\$target" } | Select-Object -First 1
}

function deployBinary([string]$targetBinaryDir, [string]$sourceDir, [string]$targetBinaryName) {
    if (Test-Path "$targetBinaryDir\$targetBinaryName") {
        Write-Verbose " ${targetBinaryName}:already present"        
    }
    else {
        Write-Verbose " ${targetBinaryName}:Copying $sourceDir\$targetBinaryName"
        Copy-Item "$sourceDir\$targetBinaryName" $targetBinaryDir
    }

    if ($copiedFilesLog) { Add-Content $copiedFilesLog "$targetBinaryDir\$targetBinaryName" }
    if ($tlogFile) { Add-Content $tlogFile "$targetBinaryDir\$targetBinaryName" }     
}

Write-Verbose "Resolving base path $targetBinary..."
try {
    $baseBinaryPath = Resolve-Path $targetBinary -erroraction stop
    $baseTargetBinaryDir = Split-Path $baseBinaryPath -parent
}
catch [System.Management.Automation.ItemNotFoundException] {
    return
}

function resolve([string]$targetBinary) {
    Write-Verbose "Resolving $targetBinary"
    try {
        $targetBinaryPath = Resolve-Path $targetBinary -erroraction stop 
    }
    catch [System.Management.Automation.ItemNotFoundException] {
        return
    }

    $targetBinaryPath = Split-Path $targetBinaryPath -parent 

    $a = $(dumpbin /DEPENDENTS $targetBinary | ? { $_ -match "^    [^ ].*\.(dll|tx)" } | % { $_ -replace "^    ", "" })
    $a | % {
        if ([string]::IsNullOrEmpty($_)) {
            return
        }
        if ($g_searched.ContainsKey($_)) {
            Write-Verbose "  ${_}: previously searched - Skip"
            return
        }
        $g_searched.Set_Item($_, $true)

        $binaryDir = findBinaryDir($_)
        if ($binaryDir) {
            deployBinary $baseTargetBinaryDir $binaryDir "$_"
            resolve "$targetBinaryPath\$_"
        }
        else {
            Write-Verbose "${_}:${_} not found."
        }
    }
    Write-Verbose "Done Resolving $targetBinary."
}

resolve($targetBinary)
Write-Verbose $($g_searched | Out-String)
