#include <random>

class Random {
	private:
		long long lb;
		long long ub;
		std::random_device rd;

	public:
		Random (long long lb, long long ub) :
			lb(lb), ub(ub) {}
		
		long long operator ()() {
			return (rd() % (ub - lb)) - lb;
		}
};
