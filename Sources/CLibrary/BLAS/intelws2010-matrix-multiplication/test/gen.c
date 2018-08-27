/*
 * Matrices generator
 *
 * This file is a part of solution of a Intel Winter Summer School problem
 *
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
#include <time.h>

#ifdef USE_INT
static const char *input_format="%ld";
typedef size_t data_t;
#else
static const char *input_format="%lf";
typedef double data_t;
#endif
static const char *size_format="%llu";

static void save_test_case(const char *path, size_t height, size_t width) {
	FILE *stream = fopen(path, "w");

	fprintf(stream, size_format, height);
	fputc(' ', stream);
	fprintf(stream, size_format, width);
	fputc(' ', stream);

	size_t i;
	for(i=0; i < height * width; i++) {
		// fill with nonsense data
		data_t value = (double) rand();
		fprintf(stream, input_format, value);
		fputc(' ', stream);
	}

	fclose(stream);
}



int main(int argc, char *argv[]) {
	if(argc != 4) {
		printf("Usage: ./me height width out.file\n");
		exit(1);
	}

	srand(time(NULL));
	size_t height = atol(argv[1]);
	size_t width = atol(argv[2]);

	char *path = argv[3];
	save_test_case(path, height, width);

	return 0;
}

