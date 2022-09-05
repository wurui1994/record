/* Reverse polish notation calculator.  */
%{
#define YYSTYPE double
#include <math.h>
#include <stdio.h>
int yylex(void);
void yyerror(char const *);
%}

%token NUM

%% /* Grammar rules and actions follow.  */
input : /* empty */
        | input line;

line : '\n' | exp '\n' { printf(" %.10g\n", $1); };

exp : NUM { $$ = $1; }
    | exp exp '+' { $$ = $1 + $2; }
    | exp exp '-' { $$ = $1 - $2; }
    | exp exp '*' { $$ = $1 * $2; }
    | exp exp '/' { $$ = $1 / $2; }
    | exp exp '^' { $$ = pow($1, $2); }
    | exp 'n' { $$ = -$1; };
%%

#include <ctype.h>

int yylex(void)
{
    int c;

    /* Skip white space.  */
    while ((c = getchar()) == ' ' || c == '\t')
        ;
    /* Process numbers.  */
    if (c == '.' || isdigit(c))
    {
        ungetc(c, stdin);
        scanf("%lf", &yylval);
        return NUM;
    }
    /* Return end-of-input.  */
    if (c == EOF)
        return 0;
    /* Return a single char.  */
    return c;
}

int main(void)
{
    return yyparse();
}

#include <stdio.h>

/* Called by yyparse on error.  */
void yyerror(char const *s)
{
    fprintf(stderr, "%s\n", s);
}