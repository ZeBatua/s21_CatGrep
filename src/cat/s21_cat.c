#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

struct flag {
  int b_flag;
  int e_flag;
  int n_flag;
  int s_flag;
  int t_flag;
  int v_flag;
} flags;

const struct option long_options[] = {
    {"number-nonblank", no_argument, NULL, 'b'},
    {"number", no_argument, NULL, 'n'},
    {"squeeze-blank", no_argument, NULL, 's'},
};

int getFlags(int ARGC, char* ARGV[]) {
    int find_f;
    int option_index = 0;
    find_f = getopt_long(ARGC, ARGV, "YbenstETv", long_options, &option_index);
    if (find_f != -1) {
        switch (find_f) {
            case 'b':
                flags.b_flag = 1;
                break;
            case 'e':
                flags.e_flag = 1;
                flags.v_flag = 1;
                break;
            case 'E':
                flags.e_flag = 1;
                break;
            case 'n':
                flags.n_flag = 1;
                break;
            case 's':
                flags.s_flag = 1;
                break;
            case 't':
                flags.t_flag = 1;
                flags.v_flag = 1;
                break;
            case 'T':
                flags.t_flag = 1;
                break;
            case '?':
                break;
        }
    }
    return find_f;
}

void s21_cat(char* ARGV[]) {
    FILE *file = NULL;
    file = fopen(*ARGV, "r");
    if (file == NULL) {
        fprintf(stderr, "s21_cat: %s: No such file or directory\n", *ARGV);
    } else {
        int count_line = 1;
        int empty_lines = 0;
        char read_char = '\0';
        char last = '\n';
        int counter_for_b = 0;
        int costil = 0;
        while ((read_char = fgetc(file)) != EOF) {
            if (flags.s_flag == 1 && read_char == '\n') {
                if (empty_lines >= 1) {
                    continue;
                }
                empty_lines++;
            } else {
                empty_lines = -1;
            }
            if ((flags.b_flag != 1 && flags.n_flag == 1 && last == '\n') || (flags.b_flag == 1 && read_char != '\n' && last == '\n')) {
                if (counter_for_b == 1) {
                } else {
                    fprintf(stdout, "%6d\t", count_line++);
                    counter_for_b++;
                }

            }
            if (flags.v_flag == 1 && read_char != '\t' && read_char != '\n') {
                if (read_char >= 32 && read_char <= 126) {
                    fprintf(stdout, "%c", read_char);
                    continue;
                } else {
                    fprintf(stdout, "^%c", read_char + 64);
                    continue;
                }
            }
            if (flags.e_flag == 1 && read_char == '\n') {
                fprintf(stdout, "%c", '$');
            }
            if (flags.t_flag == 1 && read_char == '\t') {
                fprintf(stdout, "^I");
                continue;
            }
            fprintf(stdout, "%c", read_char);
            last = read_char;
            counter_for_b = 0;
        }
    }
    fclose(file);
}


int main(int ARGC, char *ARGV[]) {
    int error = 0;
    int flags_num = 0;
    for (int i = 1; i < ARGC; i++){
        error = getFlags(ARGC, ARGV);
        if (error == -1) {
        } else if (error == '?') {
            exit(0);
        } else {
            flags_num++;
        }
    }
    int j = 0;
    for (j = 1 + flags_num; j < ARGC; j++) { 
        s21_cat(&ARGV[j]); // разобраться 
    }
    return 0; // 0 если все ок, 1 если произошла любая ошибка

}