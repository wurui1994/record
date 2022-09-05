

%{
	#include <stdio.h>  /* For printf, etc. */
	#include <math.h>   /* For pow, used in the grammar. */
	/* Function type. */
	typedef double (func_t) (double);
	/* Data type for links in the chain of symbols. */
	struct symrec
	{
		char *name;  /* name of symbol */
		int type;    /* type of symbol: either VAR or FUN */
		union
		{
			double var;    /* value of a VAR */
			func_t *fun;   /* value of a FUN */
		} value;
		struct symrec *next;  /* link field */
	};

	typedef struct symrec symrec;

	/* The symbol table: a chain of 'struct symrec'. */
	extern symrec *sym_table;

	symrec *putsym (char const *name, int sym_type);
	symrec *getsym (char const *name);

	int yylex (void);
	void yyerror (char const *);
%}


%define api.value.type union /* Generate YYSTYPE from these types: */
%token <double>  NUM     /* Double precision number. */
%token <symrec*> VAR FUN /* Symbol table pointer: variable/function. */
%nterm <double>  exp

%precedence '='
%left '-' '+'
%left '*' '/'
%precedence NEG /* negation--unary minus */
%right '^'      /* exponentiation */


%% /* The grammar follows. */

input:
  %empty
| input line
;


line:
  '\n'
| exp '\n'   { printf ("%.10g\n", $1); }
| error '\n' { yyerrok;                }
;


exp:
  NUM
| VAR                { $$ = $1->value.var;              }
| VAR '=' exp        { $$ = $3; $1->value.var = $3;     }
| FUN '(' exp ')'    { $$ = $1->value.fun ($3);         }
| exp '+' exp        { $$ = $1 + $3;                    }
| exp '-' exp        { $$ = $1 - $3;                    }
| exp '*' exp        { $$ = $1 * $3;                    }
| exp '/' exp        { $$ = $1 / $3;                    }
| '-' exp  %prec NEG { $$ = -$2;                        }
| exp '^' exp        { $$ = pow ($1, $3);               }
| '(' exp ')'        { $$ = $2;                         }
;

/* End of grammar. */
%%

struct init
{
  char const *name;
  func_t *fun;
};


struct init const funs[] =
{
  { "atan", atan },
  { "cos",  cos  },
  { "exp",  exp  },
  { "ln",   log  },
  { "sin",  sin  },
  { "sqrt", sqrt },
  { 0, 0 },
};


/* The symbol table: a chain of 'struct symrec'. */
symrec *sym_table;


/* Put functions in table. */
static void
init_table (void)
{
  for (int i = 0; funs[i].name; i++)
    {
      symrec *ptr = putsym (funs[i].name, FUN);
      ptr->value.fun = funs[i].fun;
    }
}



/* The mfcalc code assumes that malloc and realloc
   always succeed, and that integer calculations
   never overflow.  Production-quality code should
   not make these assumptions.  */
#include <assert.h>
#include <stdlib.h> /* malloc, realloc. */
#include <string.h> /* strlen. */


symrec *
putsym (char const *name, int sym_type)
{
  symrec *res = (symrec *) malloc (sizeof (symrec));
  res->name = strdup (name);
  res->type = sym_type;
  res->value.var = 0; /* Set value to 0 even if fun. */
  res->next = sym_table;
  sym_table = res;
  return res;
}


symrec *
getsym (char const *name)
{
  for (symrec *p = sym_table; p; p = p->next)
    if (strcmp (p->name, name) == 0)
      return p;
  return NULL;
}

#include <ctype.h>
#include <stddef.h>

int
yylex (void)
{
  int c = getchar ();

  /* Ignore white space, get first nonwhite character. */
  while (c == ' ' || c == '\t')
    c = getchar ();

  if (c == EOF)
    return YYEOF;


  /* Char starts a number => parse the number. */
  if (c == '.' || isdigit (c))
    {
      ungetc (c, stdin);
      if (scanf ("%lf", &yylval.NUM) != 1)
        abort ();
      return NUM;
    }


  /* Char starts an identifier => read the name. */
  if (isalpha (c))
    {
      static ptrdiff_t bufsize = 0;
      static char *symbuf = 0;

      ptrdiff_t i = 0;
      do

        {
          /* If buffer is full, make it bigger. */
          if (bufsize <= i)
            {
              bufsize = 2 * bufsize + 40;
              symbuf = realloc (symbuf, (size_t) bufsize);
            }
          /* Add this character to the buffer. */
          symbuf[i++] = (char) c;
          /* Get another character. */
          c = getchar ();
        }

      while (isalnum (c));

      ungetc (c, stdin);
      symbuf[i] = '\0';


      symrec *s = getsym (symbuf);
      if (!s)
        s = putsym (symbuf, VAR);
      yylval.VAR = s; /* or yylval.FUN = s. */
      return s->type;
    }

  /* Any other character is a token by itself. */
  return c;
}



/* Called by yyparse on error. */
void yyerror (char const *s)
{
  fprintf (stderr, "%s\n", s);
}


int main (int argc, char const* argv[])
{
  init_table ();
  return yyparse ();
}