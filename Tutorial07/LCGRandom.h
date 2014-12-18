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
		unsigned int a = random(state);
		return ((float)a)/MAX_LCG_RAND;

	}

	uint64_t
		ranhash(uint64_t v) {
			v *= 3935559000370003845LL;
			v += 2691343689449507681LL;
			v ^= v >> 21; v ^= v << 37; v ^= v >> 4;
			v *= 4768777513237032717LL;
			v ^= v << 20; v ^= v >> 41; v ^= v << 5;
			return v;
		}

	double
		ranhashdoub(uint64_t v) {
			return 5.42101086242752217E-20 * ranhash(v);
		}
};
