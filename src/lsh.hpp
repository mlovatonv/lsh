#ifndef LSH_INCLUDED
#define LSH_INCLUDED

#include <vector>
#include <unordered_map>
#include <utility>
#include "hash.hpp"
#include "boundedPQueue.h"
#include "point.hpp"

template <std::size_t N, std::size_t L, typename ElemType>
class LSH {
	private:
		using Points = std::vector<std::pair<Point<N>, ElemType>>;
		using Region = std::unordered_map<unsigned long long, Points>;
		
		std::size_t numOfPlanes;
		Region regions[L];
		Hash<N> hashes[L];

	public:
		LSH (std::size_t numOfPlanes, Points &points) :
			numOfPlanes(numOfPlanes) {

				for (int i = 0; i < L; i++) {
					Hash<N> tempHash(numOfPlanes);
					hashes[i] = tempHash;
				}

				for (std::pair<Point<N>, ElemType> p : points) {
					for (int i = 0; i < L; i++) {
						regions[i][hashes[i](p.first)].push_back(p);
					}
				}
			}

		ElemType kNNValue (const Point<N> &point, double k) const {
			BoundedPQueue<ElemType> pQueue(k);

			for (int i = 0; i < L; i++) { 
				unsigned long long hashedPoint = hashes[i](point);
				auto it = regions[i].find(hashedPoint);
				if (it == regions[i].end()) {
					continue;
				}

				Points hashNNs = it->second;
				for (std::pair<Point<N>, ElemType> p : hashNNs) {
					pQueue.enqueue(p.second, Distance(point, p.first));
				}
			}

			std::unordered_map<ElemType, int> counter;
			while (!pQueue.empty()) {
				counter[pQueue.dequeueMin()]++;
			}

			ElemType mxElem;
			int mxCount = -1;
			for (auto p : counter){
				if (p.second > mxCount) {
					mxElem = p.first;
					mxCount = p.second;
				}
			}

			return mxElem;
		}

		bool contains(const Point<N> &point) const {
			unsigned long long hashedPoint = hashes[0](point);
			auto it = regions[0].find(hashedPoint);

			if (it == regions[0].end()) {
				return false;
			}

			for (std::pair<Point<N>, ElemType> p : it->second) {
				if (p.first == point) { 
					return true;
				}
			}

			return false;
		}
};

#endif
