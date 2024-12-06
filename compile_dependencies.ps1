$BUILD_DIR = "build"
$ROOT_PATH = $PSScriptRoot

$env:OPENGL_PROJECT_LIBRARY_PATH = ""
$env:OPENGL_PROJECT_INCLUDE_PATH = ""


if (Test-Path "$BUILD_DIR") {
    Remove-Item -Recurse "$BUILD_DIR"
}

New-Item -ItemType Directory "$BUILD_DIR"


function Download-GitHub-Dependency {
    param (
        $Name,
        $Url
    )

    $dependencyArchive = "$BUILD_DIR/${Name}.zip"

    Invoke-WebRequest $Url -OutFile $dependencyArchive
    Expand-Archive $dependencyArchive "$BUILD_DIR"
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


function Push-Include-Path {
    param (
        $DependencyName,
        $Path = "include"
    )
    $pathToInclude = "$BUILD_DIR/$DependencyName/$Path"
    $env:OPENGL_PROJECT_INCLUDE_PATH = "${pathToInclude}:${env:OPENGL_PROJECT_INCLUDE_PATH}"
}


function Push-Library-Path {
    param (
        $DependencyName,
        $Path
    )
    $libraryPath = "$BUILD_DIR/$DependencyName/build/$Path"
    $env:OPENGL_PROJECT_LIBRARY_PATH = "${libraryPath}:${env:OPENGL_PROJECT_LIBRARY_PATH}"
}


Download-GitHub-Dependency "glfw-3.4" "https://github.com/glfw/glfw/releases/download/3.4/glfw-3.4.zip"
Compile-Dependency "glfw-3.4"
Push-Include-Path "glfw-3.4"
Push-Library-Path "glfw-3.4" "src"

Download-GitHub-Dependency "googletest-1.15.2" "https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip"
Compile-Dependency "googletest-1.15.2"
Push-Include-Path "googletest-1.15.2" "googletest/include"
Push-Include-Path "googletest-1.15.2" "googlemock/include"
Push-Library-Path "lib"