$OUT_DIR = "out"
$ROOT_PATH = $PSScriptRoot

if (!(Test-Path "$OUT_DIR")) {
    New-Item -ItemType Directory "$OUT_DIR"
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


function Compile-Source-File {
    param (
        $Name,
        $SourceDir = "src"
    )

    $baseName = (Get-Item "$SourceDir/$Name").BaseName

    $sourceFile = "$SourceDir/${Name}"
    $outFile = "$OUT_DIR/${baseName}.a"

    if (Needs-Recompilation $sourceFile $outFile) {
        Write-Host "Compiling ${baseName}"
        g++ -c -Wall -Wextra -Werror $sourceFile -o $outFile
    }
}


Compile-Source-File "stb_image.cpp"
Compile-Source-File "glad.c" "build/glad/src"
Compile-Source-File "main.cpp"
Compile-Source-File "utils.cpp"
Compile-Source-File "shader.cpp"
Compile-Source-File "shader_program.cpp"
Compile-Source-File "glfw_handler.cpp"
Compile-Source-File "texture.cpp"
