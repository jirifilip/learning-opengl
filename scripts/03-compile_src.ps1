. "$PSScriptRoot/utils.ps1"


$OUT_DIR = "out"

if (!(Test-Path "$OUT_DIR")) {
    New-Item -ItemType Directory "$OUT_DIR"
}

if (!(Test-Path "$OUT_DIR/executable")) {
    New-Item -ItemType Directory "$OUT_DIR/executable"
} 


$sourceFiles = Get-ChildItem -Path src -Recurse |
    Where-Object { $_.Extension -eq ".cpp" }


foreach ($sourceFile in $sourceFiles) {
    Compile-Source-File "$($sourceFile.BaseName)$($sourceFile.Extension)" "$($sourceFile.DirectoryName)"
}


Compile-Source-File "glad.c" "build/glad/src"

