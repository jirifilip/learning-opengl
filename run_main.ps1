$OUT_DIR = "out"
$ROOT_PATH = $PSScriptRoot

if (Test-Path "$OUT_DIR") {
    Remove-Item -Recurse "$OUT_DIR"
}

New-Item -ItemType Directory "$OUT_DIR"


g++ -Wall -Wextra -Werror `
    -L build/glfw-3.4/build/src `
    -L build/freeglut-3.6.0/build/lib `
    -I build/glfw-3.4/include `
    -I build/freeglut-3.6.0/include `
    -I build/glad/include `
    -I build/glad/src `
    -I build/stb* `
    src/main.cpp `
    -o "$OUT_DIR/main.exe" `
    -l glfw3 `
    -l freeglut `
    -lgdi32
     

if ($?) {
    . "$OUT_DIR/main.exe"
}