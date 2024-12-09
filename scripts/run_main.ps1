$OUT_DIR = "out"

g++ $OUT_DIR/main.a -o $OUT_DIR/main.exe -l glfw3 -l freeglut -l gdi32 -l:stb_image.a

if ($?) {
    . "$OUT_DIR/main.exe"
}