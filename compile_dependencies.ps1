$BUILD_DIR = "build"
$ROOT_PATH = $PSScriptRoot

if (Test-Path "$BUILD_DIR") {
    Remove-Item -Recurse "$BUILD_DIR"
}

New-Item -ItemType Directory "$BUILD_DIR"


function Download-Zip {
    param (
        $Name,
        $Url,
        $Flatten = $true
    )

    $dependencyArchive = "$BUILD_DIR/${Name}.zip"

    Invoke-WebRequest $Url -OutFile $dependencyArchive
    
    $expandPath = if ($Flatten -eq $true) {"$BUILD_DIR"} else {"$BUILD_DIR/$Name"}   
    Expand-Archive $dependencyArchive "$expandPath"
    
    Remove-Item $dependencyArchive
}


function Compile-Dependency {
    param (
        $Name
    )

    Set-Location "$BUILD_DIR/$Name"
    
    cmake -S . `
        -B build `
        -G "MinGW Makefiles" `
        -D CMAKE_C_COMPILER=gcc `
        -D CMAKE_CXX_COMPILER=g++ `
        -D CMAKE_C_COMPILER=gcc
    cmake --build build --config Debug

    Set-Location $ROOT_PATH
}


Download-Zip "stb" "https://github.com/nothings/stb/archive/5c205738c191bcb0abc65c4febfa9bd25ff35234.zip"

# https://glad.dav1d.de/#language=c&specification=gl&api=gl%3D3.3&api=gles1%3Dnone&api=gles2%3Dnone&api=glsc2%3Dnone&profile=core&loader=on
Download-Zip "glad" "https://glad.dav1d.de/generated/tmp9aklh4jwglad/glad.zip" $false

Download-Zip "freeglut-3.6.0" "https://github.com/freeglut/freeglut/archive/refs/tags/v3.6.0.zip"
Compile-Dependency "freeglut-3.6.0"

Download-Zip "glfw-3.4" "https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip"
Compile-Dependency "glfw-3.4"

Download-Zip "googletest-1.15.2" "https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip"
Compile-Dependency "googletest-1.15.2"