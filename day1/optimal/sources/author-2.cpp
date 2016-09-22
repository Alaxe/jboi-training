//Author: Alexander Crustev
#include <cstdio>
#include <cinttypes>
#include <algorithm>

struct City {
	uint32_t x, y;
	uint32_t population;
};

const uint32_t MAX_CITY = 1e6 + 12;
const uint64_t INF = 1ULL << (63 - 1);

City cities[MAX_CITY];
uint32_t cityCnt;

uint32_t w, h;

void input() {
	scanf("%u %u %u", &h, &w, &cityCnt);
	//printf("%u %u %u\n", h, w, cityCnt);
	for (uint32_t i = 0;i < cityCnt;i++) {
		scanf("%u %u %u", &cities[i].y, &cities[i].x, 
				&cities[i].population);
	}
}

uint64_t calc_x_dist() {
	std::sort(cities, cities + cityCnt, 
		[](const City &a, const City &b) -> bool {
			return a.x < b.x;		
		});

	uint64_t curDist = 0;
	uint64_t curRight = 0;
	uint64_t curLeft = 0;

	for (uint32_t i = 0;i < cityCnt;i++) {
		curDist += (uint64_t) cities[i].x * cities[i].population;
		curRight += cities[i].population;
	}

	uint64_t bestDist = INF;
	uint32_t cityInd = 0;
	for (uint32_t x = 1;x <= w;x++) {
		//printf("%" PRIu64 "\n", curDist);
		curDist += curLeft;
		curDist -= curRight;
		bestDist = std::min(curDist, bestDist);

		while ((cityInd < cityCnt) && (cities[cityInd].x == x)) {
			curLeft += cities[cityInd].population;
			curRight -= cities[cityInd].population;

			cityInd++;
		}
	}
	//printf("%" PRIu64 "\n", curDist);
	return bestDist;
}

void swap_x_y() {
	std::swap(w, h);
	for (uint32_t i = 0;i < cityCnt;i++) {
		std::swap(cities[i].x, cities[i].y);
	}
}

int main() {
	input();
	uint64_t xAns = calc_x_dist();
	swap_x_y();
	uint64_t yAns = calc_x_dist();

	printf("%" PRIu64 "\n", xAns + yAns);
}
