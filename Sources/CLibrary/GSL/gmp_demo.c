//tcc -lmpir -run gmptest.c
#include <stdio.h> //hello world 工程默认的，如果你建立的是空工程就不需要这句
#include <gmp.h>//记得引入GMP.H的头文件
// #pragma comment(lib,"mpir")
int main(int argc, char* argv[])
{
	mpz_t t; //mpz_t 为GMP内置大数类型
	mpz_init(t); //大数t使用前要进行初始化，以便动态分配空间
	mpz_ui_pow_ui(t, 2, 1000); //GMP所有函数基本都是以mpz打头
	gmp_printf("2^100=%Zd\n", t); //输出大数，大数的格式化标志为%Zd
	mpz_clear(t);
	return 0;
}