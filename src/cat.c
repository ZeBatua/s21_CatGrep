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
    find_f = getopt_long(ARGC, ARGV, "benstET", long_options, &option_index);
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

void s21_cat (char* ARGV[]) {
    FILE *file = NULL;
    file = fopen(*ARGV, "r");

    if (file == NULL) { //кароче  у меня косяк когда подаешь --- и в если в иначе
        fprintf(stderr, "s21_cat: %s: No such file or 12345678directory\n", *ARGV);
    } else {
        int count_line = 1;
        int empty_lines = -1;
        char read_char = '\0';
        char last = '\n';
        while ((read_char = fgetc(file)) != EOF) {
            if ((flags.b_flag != 1 && flags.n_flag == 1 && last == '\n') ||
                (flags.b_flag == 1 && read_char != '\n' && last == '\n')) {
                fprintf(stdout, "%6d\t", count_line++);
            }
            if (flags.e_flag == 1 && read_char == '\n') {
                fprintf(stdout, "%c", '$');
            }
            if (flags.s_flag == 1 && read_char == '\n') {
                if (empty_lines >= 1) {
                    continue;
                }
                empty_lines++;
            } else {
                empty_lines = -1;
            }
            if (flags.t_flag == 1 && read_char == '\t') {
                fprintf(stdout, "^I");
                continue;
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
            fprintf(stdout, "%c", read_char);
            last = read_char;
        }        
    }
    fclose(file);
}

int main(int ARGC, char *ARGV[]) {  //  подается  s21_cat -l test.txt
    int error = 0;
    int flags_num = 0;
    for (int i = 0; i < ARGC; i++){
        error = getFlags(ARGC, ARGV);
        if (error == -1) {
            continue;
        } else if (error == '?') {
            exit(0);
        } else {
            flags_num++;
        }
    }
    for (int i = 1 + flags_num; i < ARGC; i++) {
        s21_cat(&ARGV[i]);
    }
    return 0; // 0 если все ок, 1 если произошла любая ошибка

}