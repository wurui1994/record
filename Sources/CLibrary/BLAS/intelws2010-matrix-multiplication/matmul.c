/*
 * Matrices multiplication algorithms: a simple, strassen, and Intel BLAS
 *
 * This file is part of solution of a Intel Winter Summer School problem
 * Copyright (c) 2010 Roman Tsisyk <roman@tsisyk.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *    * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *    * Redistributions in binary form must reproduce the above
 * copyright notice, this list of conditions and the following disclaimer
 * in the documentation and/or other materials provided with the
 * distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include "matmul.h"

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

#include <omp.h>
#ifdef WITH_MKL
#include <mkl.h>
#endif

/*
 * TODO: malloc checks
 */

/*
 * We use strassen algorithm if product size less that kMinStrassen
 */
static const size_t kMinStrassen = 64L * 64L; // best on tested 2 x Xeon E5440

/*
 * TODO: use col-major arrays for B matrix, its may improve prefetching
 * TODO: replace at_r with inline functions
 * _r functions for row-major arrays
 */
#define at_r(M, i, j) (M + (i * rstride##M + j))
#define at_r_ref(M, i, j) (*at_r(M, i, j))

void matmul_init() {
#ifdef WITH_MKL
	mkl_set_dynamic(1);
#endif
	omp_set_dynamic(1);
}

void matmul_set_num_threads(size_t count) {
#ifdef WITH_MKL
	mkl_set_num_threads(count);
#endif
	omp_set_num_threads(count);
}

void matmul_fini() {
#ifdef WITH_MKL
    mkl_free_buffers();
#endif
}

/*
void matmul_debug_print(data_t *A, size_t rstrideA, size_t height, size_t width) {
	const data_t *end0 = A + height * rstrideA;

	for (; A < end0; A += rstrideA) {
		const data_t *end1 = A + width;
		data_t *a = A;

		for (; a < end1; a++) {
			printf("%d ", *a);
		}
		printf("\n");
	}
}
*/

inline void matmul_matmul(size_t heightA, size_t widthA, size_t widthB,
		data_t *A, size_t rstrideA,
		data_t *B, size_t rstrideB,
		data_t *C, size_t rstrideC) {

	// I dont want to use MKL here, please call directly matmul_mkl
	if(heightA * widthB < kMinStrassen)
		matmul_simple(heightA, widthA, widthB, A, rstrideA, B, rstrideB, C, rstrideC);
	else
		matmul_strassen(heightA, widthA, widthB, A, rstrideA, B, rstrideB, C, rstrideC);
}

/*
 * Sum of matrices
 */
static void matmul_add_r(data_t *A, size_t rstrideA, data_t *B, size_t rstrideB,
		data_t *R, size_t rstrideR, size_t height, size_t width) {
	const data_t *end0 = A + height * rstrideA;

	// its making no sense to parallelize here
	for (; A < end0; A += rstrideA, B += rstrideB, R += rstrideR) {
		const data_t *end1 = A + width;
		data_t *a = A;
		data_t *b = B;
		data_t *r = R;

		for (; a < end1; a++, b++, r++) {
			*r = *a + *b;
		}
	}
}


/*
 * Substraction of matrices
 */
static void matmul_sub_r(data_t *A, size_t rstrideA, data_t *B, size_t rstrideB,
		data_t *R, size_t rstrideR, size_t height, size_t width) {
	const data_t *end0 = A + height * rstrideA;

	// its making no sense to parallelize here
	for (; A < end0; A += rstrideA, B += rstrideB, R += rstrideR) {
		const data_t *end1 = A + width;
		data_t *a = A;
		data_t *b = B;
		data_t *r = R;

		for (; a < end1; a++, b++, r++) {
			*r = *a - *b;
		}
	}
}


/*
 * Strassen P1 helper
 * P = (A11 + A22) * (B11 + B22)
 */
static void matmul_strassen_P1 (size_t heightA, size_t widthA, size_t widthB,
		  data_t *A1,
		  data_t *A2,
		  size_t rstrideA,
		  data_t *B1,
		  data_t *B2,
		  size_t rstrideB,
		  data_t *P, size_t rstrideP)
{
	const size_t heightB = widthA;

	data_t *F = (data_t *) malloc(sizeof(data_t) * heightA * widthA);
	const size_t rstrideF = widthA;

	data_t *S = (data_t *) malloc(sizeof(data_t) * heightB * widthB);
	const size_t rstrideS = widthB;

#pragma omp parallel sections
	{
#pragma omp section
	matmul_add_r(A1, rstrideA, A2, rstrideA, F, rstrideF, heightA, widthA);
#pragma omp section
	matmul_add_r(B1, rstrideB, B2, rstrideB, S, rstrideS, heightB, widthB);
	}

	// start recursion here
	matmul_matmul(heightA, widthA, widthB, F, rstrideF, S, rstrideS, P,
			rstrideP);

	free(S);
	free(F);
}

/*
 * Strassen P2 and P5 helper
 * P = (A1 + A2) * B
 */
static void matmul_strassen_P2_P5 (size_t heightA, size_t widthA, size_t widthB,
		  data_t *A1,
		  data_t *A2,
		  size_t rstrideA,
		  data_t *B,
		  size_t rstrideB,
		  data_t *P, size_t rstrideP)
{
	data_t *F = (data_t *) malloc(sizeof(data_t) * heightA * widthA);
	const size_t rstrideF = widthA;

	matmul_add_r(A1, rstrideA, A2, rstrideA, F, rstrideF, heightA, widthA);

	// start recursion here
	matmul_matmul(heightA, widthA, widthB, F, rstrideF, B, rstrideB, P,
			rstrideP);

	free(F);
}

/*
 * Strassen P3 and P4 helper
 * P = A * (B1 - B2)
 */
static void matmul_strassen_P3_P4 (size_t heightA, size_t widthA, size_t widthB,
		  data_t *A,
		  size_t rstrideA,
		  data_t *B1,
		  data_t *B2,
		  size_t rstrideB,
		  data_t *P, size_t rstrideP)
{
	const size_t heightB = widthA;

	data_t *S = (data_t *) malloc(sizeof(data_t) * heightB * widthB);
	const size_t rstrideS = widthB;

	matmul_sub_r(B1, rstrideB, B2, rstrideB, S, rstrideS, heightB, widthB);

	// start recursion here
	matmul_matmul(heightA, widthA, widthB, A, rstrideA, S, rstrideS, P,
			rstrideP);

	free(S);
}

/*
 * Strassen P6 and P7 helper
 * P = (A1 - A2) * (B1 + B2)
 */
static void matmul_strassen_P6_P7 (size_t heightA, size_t widthA, size_t widthB,
		  data_t *A1,
		  data_t *A2,
		  size_t rstrideA,
		  data_t *B1,
		  data_t *B2,
		  size_t rstrideB,
		  data_t *P, size_t rstrideP)
{
	const size_t heightB = widthA;

	// Linux malloc is enough fast => not parallelize it below
	data_t *F = (data_t *) malloc(sizeof(data_t) * heightA * widthA);
	const size_t rstrideF = widthA;

	data_t *S = (data_t *) malloc(sizeof(data_t) * heightB * widthB);
	const size_t rstrideS = widthB;

#pragma omp parallel sections
	{
#pragma omp section
	matmul_sub_r(A1, rstrideA, A2, rstrideA, F, rstrideF, heightA, widthA);
#pragma omp section
	matmul_add_r(B1, rstrideB, B2, rstrideB, S, rstrideS, heightB, widthB);
	} // omp paralell sections

	// start recursion here
	matmul_matmul(heightA, widthA, widthB, F, rstrideF, S, rstrideS, P,
			rstrideP);

	free(S);
	free(F);
}


/*
 * Strassen C11 and C22 helper
 * C = ([P1=C] + P2) + (P3 - P4)
 */
static void matmul_strassen_C11_C22 (
		  data_t *P1,
		  size_t rstrideP1,
		  data_t *P2,
		  size_t rstrideP2,
		  data_t *P3,
		  size_t rstrideP3,
		  data_t *P4,
		  size_t rstrideP4,
		  size_t heightP, size_t widthP)
{
	data_t *S = (data_t *) malloc(sizeof(data_t) * heightP * widthP);
	const size_t rstrideS = widthP;

#pragma omp parallel sections
	{
#pragma omp section
	matmul_add_r(P1, rstrideP1, P2, rstrideP2, P1, rstrideP1, heightP, widthP);
#pragma omp section
	matmul_sub_r(P3, rstrideP3, P4, rstrideP4, S, rstrideS, heightP, widthP);
	}
	// sync
	matmul_add_r(P1, rstrideP1, S, rstrideS, P1, rstrideP1, heightP, widthP);

	free(S);
}

/*
 * Strassen C12 and C21 helper
 * C = [P1=C] + P2
 */
static void matmul_strassen_C12_C21 (
		  data_t *P1,
		  size_t rstrideP1,
		  data_t *P2,
		  size_t rstrideP2,
		  size_t heightP, size_t widthP)
{
	matmul_add_r(P1, rstrideP1, P2, rstrideP2, P1, rstrideP1, heightP, widthP);
}

static void matmul_strassen_fix_heightA_odd(size_t heightA, size_t widthA,
		size_t widthB, data_t *A, size_t rstrideA, data_t *B, size_t rstrideB,
		data_t *C, size_t rstrideC) {

	A += (heightA - 1) * rstrideA;
	C += (heightA - 1) * rstrideC;

	matmul_simple(1, widthA, widthB, A, rstrideA, B, rstrideB, C, rstrideC);
}


static void matmul_strassen_fix_widthB_odd(size_t heightA, size_t widthA, size_t widthB,
		data_t *A, size_t rstrideA,
		data_t *B, size_t rstrideB,
		data_t *C, size_t rstrideC) {

	B += (widthB - 1);
	C += (widthB - 1);

	// edge was fixed by fix_heightA
	heightA &= ~1;
	matmul_simple(heightA, widthA, 1, A, rstrideA, B, rstrideB, C, rstrideC);
}

static void matmul_strassen_fix_widthA_odd(size_t heightA, size_t widthA, size_t widthB,
		data_t *A, size_t rstrideA,
		data_t *B, size_t rstrideB,
		data_t *C, size_t rstrideC) {

	size_t i;
	size_t j;
	size_t k = widthA - 1;
	// edges were fixed by fix_heightA and fix_widthB
	heightA &= ~1;
	widthB &= ~1;

	// FIXME: replace at_h with pointers
#pragma omp parallel for
	for (i = 0; i < heightA; i++) {
		for (j = 0; j < widthB; j++) {
			at_r_ref(C, i, j) += at_r_ref(A, i, k) * at_r_ref(B, k, j);
		}
	}
}

/*
 * Strassen algorithm for multiplication
 * @see http://en.wikipedia.org/wiki/Strassen_algorithm
 */
void matmul_strassen(size_t heightA, size_t widthA, size_t widthB,
		data_t *A, size_t rstrideA,
		data_t *B, size_t rstrideB,
		data_t *C, size_t rstrideC) {

	/*
	 * divide matrices first
	 */
	const size_t heightAh = heightA >> 1;
	const size_t widthAh = widthA >> 1;
	const size_t heightBh = widthAh;
	const size_t widthBh = widthB >> 1;

	// A
	data_t *A11 = at_r(A, 0, 0);
	data_t *A12 = at_r(A, 0, widthAh);
	data_t *A21 = at_r(A, heightAh, 0);
	data_t *A22 = at_r(A, heightAh, widthAh);

	// B
	data_t *B11 = at_r(B, 0, 0);
	data_t *B12 = at_r(B, 0, widthBh);
	data_t *B21 = at_r(B, heightBh, 0);
	data_t *B22 = at_r(B, heightBh, widthBh);

	// C
	data_t *C11 = at_r(C, 0, 0);
	data_t *C12 = at_r(C, 0, widthBh);
	data_t *C21 = at_r(C, heightAh, 0);
	data_t *C22 = at_r(C, heightAh, widthBh);

	const size_t heightP = heightAh;
	const size_t widthP = widthBh;

	data_t *P1 = (data_t *) malloc(sizeof(data_t) * heightP * widthP);
	const size_t rstrideP1 = widthP;

	data_t *P2 = C21;
	const size_t rstrideP2 = rstrideC;

	data_t *P3 = (data_t *) malloc(sizeof(data_t) * heightP * widthP);
	const size_t rstrideP3 = widthP;

	data_t *P4 = (data_t *) malloc(sizeof(data_t) * heightP * widthP);
	const size_t rstrideP4 = widthP;

	data_t *P5 = C12;
	const size_t rstrideP5 = rstrideC;

	data_t *P6 = C22;
	const size_t rstrideP6 = rstrideC;

	data_t *P7 = C11;
	const size_t rstrideP7 = rstrideC;

#pragma omp parallel sections
	{
	// P1
#pragma omp section
	matmul_strassen_P1(heightAh, widthAh, widthBh, A11, A22, rstrideA, B11,
			B22, rstrideB, P1, rstrideP1);

	// P2, P5
#pragma omp section
	matmul_strassen_P2_P5(heightAh, widthAh, widthBh, A21, A22, rstrideA, B11,
			rstrideB, P2, rstrideP2);
#pragma omp section
	matmul_strassen_P2_P5(heightAh, widthAh, widthBh, A11, A12, rstrideA, B22,
			rstrideB, P5, rstrideP5);

	// P3, P4
#pragma omp section
	matmul_strassen_P3_P4(heightAh, widthAh, widthBh, A11, rstrideA, B12, B22,
			rstrideB, P3, rstrideP3);
#pragma omp section
	matmul_strassen_P3_P4(heightAh, widthAh, widthBh, A22, rstrideA, B21, B11,
			rstrideB, P4, rstrideP4);

	// P6, P7
#pragma omp section
	matmul_strassen_P6_P7(heightAh, widthAh, widthBh, A21, A11, rstrideA, B11,
			B12, rstrideB, P6, rstrideP6);
#pragma omp section
	matmul_strassen_P6_P7(heightAh, widthAh, widthBh, A12, A22, rstrideA, B21,
			B22, rstrideB, P7, rstrideP7);
	} // omp paralell sections

#pragma omp parallel sections
	{
#pragma omp section
	matmul_strassen_C11_C22( P7, rstrideP7, P1, rstrideP1, P4, rstrideP4, P5,
		rstrideP5, heightP, widthP);
#pragma omp section
	matmul_strassen_C11_C22( P6, rstrideP6, P1, rstrideP1, P3, rstrideP3, P2,
		rstrideP2, heightP, widthP);
	} // omp paralell sections

#pragma omp parallel sections
	{
#pragma omp section
	matmul_strassen_C12_C21(P5, rstrideP5, P3, rstrideP3, heightP, widthP);
#pragma omp section
	matmul_strassen_C12_C21(P2, rstrideP2, P4, rstrideP4, heightP, widthP);
	} // omp paralell sections

	/*
	 * Fix odd
	 */
#pragma omp parallel sections
	{
#pragma omp section
	if (heightA & 1) // heightA is odd
		matmul_strassen_fix_heightA_odd(heightA, widthA, widthB, A, rstrideA,
				B, rstrideB, C, rstrideC);

#pragma omp section
	if (widthB & 1) // widthB is odd
		matmul_strassen_fix_widthB_odd(heightA, widthA, widthB, A, rstrideA,
				B, rstrideB, C, rstrideC);

#pragma omp section
	if (widthA & 1) // widthA is odd
		matmul_strassen_fix_widthA_odd(heightA, widthA, widthB, A, rstrideA,
				B, rstrideB, C, rstrideC);
	} // omp paralell sections

	// sync
	free(P4);
	free(P3);
	free(P1);
}

/*
 * Simple, three-loop multiplication
 */
void matmul_simple(size_t heightA, size_t widthA, size_t widthB,
		data_t *A, size_t rstrideA,
		data_t *B, size_t rstrideB,
		data_t *C, size_t rstrideC) {

	size_t i;
	size_t j;
	size_t k;

#pragma omp parallel for
	for (i = 0; i < heightA; i++) {
		for (j = 0; j < widthB; j++) {
			data_t sum = 0;
/* unsafe, slowly, no sense
#pragma omp parallel for reduction(+:sum) */
			for(k = 0; k < widthA; k++) {
				sum += at_r_ref(A, i, k) * at_r_ref(B, k, j);
			}
			at_r_ref(C, i, j) = sum;
		}
	}
}

#ifdef WITH_MKL
#ifdef USE_INT
#error Not implemented yet
#endif
/*
 * MKL multiplication
 */
void matmul_mkl(size_t heightA, size_t widthA, size_t widthB,
		data_t *A, size_t rstrideA,
		data_t *B, size_t rstrideB,
		data_t *C, size_t rstrideC) {

	// C := alpha*op(A)*op(B) + beta*C
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans,
		heightA, widthB, widthA, 1.0,
		A, rstrideA, B, rstrideB, 0.0, C, rstrideC);
}
#endif

#undef at_r_ref
#undef at_r
