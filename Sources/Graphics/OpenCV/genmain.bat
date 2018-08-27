REM g++ -pg -g %1 -o main.exe `pkg-config --libs opencv`
main.exe 1-16041P91P6.jpg>nul
gprof -p -q -A main.exe > prof.txt
gprof2dot prof.txt -n0 -e0 -s -o prof.dot
dot prof.dot -Tpdf -o main.pdf
main.pdf
pause