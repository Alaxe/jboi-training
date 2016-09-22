//Author: Alexander Crustev
#include <cstdio>
#include <cinttypes>

uint32_t sciCnt, pCnt;

FILE *in, *sol, *out;

uint32_t min(uint32_t a, uint32_t b) {
	return b < a ? b : a;
}

uint32_t open_files(uint32_t argc, char **argv) {
	if (argc != 4) {
		fprintf(stdout, "0.0\nInvalid number of arguments\n");
		return 1;
	}
	in = fopen(argv[1], "r");
	sol = fopen(argv[2], "r");
	out = fopen(argv[3], "r");

	if ((in == nullptr) || (sol == nullptr) || (out == nullptr)) {
		fprintf(stdout, "0.0\nFailed opening files\n");
		return 1;
	} 

	return 0;
}

void close_files() {
	if (in != nullptr) {
		fclose(in);
	}
	if (sol != nullptr) {
		fclose(sol);
	}
	if (out != nullptr) {
		fclose(out);
	}
}

uint32_t read_input() {
	uint32_t meetingCnt;
	uint32_t read = fscanf(in, "%u %u %u", &pCnt, &meetingCnt, &sciCnt);

	if (read != 3) {
		fprintf(stdout, "0.0\nInvalid input file\n");
		return 1;
	} else {
		return 0;
	}
}

uint32_t grade() {
	uint32_t correctRows = 3;
	bool formatOK = true;
	
	if (feof(out)) {
		correctRows = 0;
	} else {
		for (uint32_t i = 0;i < sciCnt;i++) {
			uint32_t curSol, curOut;
			if (fscanf(sol, "%u", &curSol) != 1) {
				fprintf(stdout, "0.0\nInvalid sol file\n");
				return 1;
			}
			if (fscanf(out, "%u", &curOut) != 1) {
				correctRows = min(correctRows, 0);
				if (i != 0) {
					formatOK = false;
					correctRows = 0;
				}
				break;
			}
			if (curSol != curOut) {
				correctRows = 0;
			}
		}
	}

	if ((feof(out)) || (!formatOK)) {
		correctRows = min(correctRows, 1);
	} else {
		uint32_t solCnt, outCnt;
		if (fscanf(sol, "%u", &solCnt) != 1) {
			fprintf(stdout, "0.0\nInvalid sol file\n");
			return 1;
		}
		if (fscanf(out, "%u", &outCnt) != 1) {
			correctRows = min(correctRows, 1);
		} else if (outCnt > pCnt - sciCnt) {
			correctRows = min(correctRows, 1);
		} else if (solCnt != outCnt) {
			correctRows = min(correctRows, 1);
			for (uint32_t i = 0;i < outCnt;i++) {
				uint32_t curOut;
				if (fscanf(out, "%u", &curOut) != 1) {
					formatOK = false;
					correctRows = 0;
					break;
				}
			}
			for (uint32_t i = 0;i < solCnt;i++) {
				uint32_t curSol;
				if (fscanf(sol, "%u", &curSol) != 1) {
					fprintf(stdout, "0.0\nInvalid sol file\n");
					return 1;
				}
			}
		} else {
			for (uint32_t i = 0;i < outCnt;i++) {
				uint32_t curOut;
				uint32_t curSol;

				if (fscanf(out, "%u", &curOut) != 1) {
					formatOK = false;
					correctRows = 0;
					break;
				}
				if (fscanf(sol, "%u", &curSol) != 1) {
					fprintf(stdout, "0.0\nInvalid sol file\n");
					return 1;
				}

				if (curOut != curSol) {
					correctRows = 0;
				}
			}
		}
	}

	if ((feof(out)) || (!formatOK)) {
		correctRows = min(correctRows, 2);
	} else {
		for (uint32_t i = 0;i < sciCnt;i++) {
			uint32_t curSol, curOut;
			if (fscanf(sol, "%u", &curSol) != 1) {
				fprintf(stdout, "0.0\nInvalid sol file\n");
				return 1;
			}
			if (fscanf(out, "%u", &curOut) != 1) {
				correctRows = min(correctRows, 2);
				if (i != 0) {
					correctRows = 0;
					formatOK = false;
				}
				break;
			}
			if (curSol != curOut) {
				correctRows = 0;
			}
		}
	}

	if (!formatOK) {
		fprintf(stderr, "Output isn\'t formated correctly\n");
		fprintf(stdout, "0.0\n");
		return 0;
	}

	float score = 0.f;
	if ((pCnt <= 1000) && (correctRows != 3)) {
		correctRows = 0;
	}
	switch (correctRows) {
		case 0: score = 0; break;
		case 1: score = 0.2; break;
		case 2: score = 0.4; break;
		case 3: score = 1; break;
	}
	fprintf(stdout, "%f\n", score);

	if (correctRows == 0) {
		fprintf(stderr, "Output isn\'t correct\n");
	} else if (correctRows == 1) {
		fprintf(stderr, "First line is correct\n");
	} else if (correctRows == 2) {
		fprintf(stderr, "First two lines are correct\n");
	} else {
		fprintf(stderr, "Output is correct\n");
	}
	return 0;
}

int main(int argc, char **argv) {
	uint32_t ret = 0;
	if (open_files(argc, argv)) {
		ret = 1;
	} else if (read_input()) {
		ret = 1;
	} else if (grade()) {
		ret = 1;
	}
	close_files();
	return ret;
}
