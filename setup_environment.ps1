$libraryPaths = @(
    "build/glfw-3.4/build/src",
    "build/freeglut-3.6.0/build/lib",
    "build/googletest-1.15.2/build/lib",
    "out"
)
$includePaths = @(
    "build/glfw-3.4/include",
    "build/freeglut-3.6.0/include",
    "build/glad/include",
    "build/glad/src",
    (Resolve-Path "build/stb*"),
    "build/googletest-1.15.2/googletest/include",
    "build/googletest-1.15.2/googlemock/include"
)

$env:LIBRARY_PATH = "$($libraryPaths -join ";")"
$env:CPLUS_INCLUDE_PATH = "$($includePaths -join ";")"