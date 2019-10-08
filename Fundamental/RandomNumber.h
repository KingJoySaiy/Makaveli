#ifndef INC_233_RANDOMNUMBER_H
#define INC_233_RANDOMNUMBER_H

#include <climits>
#include <ctime>

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

#undef mult
#undef add

#endif //INC_233_RANDOMNUMBER_H
