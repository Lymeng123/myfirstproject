#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include "domino.h"

class dominoset
{
public :
	dominoset(int maxVal = 6){
		for (int i = 0; i <= maxVal; ++i){
			for (int j = i; j <= maxVal; ++j) {
				tiles.emplace_back(i, j);
			}
		}
	}
	void shuffle() {
		std::random_device rd;       // 1. True random number generator
		std::mt19937 g(rd());        // 2. Initialize Mersenne Twister engine
		std::shuffle(tiles.begin(),   // 3. Shuffle algorithm
			tiles.end(),
			g);
	}
	domino draw() {
		domino tile = tiles.back();  // 1. Get last element
		tiles.pop_back();            // 2. Remove it
		return tile;                 // 3. Return the tile
	}
	bool isEmpty() const {
		return tiles.empty();
	}
private:
	std::vector<domino> tiles;
};

