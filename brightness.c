#include <stdio.h>

int main(int argc, char *argv[]) {

	int val, inc;
	char c;

	if (argc != 2) {
		printf("brightness: usage: \"brightness {0, 1, 2, 3, 4, 5, 6, 7, +, -}\"\n");
		return 1;
	} else if (argv[1][1] != '\0') {
		printf("brightness: usage: \"brightness {0, 1, 2, 3, 4, 5, 6, 7, +, -}\"\n");
		return 1;
	} else {
		switch (c=*argv[1]) {
			case '0':
			case '1':
			case '2':
			case '3': /* for *argv[1] = {0, 1, 2, 3, 4, 5, 6, 7} */
			case '4':
			case '5':
			case '6':
			case '7': val = c - '0'; inc = 0; break;
			case '+': val = 0; inc = 1; break;
			case '-': val = 0; inc =-1; break;
			default: printf("brightness: usage: \"brightness {0, 1, 2, 3, 4, 5, 6, 7, +, -}\"\n"); break;
		}
	}

	FILE *fp; /* fp = file pointer */
	int br_val;

	if ((fp = fopen("/sys/class/backlight/acpi_video0/brightness", "r")) == NULL) {
		printf("brightness: Could not open brightness file.\n");
		return 1;
	} else {
		fscanf(fp, "%d", &br_val);
		fclose(fp);

		int br_new = (inc==0) ? val : br_val + inc;
		if (br_new > 7) {
			printf("brightness: already max.\n");
		} else if (br_new < 0) {
			printf("brightness: already min.\n");
		}

		if ((fp = fopen("/sys/class/backlight/acpi_video0/brightness", "w")) == NULL) {
			printf("brightness: Could not open brightness file for writing.\n");
			return 1;
		} else {
			fprintf(fp, "%d", br_new);
			fclose(fp);
		}
	}
	return 0;
}
