CC = g++
CFLAGS = -O3 -march=core2 -Wall -g
spider: spider.o
	$(CC) -o $@ $< -levent -lpthread
spider.o: spider.c bloom.h dns.h url.h http.h
clean: 
	-rm spider.o spider downpage/*
