@copy %1 %~dp0main.cpp 1>NUL
@root -q -l -b -n %~dp0main.cpp 2>NUL | findstr /V /R "^$" | findstr /V /R "Processing" | findstr /V /R "(int)"