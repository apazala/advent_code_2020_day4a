#include <stdio.h>
#include <string.h>

char line[1024];

int fieldnamestree[26][26][26];

char fieldnames[7][4] = {
	"byr",
	"iyr",
	"eyr",
	"hgt",
	"hcl",
	"ecl",
	"pid"
};

void init() {
	for (int i = 0; i < 7; i++) {
		fieldnamestree[fieldnames[i][0] - 'a'][fieldnames[i][1] - 'a'][fieldnames[i][2] - 'a'] = 1;
	}
}

int main() {

	FILE *fin = fopen("input.txt", "r");
	if (!fin) {
		fprintf(stderr, "unable to open file\n");
		return 1;
	}

	init();

	int nvalid = 0;
	int count = 0;
	while (fgets(line, 1024, fin)) {
		if (line[0] == '\n') {//count and reset
			if (count >= 7)
				nvalid++;
			count = 0;
		}
		else {

			for (char *pcolon = strchr(line, ':'); pcolon; pcolon = strchr(pcolon + 1, ':')) {
				if (fieldnamestree[pcolon[-3] - 'a'][pcolon[-2] - 'a'][pcolon[-1] - 'a'])
					count++;
			}

		}
	}

	if (count >= 7) //last passport may not end with empty line
		nvalid++;

	printf("%d\n", nvalid);

	fclose(fin);
	return 0;
}