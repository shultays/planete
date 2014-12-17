#define MAX_LCG_RAND 0x7FFFF

class LCGRandom{
	unsigned int seed;
public:
	LCGRandom(int seed)
	{
		setSeed(seed);
	}
	LCGRandom()
	{
		this->seed = 0;
	}
	void setSeed(unsigned int seed)
	{
		this->seed = seed&MAX_LCG_RAND;
	}
	unsigned int random(int state){
		const unsigned int a = 1103515245;
		const unsigned int c = 12345;
		const unsigned int m = 1u<<31;
		return (((a * state + c) % m)>>16) & MAX_LCG_RAND;
	}

	float randomFloat(int state){
		return ((float)random(state))/MAX_LCG_RAND;

	}

};
