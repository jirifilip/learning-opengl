$OUT_DIR = "out"
$ROOT_PATH = $PSScriptRoot

if (Test-Path "$OUT_DIR") {
    Remove-Item -Recurse "$OUT_DIR"
}

New-Item -ItemType Directory "$OUT_DIR"


g++ -I build/stb* -c src/stb_image.cpp -o "$OUT_DIR/stb_image.a"

g++ -Wall -Wextra -Werror `
    -L $OUT_DIR `
    -L build/googletest-1.15.2/build/lib `
    -L build/glfw-3.4/build/src `
    -L build/freeglut-3.6.0/build/lib `
    -I build/googletest-1.15.2/googletest/include `
    -I build/googletest-1.15.2/googlemock/include `
    -I build/glfw-3.4/include `
    -I build/freeglut-3.6.0/include `
    -I build/glad/include `
    -I build/glad/src `
    -I build/stb* `
    tests/test_main.cpp `
    -o "$OUT_DIR/test_main.exe" `
    -l glfw3 `
    -l freeglut `
    -l gtest `
    -l gmock `
    -l gtest_main `
    -l:stb_image.a `
    -lgdi32
     

if ($?) {
    . "$OUT_DIR/test_main.exe"
}