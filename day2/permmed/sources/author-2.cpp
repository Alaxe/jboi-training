//Author: Alexander Crustev
#include <cstdio>
#include <cinttypes>

const uint32_t MAX_N = 1e5 + 12;

uint32_t possib[2 * MAX_N];

uint32_t numCnt;
uint32_t nums[MAX_N];

uint32_t targMed;
uint32_t medInd;

void input() {
	scanf("%u %u", &numCnt, &targMed);
	for (uint32_t i = 0;i < numCnt;i++) {
		scanf("%u", &nums[i]);
	}
}

void calc_med_ind() {
	for (uint32_t i = 0;i < numCnt;i++) {
		if (nums[i] == targMed) {
			medInd = i;
			break;
		}
	}
}

void calc_possib() {
	possib[MAX_N] = 1;

	uint32_t ls = 0;
	uint32_t gr = 0;

	for (uint32_t i = 0;i < medInd;i++) {
		if (nums[i] > targMed) {
			gr++;
		} else if (nums[i] < targMed) {
			ls++;
		}

		possib[MAX_N + gr - ls]++;
	}
}

uint64_t calc_ans() {
	uint64_t ans = 0;

	uint32_t ls = 0;
	uint32_t gr = 0;

	for (uint32_t i = 0;i < numCnt;i++) {
		if (nums[i] > targMed) {
			gr++;
		} else if (nums[i] < targMed) {
			ls++;
		}
		if (i >= medInd) {
			ans += possib[MAX_N + gr - ls];
		}
	}
	return ans;
}

int main() {
	input();
	calc_med_ind();
	calc_possib();
	printf("%" PRIu64 "\n", calc_ans());

}
