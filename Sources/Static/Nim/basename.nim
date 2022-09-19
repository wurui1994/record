import std/[os]
let filePath = "tests/test1.org"
var (dir, basename, ext) = splitFile(filePath)
echo "dir = ", dir
echo "basename = ", basename
echo "ext = ", ext