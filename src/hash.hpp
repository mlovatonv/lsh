#ifndef HASH_INCLUDED
#define HASH_INCLUDED

#include <iostream>
#include <numeric>
#include "point.hpp"
#include "random.hpp"

template <std::size_t N>
class Hash {
	private:
		using Plane = std::vector<int>;
		using HashedStr = unsigned long long;

		int numOfPlanes;
		std::vector<Plane> planes;

	public:
		Hash(int dimensions, int numOfPlanes) : 
			dimensions(dimensions), numOfPlanes(numOfPlanes) {
				planes.resize(numOfPlanes);
				Random rd(-2500, 2500);

				for (Plane plane : planes) {
					for (int j = 0; j < dimensions; j++) {
						int x = rd();
						std::cout<<x<<" ";
						plane.push_back(x);
					}
					std::cout << std::endl;
				}
			}

		HashedStr operator()(Point p) {
			HashedStr hashedPoint = 0;

			for (Plane plane : planes) {
				hashedPoint <<= 1;
				if (compare(p, plane)) {
					hashedPoint++; 
				}
				std::cout << hashedPoint << std::endl;
			}

			return hashedPoint;
		}

		bool compare (Point &point, Plane &plane) {
			long long z = 0;

			for (std::size_t i = 0; i < N; i++) {
				z += plane[i]*point[i];
			}

			return z > 0;
		}
};

#endif
