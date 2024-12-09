$OUT_DIR = "out"

g++ -Wall -Wextra -Werror `
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