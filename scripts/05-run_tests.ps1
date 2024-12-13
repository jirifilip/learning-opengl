. "$PSScriptRoot/utils.ps1"

$OUT_DIR = "out"


$sourceFiles = Get-ChildItem -Path "tests" -Recurse | Where-Object { $_.Extension -eq ".cpp" }

foreach ($sourceFile in $sourceFiles) {
    Compile-Source-File "$($sourceFile.BaseName)$($sourceFile.Extension)" "$($sourceFile.DirectoryName)"
}


$librariesToLink = Get-ChildItem -Path $OUT_DIR | Where-Object { $_.Extension -eq ".a" } | ForEach-Object { $_.FullName }

g++ @($librariesToLink) `
    -o "$OUT_DIR/executable/test_main.exe" `
    -l glfw3 `
    -l freeglut `
    -l gtest `
    -l gmock `
    -l gtest_main `
    -l gdi32
    

if ($?) {
    . "$OUT_DIR/executable/test_main.exe"
}
