//Author: Alexander Crustev
#include <cstdio>
#include <cinttypes>

const uint32_t MAX_N = 1e5;

uint32_t nums[MAX_N];
uint32_t numCnt;
uint32_t targMed;

void input() {
	scanf("%u %u", &numCnt, &targMed);
	for (uint32_t i = 0;i < numCnt;i++) {
		scanf("%u", &nums[i]);
	}
}

int main() {
	input();
	uint32_t ans = 0;
	for (uint32_t i = 0;i < numCnt;i++) {
		uint32_t ls = 0;
		uint32_t gr = 0;
		uint32_t eq = 0;
		for (uint32_t j = i;j < numCnt;j++) {
			if (nums[j] > targMed) {
				gr++;
			} else if (nums[j] < targMed) {
				ls++;
			} else {
				eq++;
			}

			if ((ls == gr) && (eq > 0)) {
				ans++;
			}
		}
	}
	printf("%u\n", ans);
}
