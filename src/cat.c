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
  int count = 0;
  if (ARGC > 1) {
    while (ARGV) {
      if (ARGV[count][0] == '-') break;
    }
  }

  return 0;
}
