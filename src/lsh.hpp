#ifndef LSH_INCLUDED
#define LSH_INCLUDED

#include <vector>;
#include <unordered_map>
#include "hash.hpp"
#include "point.hpp"

template <std::size_t N>
class LSH {
	private:
		using Points = std::vector<Point<N>>;
		using Region = std::unordered_map<unsigned long long, Points>;
			
		Points points;
		Region regions;
		std::vector<Hash<N>> hashes;

	public:
		LSH (int dimension,int numOfPlanes, Points points) :
			dimension(dimension), numOfPlanes(numOfPlanes) {

				for (int i = 0; i < N 

				for (std::size_t i = 0; i < N; i++) {
					regions[hash(point)].emplace_back(point);
				}
			}

		Points kNN (Point point) {
			return regions[hash(point)];
		}
}

#endif
