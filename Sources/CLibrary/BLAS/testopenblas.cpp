//N=7500阶，dgemm耗时90.325000 seconds
//N=7500阶，sgemm耗时55.952999 seconds 
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <openblas/cblas.h>

#pragma comment(lib,"openblas.lib")
int main()
{
	const enum CBLAS_ORDER Order = CblasRowMajor;
	const enum CBLAS_TRANSPOSE TransA = CblasNoTrans;
	const enum CBLAS_TRANSPOSE TransB = CblasNoTrans;
	const int M = 5000;//A的行数，C的行数
	const int N = 5000;//B的列数，C的列数
	const int K = 5000;//A的列数，B的行数
	const double alpha = 1;
	const double beta = 0;
	const int lda = K;//A的列
	const int ldb = N;//B的列
	const int ldc = N;//C的列
	double *A = new double[M*K];// = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6 };
	double *B = new double[K*N];// = { 5, 4, 3, 2, 1, 0 };
	double *C = new double[M*N];
	for (int i = 0; i < M*K; i++)A[i] = double(rand() / (RAND_MAX + 1.0));
	for (int i = 0; i < K*N; i++)A[i] = double(rand() / (RAND_MAX + 1.0));
	int st = clock();
	cblas_dgemm(Order, TransA, TransB, M, N, K, alpha, A, lda, B, ldb, beta, C, ldc);
	int et = clock();
	printf("%lf seconds fininhed", double(et - st) / CLOCKS_PER_SEC);
	return EXIT_SUCCESS;
}