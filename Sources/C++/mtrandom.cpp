#ifndef mtrandom_HPP_
#define mtrandom_HPP_

class mtrandom{
public:
	mtrandom() : left(1) { init(); }
	explicit mtrandom(size_t seed) : left(1) { init(seed); }
	mtrandom(size_t* init_key, int key_length) : left(1){
		int i = 1, j = 0;
		int k = N > key_length ? N : key_length;
		init();
		for (; k; --k){
			state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * 1664525UL)) + init_key[j] + j; // non linear

			state[i] &= 4294967295UL; // for WORDSIZE > 32 machines
			++i; ++j;
			if (i >= N){
				state[0] = state[N - 1];
				i = 1;
			}
			if (j >= key_length)
				j = 0;
		}
		for (k = N - 1; k; --k){
			state[i] = (state[i] ^ ((state[i - 1] ^ (state[i - 1] >> 30)) * 1566083941UL)) - i; // non linear
			state[i] &= 4294967295UL; // for WORDSIZE > 32 machines
			++i;
			if (i >= N){
				state[0] = state[N - 1];
				i = 1;
			}
		}
		state[0] = 2147483648UL; // MSB is 1; assuring non-zero initial array
	}
	void reset(size_t rs){
		init(rs);
		next_state();
	}
	size_t rand(){
		size_t y;
		if (0 == --left)
			next_state();
		y = *next++;
		// Tempering
		y ^= (y >> 11);
		y ^= (y << 7) & 0x9d2c5680UL;
		y ^= (y << 15) & 0xefc60000UL;
		y ^= (y >> 18);
		return y;
	}
	double real()    { return (double)rand() / (0 - 1UL); }
	// generates a random number on [0,1) with 53-bit resolution
	double res53(){
		size_t a = rand() >> 5, b = rand() >> 6;
		return (a * 67108864.0 + b) / 9007199254740992.0;
	}

private:
	void init(size_t seed = 19650218UL){
		state[0] = seed & 4294967295UL;
		for (int j = 1; j < N; ++j){
			state[j] = (1812433253UL * (state[j - 1] ^ (state[j - 1] >> 30)) + j);
			// See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier.
			// In the previous versions, MSBs of the seed affect
			// only MSBs of the array state[].
			// 2002/01/09 modified by Makoto Matsumoto
		state[j] &= 4294967295UL;  // for >32 bit machines
		}
	}
	void next_state(){
		size_t* p = state;
		int i;
		for (i = N - M + 1; --i; ++p)
			*p = (p[M] ^ twist(p[0], p[1]));
		for (i = M; --i; ++p)
			*p = (p[M - N] ^ twist(p[0], p[1]));
		*p = p[M - N] ^ twist(p[0], state[0]);
		left = N;
		next = state;
	}
	size_t mixbits(size_t u, size_t v) const{
		return (u & 2147483648UL) | (v & 2147483647UL);
	}
	size_t twist(size_t u, size_t v) const{
		return ((mixbits(u, v) >> 1) ^ (v & 1UL ? 2567483615UL : 0UL));
	}
	static const int N = 624, M = 397;
	size_t state[N];
	size_t left;
	size_t* next;
};
class mtrand_help{
	static mtrandom r;
public:
	mtrand_help() {}
	void operator()(size_t s) { r.reset(s); }
	size_t operator()() const { return r.rand(); }
	double operator()(double) { return r.real(); }
};
mtrandom mtrand_help::r;
extern void mtsrand(size_t s) { mtrand_help()(s); }
extern size_t mtirand() { return mtrand_help()(); }
extern double mtdrand() { return mtrand_help()(1.0); }

#endif // mtrandom_HPP_


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#define N 1000000
//mitrand()产生随机数的范围为0-42亿。
//为了与标准库rand()的21亿比较，做减半处理。
int randi(){
	return mtirand() / 2;
}
int main()
{
	for (int i = 0; i < 10; i++)
		printf("%d ", rand()%10);
	printf("\n");
	for (int i = 0; i < 10; i++)
		printf("%d ", randi() % 10);
	printf("\n");
	//mtrandom mtr = mtrandom();
	//mtr.rand();
	int i, a, b, count1 = 0,count2=0;
	for (i = 1; i <= N; i++){
		a = rand() / 2;
		b = rand() / 2;
		if (a == b)count1++;
	}
	printf("In %d times,std random clone %d times.\n",N,count1);
	for (i = 1; i <= N; i++){
		a =randi()/2;
		b =randi()/2;
		if (a == b)count2++;
	}
	printf("In %d times,mt random clone %d times.\n",N,count2);
	return 0;
}
