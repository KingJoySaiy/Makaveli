#ifndef INC_233_RANDOMNUMBER_H
#define INC_233_RANDOMNUMBER_H

typedef unsigned long long ull;
typedef unsigned short us;

class RandomNumber {
private:
	ull randSeed;
public:
	RandomNumber(ull randSeed) : randSeed(randSeed) {}
	us Random(ull n) {
		
	}
	double fRandom();
};

#endif //INC_233_RANDOMNUMBER_H
