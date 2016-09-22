//Author: Alexander Crustev
#include <cstdio>
#include <cinttypes>
#include <utility>

const uint32_t MAX_N = 1e6 + 12;
const uint32_t INF = 1e9 + 7;

uint32_t sciCnt;
uint32_t pCnt;

uint32_t meetings[MAX_N][2];
uint32_t meetCnt;

void input() {
	scanf("%u %u %u", &pCnt, &meetCnt, &sciCnt);
	for (uint32_t i = 0;i < meetCnt;i++) {
		scanf("%u %u", &meetings[i][0], &meetings[i][1]);
		meetings[i][0]--;
		meetings[i][1]--;
		if (meetings[i][0] > meetings[i][1]) {
			std::swap(meetings[i][0], meetings[i][1]);
		}
	}

}

bool willBeHeard[MAX_N];
uint32_t inventT[MAX_N];

void calc_invent_t() {
	for (uint32_t i = 0;i < sciCnt;i++) {
		willBeHeard[i] = false;
	}
	for (uint32_t i = sciCnt;i < pCnt;i++) {
		willBeHeard[i] = true;
	}
	for (int32_t i = meetCnt - 1;i >= 0;i--) {
		uint32_t m1 = meetings[i][0];
		uint32_t m2 = meetings[i][1];

		bool &h1 = willBeHeard[m1];
		bool &h2 = willBeHeard[m2];

		if ((!h1) && (h2)) {
			inventT[m1] = i;
		}
		if ((h1) && (!h2)) {
			inventT[m2] = i;
		}

		h1 |= h2;
		h2 |= h1;
	}

	for (uint32_t i = 0;i < sciCnt;i++) {
		if (willBeHeard[i]) {
			printf("%u ", inventT[i] + 1);
		} else {
			printf("-1 ");
		}
	}
	printf("\n");
}

bool willHear[MAX_N];

void calc_will_hear() {
	for (uint32_t i = 0;i < pCnt;i++) {
		willHear[i] = false;
	}

	for (uint32_t i = 0;i < meetCnt;i++) {
		uint32_t m1 = meetings[i][0];
		uint32_t m2 = meetings[i][1];

		bool &h1 = willHear[m1];
		bool &h2 = willHear[m2];


		if ((m1 < sciCnt) && (inventT[m1] <= i)) {
			h1 = true;
		}
		if ((m2 < sciCnt) && (inventT[m2] <= i)) {
			h2 = true;
		}

		h1 |= h2;
		h2 |= h1;
	}

	uint32_t journalistLearnedCnt = 0;
	for (uint32_t i = sciCnt;i < pCnt;i++) {
		journalistLearnedCnt += willHear[i];
	}
	printf("%u ", journalistLearnedCnt);
	for (uint32_t i = sciCnt;i < pCnt;i++) {
		if (willHear[i]) {
			printf("%u ", i + 1);
		}
	}
	printf("\n");
}

uint32_t firstHeardBy[MAX_N];
uint32_t firstHeardAt[MAX_N];

uint32_t finalJournalist[MAX_N];

void calc_first_heard_by() {
	for (uint32_t i = 0;i < sciCnt;i++) {
		firstHeardAt[i] = firstHeardBy[i] = INF;
		finalJournalist[i] = INF;
	}

	for (int32_t i = meetCnt - 1;i >= 0;i--) {
		uint32_t m1 = meetings[i][0];
		uint32_t m2 = meetings[i][1];


		if (m1 >= sciCnt) {
			//printf("%u\n", m1);
			firstHeardBy[m1] = m1;
			firstHeardAt[m1] = i;
		}
		if (m2 >= sciCnt) {
			//printf("%u\n", m2);
			firstHeardBy[m2] = m2;
			firstHeardAt[m2] = i;
		}


		if (firstHeardAt[m1] < firstHeardAt[m2]) {
			firstHeardAt[m2] = firstHeardAt[m1];
			firstHeardBy[m2] = firstHeardBy[m1];
			if ((uint32_t) i == inventT[m2]) {
				finalJournalist[m2] = firstHeardBy[m1];
			}
		} else {
			firstHeardAt[m1] = firstHeardAt[m2];
			firstHeardBy[m1] = firstHeardBy[m2];

			if ((uint32_t) i == inventT[m1]) {
				finalJournalist[m1] = firstHeardBy[m2];
			}
		}
		//printf("(t: %u) %u: %u %u; %u: %u %u\n", i, m1, firstHeardAt[m1], firstHeardBy[m1],
				//m2, firstHeardAt[m1], firstHeardBy[m2]);
	}
	for (uint32_t i = 0;i < sciCnt;i++) {
		if (finalJournalist[i] < INF) {
			printf("%u ", finalJournalist[i] + 1);
		} else {
			printf("-1 ");
		}
	}
	printf("\n");
}

int main() {
	input();
	calc_invent_t();
	calc_will_hear();
	calc_first_heard_by();
}
