#ifndef PARSER_H
#define PARSER_H

#include <string.h>
#include <stdio.h>
#include <ctype.h>

#include "drawbmp.h"

#define w 500
#define h 500

#define MAX_STR_LEN 100
#define EXPR_SIZE 100
#define VECTOR_LEN 100

typedef struct tagSplitedStrings
{
	int n;
	char *s[MAX_STR_LEN];
} SplitedStrings;

//
typedef struct tagScalarExpr
{
	char str[32];
	double value;
} ScalarExpr;

ScalarExpr scalarexpr[EXPR_SIZE];

typedef struct tagVectorExpr
{
	char str[32];
	int length;
	double value[VECTOR_LEN];
} VectorExpr;

VectorExpr vectorexpr[EXPR_SIZE];

int g_index = 0;

SplitedStrings split()
{
	int count = 0;
	char str[MAX_STR_LEN];
	SplitedStrings ds;
	char *s = str;
	char *p;
	gets(str);
	while (1)
	{
		p = strtok(s, ",");
		if (p == NULL)
			break;
		ds.s[count] = p;
		//puts(p);
		s = NULL;
		count++;
	}
	ds.n = count;
	return ds;
}
void show(SplitedStrings ds)
{
	for (int i = 0; i < ds.n; i++)
	{
		puts(ds.s[i]);
	}
}

void print(char *str)
{
	for (int i = 0; i < EXPR_SIZE; i++)
	{
		if (!strcmp(str, scalarexpr[i].str))
			printf("%s: %lf\n", str, scalarexpr[i].value);
	}
}
void printv(char *str)
{
	//printf("%s", str);
	for (int i = 0; i < EXPR_SIZE; i++)
	{
		if (!strcmp(str, vectorexpr[i].str))
		{
			printf("%s:[ ", str);
			for (int j = 0; j < vectorexpr[i].length; j++)
				printf("%lf ", vectorexpr[i].value[j]);
			printf("]\n");
		}
	}
}
double getvalue(char *str)
{
	double r;
	for (int i = 0; i < EXPR_SIZE; i++)
	{
		if (!strcmp(str, scalarexpr[i].str))
			r = scalarexpr[i].value;
	}
	return r;
}
void avoidrepeat(char *str)
{
	for (int i = 0; i < EXPR_SIZE; i++)
	{
		if (!strcmp(str, scalarexpr[i].str))
			return;
	}
	g_index++;
}
void drawbmp(SplitedStrings ds)
{
	//绘图部分
	//puts(ds.s[0]);
	if (!strcmp(ds.s[0], "cls"))
		system("cls");
	if (!strcmp(ds.s[0], "clear"))
		initbmp(w, h);
	if (!strcmp(ds.s[0], "bgcolor"))
		SetBgColor(atoi(ds.s[1]), atoi(ds.s[2]), atoi(ds.s[3]));
	if (!strcmp(ds.s[0], "color"))
		SetColor(atoi(ds.s[1]), atoi(ds.s[2]), atoi(ds.s[3]));
	if (!strcmp(ds.s[0], "origin"))
		SetOrigin(atoi(ds.s[1]), atoi(ds.s[2]));
	if (!strcmp(ds.s[0], "scale"))
		SetScale(atof(ds.s[1]), atof(ds.s[2]));
	if (!strcmp(ds.s[0], "line"))
		DDALine(atoi(ds.s[1]), atoi(ds.s[2]), atoi(ds.s[3]), atoi(ds.s[4]));
	if (!strcmp(ds.s[0], "triangle"))
		Triangle(atoi(ds.s[1]), atoi(ds.s[2]), atoi(ds.s[3]), atoi(ds.s[4]), atoi(ds.s[5]), atoi(ds.s[6]));
	if (!strcmp(ds.s[0], "filltriangle"))
		FillTriangle(atoi(ds.s[1]), atoi(ds.s[2]), atoi(ds.s[3]), atoi(ds.s[4]), atoi(ds.s[5]), atoi(ds.s[6]));
	if (!strcmp(ds.s[0], "rect"))
		Rect(atoi(ds.s[1]), atoi(ds.s[2]), atoi(ds.s[3]), atoi(ds.s[4]));
	if (!strcmp(ds.s[0], "fillrect"))
		FillRect(atoi(ds.s[1]), atoi(ds.s[2]), atoi(ds.s[3]), atoi(ds.s[4]));
	if (!strcmp(ds.s[0], "circle"))
		MidCircle(atoi(ds.s[1]), atoi(ds.s[2]), atoi(ds.s[3]));
	if (!strcmp(ds.s[0], "fillcircle"))
		FillCircle(atoi(ds.s[1]), atoi(ds.s[2]), atoi(ds.s[3]));
	if (!strcmp(ds.s[0], "arc"))
		Arc(atoi(ds.s[1]), atoi(ds.s[2]), atoi(ds.s[3]), atoi(ds.s[4]), atoi(ds.s[5]), atoi(ds.s[6]));
	if (!strcmp(ds.s[0], "fillarc"))
		FillArc(atoi(ds.s[1]), atoi(ds.s[2]), atoi(ds.s[3]), atoi(ds.s[4]), atoi(ds.s[5]), atoi(ds.s[6]));
	if (!strcmp(ds.s[0], "littleletter"))
		littleletter(ds.s[1][0]);
	//计算部分
	//scalar
	if (!strcmp(ds.s[1], "=") || !strcmp(ds.s[1], "equal"))
		strcpy(scalarexpr[g_index].str, ds.s[0]), scalarexpr[g_index].value = atof(ds.s[2]), g_index++;
	if (!strcmp(ds.s[0], "print"))
		print(ds.s[1]);
	//plus
	if (!strcmp(ds.s[1], "+") || !strcmp(ds.s[1], "plus"))
	{
		double a, b;
		strcpy(scalarexpr[g_index].str, ds.s[0]);
		if (ds.s[2][0] >= '0' && ds.s[2][0] <= '9')
			a = atof(ds.s[2]);
		else
			a = getvalue(ds.s[2]);
		if (ds.s[3][0] >= '0' && ds.s[3][0] <= '9')
			b = atof(ds.s[3]);
		else
			b = getvalue(ds.s[3]);
		//printf("%lf %lf", a, b);
		scalarexpr[g_index].value = a + b;
		avoidrepeat(scalarexpr[g_index].str);
	}
	//sub
	if (!strcmp(ds.s[1], "-") || !strcmp(ds.s[1], "sub"))
	{
		double a, b;
		strcpy(scalarexpr[g_index].str, ds.s[0]);
		if (ds.s[2][0] >= '0' && ds.s[2][0] <= '9')
			a = atof(ds.s[2]);
		else
			a = getvalue(ds.s[2]);
		if (ds.s[3][0] >= '0' && ds.s[3][0] <= '9')
			b = atof(ds.s[3]);
		else
			b = getvalue(ds.s[3]);
		//printf("%lf %lf", a, b);
		scalarexpr[g_index].value = a - b;
		avoidrepeat(scalarexpr[g_index].str);
	}
	//mul
	if (!strcmp(ds.s[1], "*") || !strcmp(ds.s[1], "mul"))
	{
		double a, b;
		strcpy(scalarexpr[g_index].str, ds.s[0]);
		if (ds.s[2][0] >= '0' && ds.s[2][0] <= '9')
			a = atof(ds.s[2]);
		else
			a = getvalue(ds.s[2]);
		if (ds.s[3][0] >= '0' && ds.s[3][0] <= '9')
			b = atof(ds.s[3]);
		else
			b = getvalue(ds.s[3]);
		//printf("%lf %lf", a, b);
		scalarexpr[g_index].value = a * b;
		avoidrepeat(scalarexpr[g_index].str);
	}
	//div
	if (!strcmp(ds.s[1], "/") || !strcmp(ds.s[1], "div"))
	{
		double a, b;
		strcpy(scalarexpr[g_index].str, ds.s[0]);
		if (ds.s[2][0] >= '0' && ds.s[2][0] <= '9')
			a = atof(ds.s[2]);
		else
			a = getvalue(ds.s[2]);
		if (ds.s[3][0] >= '0' && ds.s[3][0] <= '9')
			b = atof(ds.s[3]);
		else
			b = getvalue(ds.s[3]);
		//printf("%lf %lf", a, b);
		scalarexpr[g_index].value = a / b;
		avoidrepeat(scalarexpr[g_index].str);
	}
	//pow
	if (!strcmp(ds.s[1], "^") || !strcmp(ds.s[1], "pow"))
	{
		double a, b, c;
		strcpy(scalarexpr[g_index].str, ds.s[0]);
		if (isdigit(ds.s[2][0]) || ds.s[2][0] == '-')
			a = atof(ds.s[2]);
		else
			a = getvalue(ds.s[2]);
		if (isdigit(ds.s[3][0]) || ds.s[2][0] == '-')
			b = atof(ds.s[3]);
		else
			b = getvalue(ds.s[3]);
		//printf("%lf %lf", a, b);
		c = pow(a, b);
		scalarexpr[g_index].value = c;
		avoidrepeat(scalarexpr[g_index].str);
	}
	//vector
	if (!strcmp(ds.s[1], "v=") || !strcmp(ds.s[1], "vequal"))
	{
		strcpy(vectorexpr[g_index].str, ds.s[0]);
		for (int i = 2; i < ds.n; i++)
		{
			vectorexpr[g_index].value[i - 2] = atof(ds.s[i]);
		}
		//printf("%lf\n", vectorexpr[index].value[0]);
		vectorexpr[g_index].length = ds.n - 2;
		g_index++;
	}
	//
	if (!strcmp(ds.s[0], "printv"))
		printv(ds.s[1]);
	//linespace
	if (!strcmp(ds.s[1], ":") || !strcmp(ds.s[1], "linspace"))
	{
	};
}
#endif //PARSER_H