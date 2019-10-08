#ifndef INC_233_RANDOM_H
#define INC_233_RANDOM_H

#include <climits>
#include <ctime>
#include <iostream>

typedef unsigned long long ull;
typedef unsigned short us;

#define mult 1194211693
#define add 12345

class RandomNumber {
private:
	ull randSeed;
public:
	RandomNumber(ull s) {	//use user's seed
		randSeed = s;
	}
	RandomNumber() {	//default seed
		randSeed = time(0);
	}
	us Random(ull n) {	//return integral rand number range [0, n) 
		randSeed = mult * randSeed + add;
		return (randSeed >> 16) % n;
	}
	double fRandom() {	//return floating rand number range [0, 1)
		return Random(SHRT_MAX) / double(SHRT_MAX);
	}
};

void shuffle(int a[], int n) {	//shuffle the array
	
	for (int i = 0; i < n; i++) {
		std::swap(a[i], a[RandomNumber().Random(n - i) + i]);
	}
}

#undef mult
#undef add

#endif //INC_233_RANDOM_H
