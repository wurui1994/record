%{
#include <stdio.h>
%}

%%
stop printf("Stop command received");
start printf("Start command received");
[0123456789]+ printf("NUMBER");
[a-zA-Z][a-zA-Z0-9]* printf("WORD");
%%