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

#ifndef MATMUL_H_
#define MATMUL_H_

#include <stddef.h>
#ifdef WITH_MKL
#include <mkl.h>
#endif

#ifdef USE_INT // maybe somebody need it
typedef size_t data_t;
#else
typedef double data_t;
#endif

void matmul_init();
void matmul_set_num_threads(size_t count);
void matmul_fini();

/*
 * Multiplies matrices with simple and/or strassen algorithms
 */
void matmul_matmul(size_t heightA, size_t widthA, size_t widthB,
		data_t *A, size_t rstrideA,
		data_t *B, size_t rstrideB,
		data_t *C, size_t rstrideC);

void matmul_simple(size_t heightA, size_t widthA, size_t widthB,
		data_t *A, size_t rstrideA,
		data_t *B, size_t rstrideB,
		data_t *C, size_t rstrideC);

void matmul_strassen(size_t heightA, size_t widthA, size_t widthB,
		data_t *A, size_t rstrideA,
		data_t *B, size_t rstrideB,
		data_t *C, size_t rstrideC);

#ifdef WITH_MKL
void matmul_mkl(size_t heightA, size_t widthA, size_t widthB,
		data_t *A, size_t rstrideA,
		data_t *B, size_t rstrideB,
		data_t *C, size_t rstrideC);
#endif

#endif /* MATMUL_H_ */
