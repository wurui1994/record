mkdir root\backup
REM
move bin root\backup\
move etc root\backup\
move lib root\backup\
move lib64 root\backup\
move sbin root\backup\
move usr root\backup\
move var root\backup\
REM
move root\root.x86_64\bin .
move root\root.x86_64\etc .
move root\root.x86_64\lib .
move root\root.x86_64\lib64 .
move root\root.x86_64\sbin .
move root\root.x86_64\usr .
move root\root.x86_64\var .