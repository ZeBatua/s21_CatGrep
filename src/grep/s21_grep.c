#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <regex.h>
#include <limits.h>
#include <string.h>

struct grep_flag {
    int e_flag;
    int i_flag;
    int v_flag;
    int c_flag;
    int l_flag;
    int n_flag;
    int h_flag;
    int s_flag;
    int f_flag;
    int o_flag;
} flag;

void find_flag(int ARGC, char **ARGV);
void cycle_output_string(int amount_str, char* string, char *fp, int count_file);
void s21_grep(char* filenames, char* pattern_names, int counter_pars_files);
void once_output_string(char* fp, int count_file, int same_str, int* er_counter);
void print_for_flag_o(char* fp, int count_file, char* string, char* p_pattern, char* pattern);
char pars_files(char **ARGV, char* filenames, int* counter_pars_files);
int pars_string(int ARGC, char **ARGV, int *mass);
char *eq_flag_status(char **ARGV, char *ch);
char pars_patterns(char* ARGV[], char* pattern_names, int* counter_pars_patterns);
void disable_once_flag(char *ch);

int main(int ARGC, char **ARGV) {
    if (ARGC > 2) {
        char filenames[4096] = {'\0'};
        char pattern_names[4096] = {'\0'};
        int  mass[1024] = {0};
        int counter_pars_patterns = 0;
        int counter_pars_files = 0;
        int amount_some_file = 0;

        find_flag(ARGC, ARGV);

        amount_some_file = pars_string(ARGC, ARGV, mass);

        for (int b = 0; b <= ARGC; b++) {
            if (mass[b] == 1) {
                pars_files(&ARGV[b], filenames, &counter_pars_files);
            }
        }
        for (int b = 0; b <= ARGC; b++) {
            if (mass[b] == 2 || mass[b] == 4) {
            pars_patterns(&ARGV[b], pattern_names, &counter_pars_patterns);
            }
        }
        s21_grep(filenames, pattern_names, amount_some_file);
    } else {
        fprintf(stderr, "Not enought arguments\n");
    }
    return 0;
}

char pars_patterns(char* ARGV[], char* pattern_names, int* counter_pars_patterns) {
        if (*counter_pars_patterns > 0) {
            strcat(pattern_names, "|");
        }
        strcat(pattern_names, *ARGV);
        *counter_pars_patterns+=1;
    return *pattern_names;
}

void s21_grep(char* filenames, char* pattern_names, int counter_pars_files) {
    char string[LINE_MAX];
    int amount_str = 0;
    int same_str = 0;
    int er_counter = 0;
    regex_t preg;
    regmatch_t pmatch[1] = {0};
    char pattern_for_f[4096] = {'\0'};
    char *fp = NULL;
    fp = strtok(filenames, "|");
    char cc[4097] = {'\0'};
    if (filenames[0] == '\0') {
    } else {
        while (fp != NULL) {
            same_str = 0;
            amount_str = 0;
            FILE *file;
            if ((file = fopen(fp, "r")) != NULL) {
                if (flag.f_flag == 1) {
                    char regfile[1024];
                    char *file = regfile;
                    file = fp;
                    FILE *f;
                    char str[4097] = {'\0'};
                    char *cc = str;
                    int e_counter = 0;
                    if ((f = fopen(file, "r")) != NULL) {
                        for (size_t j = 0; fgets(cc, 4096, f); j++) {
                            if (e_counter > 0) {
                                strcat(pattern_for_f, "|");
                            }
                            if (strchr(cc, '\n')) {
                                *(cc + strlen(cc) - 1) = '\0';
                            }
                            if (!strcmp(cc, "\0")) {
                                cc = "\n";
                            }
                            strcat(pattern_for_f, cc);
                            e_counter++;
                            memset(cc, '\0', 4096);
                        }
                        fclose(f);
                    } else {
                        fprintf(stderr, "s21_grep: %s: No such file or directory\n", file);
                    }
                }
                char* p_pattern = NULL;
                if (flag.f_flag != 1) {
                    if (flag.i_flag == 1) {
                        regcomp(&preg, pattern_names, REG_ICASE | REG_EXTENDED);
                    } else {
                        regcomp(&preg, pattern_names, REG_EXTENDED);
                        // printf("1||%s||\n", pattern_names);
                    }
                    p_pattern = pattern_names;
                } else {
                    if (flag.i_flag == 1) {
                        regcomp(&preg, pattern_for_f, REG_ICASE | REG_EXTENDED);
                    } else {
                        regcomp(&preg, pattern_for_f, REG_EXTENDED);
                    }
                    p_pattern = pattern_for_f;
                }
                if (flag.o_flag == 1) {
                    regexec(&preg, cc, 1, pmatch, 0);
                }
                while (fgets(string, LINE_MAX, file) != NULL) {
                    if (strrchr(string, '\n') == NULL) {
                        strcat(string, "\n");
                    }
                    if (flag.n_flag == 1) {
                        amount_str++;
                    }
                    if (flag.c_flag == 1 || flag.l_flag == 1) {
                        if (flag.v_flag == 1) {
                            if (regexec(&preg, string, 1, pmatch, 0) != 0) {
                                same_str++;
                            }
                        } else {
                            if (regexec(&preg, string, 1, pmatch, 0) == 0) {
                                same_str++;
                            }
                        }
                    } else {
                        if (flag.v_flag == 1) {
                            if (regexec(&preg, string, 1, pmatch, 0) != 0) {
                                cycle_output_string(amount_str, string, fp, counter_pars_files);
                            }
                        } else if (flag.f_flag == 1) {
                            if (regexec(&preg, string, 1, pmatch, 0) == 0) {
                                cycle_output_string(amount_str, string, fp, counter_pars_files);
                            }
                        } else if ((flag.o_flag != 1)) {
                            if (regexec(&preg, string, 0, NULL, 0) == 0) {
                                cycle_output_string(amount_str, string, fp, counter_pars_files);
                            }
                        }
                    }
                }
                fclose(file);
                print_for_flag_o(fp, counter_pars_files, string, p_pattern, pattern_names);
                once_output_string(fp, counter_pars_files, same_str, &er_counter);
                er_counter = 10;
            }
            regfree(&preg);
            fp = strtok(NULL, "|");
        }
    }
}

int pars_string(int ARGC, char **ARGV, int *mass) {
    int counter_for_mass = 1;
    int amount_file = 0;
    char ch[1024] = {'\0'};
    FILE *check;
    int counter_E = 0;
    char* e_check = "-e";
    char* f_check = "-f";
    int true_amount_file = 0;
    for (int i = 1; i < ARGC; i++) {  // 1 - файл, 2 - паттерн, 3 - флаг.
        if ((check = fopen(ARGV[i], "r")) == NULL) {
            if (ARGV[i] == NULL) {
            } else {
                if ((strcmp(ARGV[i - 1], e_check) == 0) &&
                (strcmp(ARGV[i], eq_flag_status(&ARGV[i], ch)) == 0) &&
                flag.e_flag == 1) {
                    disable_once_flag(ch);
                    mass[counter_for_mass] = 4;
                    counter_for_mass++;
                    counter_E++;
                    memset(ch, '\0', sizeof(ch));
                } else if ((strcmp(ARGV[i], e_check) == 0) && (ARGV[i + 1] == NULL)) {
                    fprintf(stderr, "grep: option requires an argument -- %s\n", &ARGV[i][1]);
                    exit(1);
                } else if ((strcmp(ARGV[i], f_check) == 0) && (ARGV[i + 1] == NULL)) {
                    fprintf(stderr, "grep: option requires an argument -- %s\n", &ARGV[i][1]);
                    exit(1);
                } else if (strcmp(ARGV[i - 1], "-e") == 0) {
                    mass[counter_for_mass] = 4;
                    counter_for_mass++;
                } else if ((strcmp(ARGV[i - 1], f_check) == 0) && (flag.f_flag == 1)) {
                    fprintf(stderr, "grep: %s: No such file or directory\n", ARGV[i]);
                    exit(1);
                } else if (strcmp(ARGV[i], eq_flag_status(&ARGV[i], ch)) == 0) {
                    mass[counter_for_mass] = 3;
                    counter_for_mass++;
                    memset(ch, '\0', sizeof(ch));
                } else if (ARGV[i - 1] == ARGV[0]) {
                    mass[counter_for_mass] = 2;
                    counter_for_mass++;
                } else if (strcmp(ARGV[i - 1], eq_flag_status(&ARGV[i - 1], ch)) == 0) {
                    mass[counter_for_mass] = 2;
                    counter_for_mass++;
                    memset(ch, '\0', sizeof(ch));
                } else {
                    if (flag.s_flag == 1) {
                    } else {
                        fprintf(stderr, "grep: %s: No such file or directory\n", ARGV[i]);
                    }
                    counter_for_mass++;
                    amount_file++;
                }
            }
        } else if (strcmp(ARGV[i - 1], "-e") == 0) {
            mass[counter_for_mass] = 2;
            counter_for_mass++;
            fclose(check);
        } else if (strcmp(ARGV[i - 1], "./s21_grep") == 0) {
            mass[counter_for_mass] = 2;
            counter_for_mass++;
            fclose(check);
        } else if (strcmp(ARGV[i - 1], f_check) == 0 && flag.f_flag == 1) {
            fclose(check);
            fprintf(stderr, "grep: %s: No such file or directory\n", ARGV[i]);
            exit(1);
        } else if (strcmp(ARGV[i - 1], eq_flag_status((&ARGV[i - 1]), ch)) == 0) {
            mass[counter_for_mass] = 1;
            counter_for_mass++;
            amount_file++;
            true_amount_file++;
            memset(ch, '\0', sizeof(ch));
            fclose(check);
        } else {
            mass[counter_for_mass] = 1;
            counter_for_mass++;
            amount_file++;
            true_amount_file++;
            fclose(check);
        }
    }
    if (counter_E > 0) {
        for (int t = 0; t != 1023; t++) {
            if (mass[t] == 2) {
                if (flag.s_flag != 1) {
                    fprintf(stderr, "grep: %s: No such file or directory\n", ARGV[t]);
                }
                mass[t] = 0;
                amount_file++;
            }
        }
    }
    if (amount_file == 0) {
        exit(1);
    }
    return amount_file;
}

void disable_once_flag(char *ch) {
    if (strcmp(&ch[0], "-")) {
        if (strcmp(&ch[1], "e") == 0) {
            flag.e_flag = 0;
        } else if (strcmp(&ch[1], "v") == 0) {
            flag.v_flag = 0;
        } else if (strcmp(&ch[1], "c") == 0) {
            flag.c_flag = 0;
        } else if (strcmp(&ch[1], "l") == 0) {
            flag.l_flag = 0;
        } else if (strcmp(&ch[1], "i") == 0) {
            flag.i_flag = 0;
        } else if (strcmp(&ch[1], "n") == 0) {
            flag.n_flag = 0;
        } else if (strcmp(&ch[1], "h") == 0) {
            flag.h_flag = 0;
        } else if (strcmp(&ch[1], "s") == 0) {
            flag.s_flag = 0;
        } else if (strcmp(&ch[1], "f") == 0) {
            flag.f_flag = 0;
        } else if (strcmp(&ch[1], "o") == 0) {
            flag.o_flag = 0;
        }
    }
}

char *eq_flag_status(char **ARGV, char *ch) {
    char buffer[1024] = {'\0'};
    char buffer2[1024] = {'\0'};
    strcat(buffer, ARGV[0]);
    memcpy(buffer2, buffer, 1);
    if (strlen(*ARGV) == 2) {
        if (strcmp(*ARGV, "-e") == 0) {
            strcat(ch, "-e");
        } else if (strcmp(*ARGV, "-i") == 0) {
            strcat(ch, "-i");
        } else if (strcmp(*ARGV, "-v") == 0) {
            strcat(ch, "-v");
        } else if (strcmp(*ARGV, "-c") == 0) {
            strcat(ch, "-c");
        } else if (strcmp(*ARGV, "-l") == 0) {
            strcat(ch, "-l");
        } else if (strcmp(*ARGV, "-n") == 0) {
            strcat(ch, "-n");
        } else if (strcmp(*ARGV, "-h") == 0) {
            strcat(ch, "-h");
        } else if (strcmp(*ARGV, "-s") == 0) {
            strcat(ch, "-s");
        } else if (strcmp(*ARGV, "-f") == 0) {
            strcat(ch, "-f");
        } else if (strcmp(*ARGV, "-o") == 0) {
            strcat(ch, "-o");
        } else {
            strcat(ch, "\0");
        }
    } else if (strlen(*ARGV) == 1) {
        strcat(ch, "\0");
    } else if (strcmp(buffer2, "-") == 0) {
        strcat(ch, *ARGV);
    }
    return ch;
}

char pars_files(char* ARGV[], char *filenames, int* counter_pars_files) {
        if (*counter_pars_files > 0) {
            strcat(filenames, "|");
        }
        strcat(filenames, *ARGV);
        *counter_pars_files+=1;
    return *filenames;
}

void find_flag(int ARGC, char **ARGV) {
    for (int i = 1; i < ARGC; i++) {
        if (ARGV[i][0] == '-') {
            if (ARGV[i][1] == '-') {
                fprintf(stderr, "grep: unrecognized option '--'\n");
                exit(1);
            } else {
                for (int j = 1; j < 3; j++) {
                    if (ARGV[i][j] == 'e') {
                        flag.e_flag = 1;
                    } else if (ARGV[i][j] == 'i') {
                        flag.i_flag = 1;
                    } else if (ARGV[i][j] == 'v') {
                        flag.v_flag = 1;
                    } else if (ARGV[i][j] == 'c') {
                        flag.c_flag = 1;
                    } else if (ARGV[i][j] == 'l') {
                        flag.l_flag = 1;
                    } else if (ARGV[i][j] == 'n') {
                        flag.n_flag = 1;
                    } else if (ARGV[i][j] == 'h') {
                        flag.h_flag = 1;
                    } else if (ARGV[i][j] == 's') {
                        flag.s_flag = 1;
                    } else if (ARGV[i][j] == 'f') {
                        flag.f_flag = 1;
                    } else if (ARGV[i][j] == 'o') {
                        flag.o_flag = 1;
                    }
                }
            }
        }
    }
}

void cycle_output_string(int amount_str, char* string, char* fp, int count_file) {
    if (count_file > 1) {
        if (flag.n_flag == 1 && flag.h_flag == 1) {
            fprintf(stdout, "%d:%s", amount_str, string);
        } else if (flag.h_flag == 1) {
            fprintf(stdout, "%s", string);
        } else if (flag.n_flag == 1 && flag.h_flag != 1) {
            fprintf(stdout, "%s:%d:%s", fp, amount_str, string);
        } else {
            fprintf(stdout, "%s:%s", fp, string);
        }
    } else {
        if (flag.n_flag == 1 && flag.h_flag == 1) {
            fprintf(stdout, "%d:%s", amount_str, string);
        } else if (flag.n_flag != 1 && flag.h_flag == 1) {
            fprintf(stdout, "%s", string);
        } else if (flag.n_flag == 1) {
            fprintf(stdout, "%d:%s", amount_str, string);
        } else {
            fprintf(stdout, "%s", string);
        }
    }
}

void once_output_string(char* fp, int count_file, int same_str, int* er_counter) {
    if (flag.c_flag == 1 && flag.l_flag != 1) {
        if (count_file > 1) {
            if (flag.h_flag == 1) {
                fprintf(stdout, "%d\n", same_str);
            } else {
                fprintf(stdout, "%s:%d\n", fp, same_str);
            }
        } else {
            fprintf(stdout, "%d\n", same_str);
        }
    } else if (flag.c_flag == 1 && flag.l_flag == 1) {
        if (count_file > 1) {
            if (same_str > 0) {
                same_str = 1;
            }
            if (flag.h_flag == 0) {
                if (*er_counter == 0) {
                    fprintf(stdout, "%s:%d\n%s\n", fp, same_str, fp);
                    *er_counter+=1;
                } else {
                    fprintf(stdout, "%s:%d\n", fp, same_str);
                }
            } else if (flag.h_flag == 1) {
                fprintf(stdout, "%d\n%s\n", same_str, fp);
            }
        } else {
            if (same_str > 0) {
                same_str = 1;
            }
            if (same_str > 0) {
                fprintf(stdout, "%d\n%s\n", same_str, fp);
            } else {
                fprintf(stdout, "%d\n", same_str);
            }
        }
    } else if (flag.l_flag == 1 && same_str > 0) {
        fprintf(stdout, "%s\n", fp);
    }
}

void print_for_flag_o(char* fp, int count_file, char* string, char* p_pattern, char* pattern) {
    if (flag.o_flag == 1 && flag.c_flag != 1 && flag.l_flag != 1 && flag.v_flag != 1) {
        FILE *file = NULL;
        file = fopen(fp, "r");
        char* read_char = NULL;
        int amount_str_2 = 0;
        int more_counters = 0;
        size_t j = 0;
        size_t k = 0;
        while ((read_char = fgets(string, LINE_MAX, file)) != NULL) {
            amount_str_2++;
            for (; j != strlen(string); j++) {
                if (read_char[j] == p_pattern[k]) {
                    k++;
                    if (strlen(pattern) == k) {
                        if (count_file == 1) {
                            if (flag.n_flag != 1) {
                                fprintf(stdout, "%s\n", pattern);
                                k = 0;
                                } else if (flag.n_flag == 1) {
                                    if (more_counters > 0) {
                                        fprintf(stdout, "%s\n", pattern);
                                    } else {
                                        fprintf(stdout, "%d:%s\n", amount_str_2, pattern);
                                        more_counters++;
                                    }
                                    k = 0;
                                }
                        } else {
                            if (flag.n_flag != 1) {
                                if (more_counters > 0) {
                                    fprintf(stdout, "%s\n", pattern);
                                } else {
                                    fprintf(stdout, "%s:%s\n", fp, pattern);
                                    more_counters++;
                                }
                                k = 0;
                            } else if (flag.n_flag == 1) {
                                if (more_counters > 0) {
                                    fprintf(stdout, "%s\n", pattern);
                                } else {
                                    fprintf(stdout, "%s:%d:%s\n", fp, amount_str_2, pattern);
                                    more_counters++;
                                }
                                k = 0;
                            }
                        }
                    }
                } else {
                    k = 0;
                }
            }
            k = 0;
            j = 0;
            more_counters = 0;
        }
        fclose(file);
    }
}
