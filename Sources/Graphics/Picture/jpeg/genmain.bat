gcc -pg -g ShowJPEG.c -luser32 -lgdi32 -ljpeg -o main.exe
main.exe >nul
gprof -p -q -A -z main.exe > prof.txt
gprof2dot prof.txt  -n0 -e0 -s -o prof.dot
dot prof.dot -Tpdf -o main.pdf
main.pdf
pause