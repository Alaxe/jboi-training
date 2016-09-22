//Author: Alexander Crustev
#include <cstdio>
#include <cinttypes>

const uint32_t MAX_N = 1001;
const uint32_t MAX_C = 10002;

const uint32_t MOD = 1e9 + 7;

int64_t possib[MAX_N][MAX_C];

void calc_possib() {
	possib[0][0] = 1;
	for (uint32_t i = 1;i < MAX_N;i++) {
		int64_t curPossib = 0;
		for (uint32_t j = 0;j < MAX_C;j++) {
			curPossib += possib[i - 1][j];
			if (j >= i) {
				curPossib -= possib[i - 1][j - i];
			}
			curPossib %= MOD;
			if (curPossib < 0) {
				curPossib += MOD;
			}

			possib[i][j] = curPossib;
		}
	}
}

int main() {
	calc_possib();
	uint32_t n, c;
	scanf("%u %u", &n, &c);
	printf("%" PRIi64 "\n", possib[n][c]);
}
