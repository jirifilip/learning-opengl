$OUT_DIR = "out"
$ROOT_PATH = $PSScriptRoot

if (!(Test-Path "$OUT_DIR")) {
    New-Item -ItemType Directory "$OUT_DIR"
}

if (!(Test-Path "$OUT_DIR/executable")) {
    New-Item -ItemType Directory "$OUT_DIR/executable"
} 


function Needs-Recompilation {
    param (
        $sourceFile,
        $outFile
    )

    if (!(Test-Path -Path $sourceFile)) {
        return $true
    }

    if (!(Test-Path -Path $outFile)) {
        return $true
    }

    $sourceTimestamp = (Get-Item $sourceFile).LastWriteTime
    $outTimestamp = (Get-Item $outFile).LastWriteTime

    if ($sourceTimestamp -gt $outTimestamp) {
        return $true
    }

    return $false
}


function Is-Executable {
    param (
        $SourceFile
    )

    return (Get-Item $SourceFile).Directory.BaseName -eq "main"
}


function Compile-Source-File {
    param (
        $Name,
        $SourceDir = "src"
    )

    $baseName = (Get-Item "$SourceDir/$Name").BaseName

    $sourceFile = "$SourceDir/${Name}"

    if (Is-Executable $sourceFile) {
        $outFile = "$OUT_DIR/executable/${baseName}.a"
    } else {
        $outFile = "$OUT_DIR/${baseName}.a"
    }

    if (Needs-Recompilation $sourceFile $outFile) {
        Write-Host "Compiling ${baseName}"
        g++ -c -Wall -Wextra -Werror $sourceFile -o $outFile
    }
}


$sourceFiles = Get-ChildItem -Path src -Recurse |
    Where-Object { $_.Extension -eq ".cpp" }


foreach ($sourceFile in $sourceFiles) {
    Compile-Source-File "$($sourceFile.BaseName)$($sourceFile.Extension)" "$($sourceFile.DirectoryName)"
}


Compile-Source-File "glad.c" "build/glad/src"

