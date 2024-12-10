$libraryPaths = @(
    "build/glfw-3.4/build/src",
    "build/freeglut-3.6.0/build/lib",
    "build/googletest-1.15.2/build/lib",
    "out"
) -join ";"
$includePaths = @(
    "include",
    "build/glfw-3.4/include",
    "build/freeglut-3.6.0/include",
    "build/glad/include",
    "build/glad/src",
    (Resolve-Path "build/stb*").toString().replace("\", "/"),
    "build/googletest-1.15.2/googletest/include",
    "build/googletest-1.15.2/googlemock/include"
) -join ";"

if (Test-Path ".env") {
    Remove-Item ".env"
}
New-Item -Path . -Name ".env" -ItemType "file" -Value @"
LIBRARY_PATH="$libraryPaths"
CPLUS_INCLUDE_PATH="$includePaths"
"@