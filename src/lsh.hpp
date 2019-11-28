#ifndef LSH_INCLUDED
#define LSH_INCLUDED

#include <vector>;
#include <unordered_map>
#include "hash.hpp"
#include "point.hpp"

template <std::size_t N, std::size_t L>
class LSH {
	private:
		using Points = std::vector<Point<N>>;
		using Region = std::unordered_map<unsigned long long, Points>;
		
		std::size_t numOfPlanes
		Region regions[L];
		Hash<N> hashes[L];

	public:
		LSH (std::size_t numOfPlanes, Points points) :
			numOfPlanes(numOfPlanes) {

				for (int i = 0; i < L; i++) {
					Hash<N> tempHash(numOfPlanes);
					hashes[i] = tempHash;
				}

				for (Point  point : points) {
					regions[hash(point)].emplace_back(point);
				}
			}

		Points kNN (Point point) {
			Points nns;

			for (Hash hash : hashes) { 
				//TODO: Correct union/intersection function
				nns = regions[hash(point)];
			}

			return nns;
		}
}

#endif
