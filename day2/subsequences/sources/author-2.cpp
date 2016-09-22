//Author Alexander Crustev
#include <cstdio>
#include <cinttypes>
#include <cstring>

const uint32_t MAX_N = 102;
const uint32_t MAX_M = 102;
const uint32_t MAX_D = 1002;

const uint32_t MOD = 1e9 + 7;

uint64_t possib[MAX_M][MAX_D];
int32_t nums[MAX_N];
uint32_t numCnt;

uint32_t pickCnt;
uint32_t div;

uint64_t solve() {
	memset(possib, 0, sizeof(possib));
	possib[0][0] = 1;

	for (uint32_t i = 0;i < numCnt;i++) {
		for (uint32_t j = pickCnt;j > 0;j--) {
			for (uint32_t k = 0;k < div;k++) {
				int32_t t = (k + nums[i]) % div;
				possib[j][t] += possib[j - 1][k];
				possib[j][t] %= MOD;
				//if (possib[j][k] Z>
				//printf("%u ", possib[j][k]);
			}
			//printf("\n");
		}
		//printf("\n\n");
	}
	
	return possib[pickCnt][0];
}

void input() {

	scanf("%u %u %u", &numCnt, &pickCnt, &div);
	for (uint32_t i = 0;i < numCnt;i++) {
		scanf("%i", &nums[i]);
	}
}

int main () {
	input();
	printf("%" PRIu64 "\n", solve());
}

