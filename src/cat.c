#include "s21_cat.h"

int flags_status(flags *status) {
  status->b = 0;
  status->e = 0;
  status->E = 0;
  status->v = 0;
  status->n = 0;
  status->s = 0;
  status->T = 0;
  return 0;
}; 

int getFlags(flags *status, char f) {
  int error = 0;
  switch (f) {
    case 'b':
      status->b = 1;
      break;
    case 'e':
      status->e = 1;
      break;
    case 'E':
      status->E = 1;
      break;
    case 'v':
      status->v = 1;
      break;
    case 'n':
      status->n = 1;
      break;
    case 's':
      status->s = 1;
      break;
    case 't':
      status->t = 1;
      break;
    case 'T':
      status->T = 1;
      break;

    default:
      break;
  }
}

int main(int ARGC, char **ARGV) {  //  подается  s21_cat -l test.txt
  // int count = 0;
  // if (ARGC > 1) {
  //   while (ARGV) {
  //     if (ARGV[count][0] == '-') break;
  //   }
  // }

  // fscanf(f, "%s", c);

}


int flag_n() {
  FILE *f;
  char c[1000];
  int i = 1;
  f = fopen("test_file.txt", "r");
	while(!feof(f)) {
		if (fgets(c, 1000, f) != NULL) {
				if (c[0] == '\n') {
					printf("%8s", c);
				} else {
			printf("%6d%2s", i, c);
			i++;
			}
		}
	}
  fclose(f);
  return 0;
}

int flag_b() {
  FILE *f; 
  char c[1000];
  int i = 1;
  f = fopen("test_file.txt", "r");
	while(!feof(f)) {
		if (fgets(c, 1000, f) != NULL) {
			printf("%6d%2s", i, c);
			i++;
		}
	}
  fclose(f);
  return 0;
} 

int flag_s() {
  FILE *f;
  char c[1000];
  int count = 0;
  int double_print = 0;
  f = fopen("test_file.txt", "r");
	while(!feof(f)) {
		if (fgets(c, 1000, f) != NULL) {
			if (c[0] == '\n') {
				count++;
			}
			if (count == 2) {
				count = 1;
			} else {
				printf("%s", c);
				double_print++;
				if (double_print == 2) { 
					count = 0;
					double_print = 0;
				}
			}
		}
	}
  fclose(f);
  return 0;
}
