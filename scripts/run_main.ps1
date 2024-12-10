$OUT_DIR = "out"

g++ $OUT_DIR/main.a `
    $OUT_DIR/utils.a `
    $OUT_DIR/shader.a `
    $OUT_DIR/shader_program.a `
    $OUT_DIR/glfw_handler.a `
    $OUT_DIR/glad.a `
    -o $OUT_DIR/main.exe `
    -l glfw3 -l freeglut -l gdi32 -l:stb_image.a

if ($?) {
    . "$OUT_DIR/main.exe"
}