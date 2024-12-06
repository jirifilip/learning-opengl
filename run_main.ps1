$OUT_DIR = "out"
$ROOT_PATH = $PSScriptRoot

if (Test-Path "$OUT_DIR") {
    Remove-Item -Recurse "$OUT_DIR"
}

New-Item -ItemType Directory "$OUT_DIR"


g++ -Wall -Wextra -Werror `
    -L build/googletest-1.15.2/build/lib `
    -L build/glfw-3.4/build/src `
    -I build/googletest-1.15.2/googletest/include `
    -I build/googletest-1.15.2/googlemock/include `
    -I build/glfw-3.4/include `
    src/main.cpp `
    -o "$OUT_DIR/main.exe" `
    -l glfw3
     

if ($?) {
    . "$OUT_DIR/main.exe"
}