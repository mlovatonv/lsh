#ifndef HASH_INCLUDED
#define HASH_INCLUDED

#include <random>
#include "point.hpp"

template <std::size_t N>
class Hash {
	private:
		using Plane = std::vector<double>;
		using HashedStr = unsigned long long;

		int numOfPlanes = -1;
		std::vector<Plane> planes;

	public:
		Hash() = default;

		Hash(int numOfPlanes) : numOfPlanes(numOfPlanes) {
			planes.resize(numOfPlanes);
			std::random_device rd;

			for (int i = 0; i < numOfPlanes; i++) {
				for (int j = 0; j < N; j++) {
					planes[i].emplace_back(rd()%2);
				}
			}
		}

		HashedStr operator()(const Point<N> &p) const {
			HashedStr hashedPoint = 0;

			for (Plane plane : planes) {
				hashedPoint <<= 1;
				if (compare(p, plane)) {
					hashedPoint++; 
				}
			}

			return hashedPoint;
		}

		bool compare (const Point<N> &point, const Plane &plane) const {
			double z = 0;

			for (std::size_t i = 0; i < N; i++) {
				if (plane[i]) {
					z += point[i];
				}
				else {
					z -= point[i];
				}
			}

			return z > 0;
		}
};

#endif
