/*
 * Main program
 *
 * This file is a part of solution of a Intel Winter Summer School problem
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h> // gettimeofday
#include <omp.h>

#include "matmul.h"

#ifdef USE_INT
static const char *input_format="%ld";
#else
static const char *input_format="%lf";
#endif
static const char *size_format="%llu";

/*
 * Benchmark utlis
 */
struct timeval start_time;
static void bench_start() {
	gettimeofday(&start_time, NULL);
}

static void bench_end() {
	struct timeval end_time;
	gettimeofday(&end_time,  NULL);

	double delta = (double) end_time.tv_sec - start_time.tv_sec;
	delta += (end_time.tv_usec - start_time.tv_usec) * 1e-6;

	printf("%0.4f seconds\n", delta);
}

/*
 * Reads matrix from file
 */
static data_t *read_matrix_r(const char *path, size_t *out_height, size_t *out_width) {
	FILE *f = fopen(path, "r");

	size_t height = 0;
	size_t width = 0;

	fscanf(f, size_format, &height);
	fscanf(f, size_format, &width);

	data_t *M = (data_t *) malloc(sizeof(data_t) * height * width);
	data_t *v = M;
	data_t *end = M + height * width;

	while(!feof(f) && v < end) {
		fscanf(f, input_format, v++);
	}

	fclose(f);

	*out_height = height;
	*out_width = width;

	return M;
}

/*
 * Writes result to file
 */
static void save_result(const char *path, data_t value, size_t max_i,
		size_t max_j) {

	FILE *f = fopen(path, "w");
	fprintf(f, input_format, value);
	fputc(' ', f);
	fprintf(f, size_format, max_i);
	fputc(' ', f);
	fprintf(f, size_format, max_j);
	fputc('\n', f);

	fclose(f);
}

/*
 * Solve WinterSchool 2010 problem ( max{A x B} )
 */
static data_t ws_problem(size_t heightA, size_t widthA, size_t widthB,
		data_t *A, data_t *B, size_t *out_max_i, size_t *out_max_j) {

	data_t *R = (data_t *) malloc(sizeof(data_t) * heightA * widthB);

#ifdef WITH_MKL
	bench_start();
	// use MKL
	matmul_mkl(heightA, widthA, widthB, A, widthA, B, widthB, R, widthB);
#else
	// use internal algorithm (strassen and/or three-loop)
	matmul_matmul(heightA, widthA, widthB, A, widthA, B, widthB, R, widthB);
#endif
	printf("Multiplication: ");
	bench_end();

	bench_start();
	data_t *max = R;
#pragma omp parallel for default(none) shared(R, max, heightA, widthB)
	for(size_t i = 0; i < heightA; i++) {
		data_t *start = R + i * widthB;
		data_t *end = start + widthB;
		data_t *local_max = start++;

		for(; start < end; start++) {
			if(*start > *local_max)
				local_max = start;
		}

#pragma omp critical
		{
		if(*local_max > *max )
			max = local_max;
		}
	}

/*	// faster, but complicated and not tested yet
	int max_threads = omp_get_max_threads();
	data_t **max_arr = (data_t **) malloc(sizeof(data_t*) * max_threads);

	printf("Max threads: %d", max_threads);

	data_t **max_arr_it = max_arr;
	data_t **max_arr_end = max_arr + max_threads;

	for(; max_arr_it < max_arr_end; max_arr_it++)
		*max_arr_it = R;

#pragma omp parallel for shared(max_arr)
	for(size_t i =0; i < heightA; i++) {
		data_t *start = R + i * widthB;
		data_t *end = start + widthB;
		data_t *local_max = start++;

		for(; start < end; start++) {
			if(*start > *local_max)
				local_max = start;
		}

		data_t **global_max_p = max_arr + omp_get_thread_num();
		if(*local_max > **global_max_p )
			*global_max_p = local_max;
	}

	data_t *max = *max_arr;
	for (max_arr_it = max_arr + 1; max_arr_it < max_arr_end; max_arr_it++) {
		//printf("Max: %lf\n", **max_arr_it);
		if (**max_arr_it > *max)
			max = *max_arr_it;
	}

	free(max_arr);
*/

	size_t max_i = (max - R) / widthB;
	size_t max_j = (max - R) % widthB;

	printf("Problem: ");
	bench_end();

	if(out_max_i != NULL)
		*out_max_i = max_i;
	if(out_max_j != NULL)
		*out_max_j = max_j;


	return *max;
}

/*
 * Prints usage information
 */
static void usage() {
	printf("Usage: ./me matrixA.file matrixB.file out.file\n");
}

/*
 * Entry point
 */
int main(int argc, char *argv[]) {
	if (argc != 4) {
		usage();
		exit(1);
	}
	matmul_init();
	int rc =0;

	char *pathA = argv[1];
	char *pathB = argv[2];
	char *pathR = argv[3];

	data_t *A;
	size_t heightA;
	size_t widthA;

	data_t *B;
	size_t heightB;
	size_t widthB;

	bench_start();
	// there is no sense to parallel disk IO
	A = read_matrix_r(pathA, &heightA, &widthA);
	if(NULL == A)
		goto quit;

	B = read_matrix_r(pathB, &heightB, &widthB);
	if(NULL == B)
		goto quit_A;

	if(widthA != heightB) {
		// what did you want to do?
		fprintf(stderr, "Invalid input!\n");
		goto quit_B;
	}
	printf("IO: ");
	bench_end();

	size_t max_i;
	size_t max_j;
	data_t max_value;

	max_value = ws_problem(heightA, widthA, widthB, A, B, &max_i, &max_j);

	save_result(pathR, max_value, max_i, max_j);

quit_B:
	free(B);
quit_A:
	free(A);
quit:
	matmul_fini();
	return rc;
}


