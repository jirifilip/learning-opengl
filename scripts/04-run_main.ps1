param(
    $MainName = "main"
)

$OUT_DIR = "out"

$librariesToLink = Get-ChildItem -Path $OUT_DIR | Where-Object { $_.Extension -eq ".a" } | ForEach-Object { $_.FullName }

g++ "$OUT_DIR/executable/$MainName.a" `
    @($librariesToLink) `
    -o "$OUT_DIR/executable/$MainName.exe" `
    -l glfw3 -l freeglut -l gdi32

if ($?) {
    . "$OUT_DIR/executable/$MainName.exe"
}