#include <iostream>
#include <numeric>
#include <random>

class Hash {
	private:
		using vi = std::vector<int>;

		int d;
		int k;
		std::vector<vi> planes;

	public:
		Hash(int d, int k) : d(d), k(k) {

			planes.resize(k);
			std::random_device rd;

			for (int i = 0; i < k; i++) {
				for (int j = 0; j < d; j++) {
					int x = rd()%5000 - 2500;
					std::cout<<x<<" ";
					planes[i].push_back(x);
				}
				std::cout<<std::endl;
			}
		}

		long long operator()(vi p) {
			long long hashedPoint = 0;

			for (std::vector<int> plane : planes) {
				hashedPoint <<= 1;
				if (compare(p, plane)) {
					hashedPoint++; 
				}
			}

			return hashedPoint;
		}

		bool compare (vi &point, vi& plane) {
			long long ans = std::inner_product(point.begin(), point.end(), plane.begin(), 0);
			return ans > 0;
		}
};
