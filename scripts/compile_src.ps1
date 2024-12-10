$OUT_DIR = "out"
$ROOT_PATH = $PSScriptRoot

if (Test-Path "$OUT_DIR") {
    Remove-Item -Recurse "$OUT_DIR"
}

New-Item -ItemType Directory "$OUT_DIR"


g++ -c src/stb_image.cpp -o "$OUT_DIR/stb_image.a"
g++ -c -Wall -Wextra -Werror build/glad/src/glad.c  -o "$OUT_DIR/glad.a"

g++ -c -Wall -Wextra -Werror src/main.cpp  -o "$OUT_DIR/main.a" 
g++ -c -Wall -Wextra -Werror src/utils.cpp  -o "$OUT_DIR/utils.a" 
g++ -c -Wall -Wextra -Werror src/shader.cpp  -o "$OUT_DIR/shader.a" 
g++ -c -Wall -Wextra -Werror src/shader_program.cpp  -o "$OUT_DIR/shader_program.a" 
