gcc -O3 -pg -g peaks.c -lgdi32 -o main.exe
main.exe >nul
gprof -p -q -A -z main.exe > prof.txt
gprof2dot prof.txt  -o prof.dot
dot prof.dot -Tpdf -o main.pdf
main.pdf
pause