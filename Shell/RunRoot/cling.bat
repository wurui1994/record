@echo off
REM bash -c "cling -std=c++14 -Dmain=%~n1 %1"
bash -c "cp %1 ~/tmp.cpp && cling -std=c++14 -Dmain=tmp ~/tmp.cpp"
REM powershell -Command "(gps bash).Kill()"
REM exit
REM bash -c 'root -q -l -b  %1 -e "main()"'