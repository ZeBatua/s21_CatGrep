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

int find_flag(int ARGC, char *ARGV[]);
void output_string(int amount_str, char* string, char* ARGV[], int amount_file);
void s21_grep(char* ARGV[], char* pattern, int count_65file);

int main(int ARGC, char *ARGV[]) { // нужна проверка то что присутствует необходимое кол-во файлов 
    int error = 0;
    int amount_flag = 0;
    int i = 0;
    // char char_for_f[] = "-f";
    for (i = 1; i < ARGC; i++) {
        error = find_flag(ARGC, ARGV);
        if (error == -1) {
            break;
        } else if (error == '?') {
            exit(0);
        } else {
            amount_flag++;
        }
    }
    // нужен цикл который скажет что i-ый это -f, следовательно то i+1 ожидается быть файлом-паттерном, иначе лох
    // for (int j = 0; j < ARGC; j++) {
    //     printf("%s\n", ARGV[j]);
    //     if (flag.f_flag == 1 && memcmp(ARGV[j], char_for_f, 5) == 0) {
    //         FILE *file = NULL;
    //         file = fopen((char *)ARGV[j + 1], "r");
    //         if (file == NULL) {
    //             fprintf(stdout, "s21_grep: %s: No such file or directory\n", (char *)ARGV[j + 1]);
    //         }
    //     }
    // }



    for (int print = i + 1; print < ARGC; print++) {
        // printf("&ARGV[print] = %s\nARGV[i] = %s\n", *&ARGV[print], ARGV[i-1]);

        s21_grep(&ARGV[print], ARGV[i], (ARGC - i - 1)); //  надо чтобы f ожидал файл
    }
    return 0;
}


int find_flag(int ARGC, char *ARGV[]) {
    int findF;
    findF = getopt(ARGC, ARGV, "eivclnhsfo"); // : надо  ли
    if (findF != -1) {
        switch (findF) {
            case 'e':
                flag.e_flag = 1;
                break;
            case 'i':
                flag.i_flag = 1;
                break;
            case 'v':
                flag.v_flag = 1;
                break;
            case 'c':
                flag.c_flag = 1;
                break;
            case 'l':
                flag.l_flag = 1;
                break;
            case 'n':
                flag.n_flag = 1;
                break;
            case 'h':
                flag.h_flag = 1;
                break;
            case 's':
                flag.s_flag = 1;
                break;
            case 'f':
                flag.f_flag = 1;
                break;
            case 'o':
                flag.o_flag = 1;
                break;
            case '?':
                break;
        }
    }
    return findF;
}

void s21_grep(char* ARGV[], char* pattern, int count_file) {
    FILE *file = NULL;
    char string[LINE_MAX];
    
    int e_counter = 0;
    int amount_str = 0;
    int same_str = 0;
    // int pattern_count = 0;
    char* read_char = NULL;
    regex_t preg;
    regmatch_t pmatch[1];
    size_t k = 0;
    // int move = 0;
    file = fopen(*ARGV, "r");
    // printf("|%s|\n\n", *ARGV);
    char pattern_for_f[4096] = {'\0'};
    if (flag.s_flag == 1 && file == NULL) {
        exit(0);
    }
    if (file == NULL) {
        fprintf(stdout, "s21_grep: %s: No such file or directory\n", *ARGV);
    } else {
        if (flag.f_flag == 1) { // куда это
            char regfile[1024];
            char *file = regfile;
            file = ARGV[count_file - 2];
            FILE *f;
            char str[4097] = {'\0'};
            char *cc = str;
                if ((f = fopen(file, "r")) != NULL) {
                    for (size_t j = 0; fgets(cc, 4096, f); j++) {
                        if (e_counter > 0) {
                            strcat(pattern_for_f, "|");
                        }
                        if (strchr(cc, '\n')) { // Указатель на первое вхождение символа в строку. Если значение не найдено, функция возвращает нулевой указатель.
                            *(cc + strlen(cc) - 1) = '\0';
                        }
                        if (!strcmp(cc, "\0")) { // сравнивает строки и выводит <>=
                            cc = "\n";
                        }
                        strcat(pattern_for_f, cc); // закидывает в конец строки строку
                        e_counter++;
                        memset(cc, '\0', 4096);  // 4096 символов заполнит \0
                    }
                    fclose(f);
                } else {
            fprintf(stderr, "s21_grep: %s: No such file or directory\n", file);
            }
        }
        char* p_pattern = NULL;
        if (flag.f_flag != 1) {
            if (flag.i_flag == 1) {
                regcomp(&preg, pattern, REG_ICASE | REG_EXTENDED);
            } else {
                regcomp(&preg, pattern, REG_EXTENDED);
            }
            p_pattern = pattern;
        } else {
            if (flag.i_flag == 1) {
                regcomp(&preg, pattern_for_f, REG_ICASE | REG_EXTENDED);
            } else {
                regcomp(&preg, pattern_for_f, REG_EXTENDED);
            }
            p_pattern = pattern_for_f;
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
                        output_string(amount_str, string, ARGV, count_file);

                    }
                } else if (flag.f_flag == 1) {
                    if (regexec(&preg, string, 1, pmatch, 0) == 0) {
                        output_string(amount_str, string, ARGV, count_file);

                    }
                } else if ((flag.o_flag != 1)){  // свободный выход // i не обрабатывает "("
                    // printf("строка %s\n", string);
                    // printf("паттерн %s\n", pattern);
                    if (regexec(&preg, string, 1, pmatch, 0) == 0) {
                        output_string(amount_str, string, ARGV, count_file);
                    }
                }
            }
        }
        fclose(file);

        //------------------------------------------------------------------------------//
        
    if (flag.o_flag == 1 && flag.c_flag != 1 && flag.l_flag != 1 && flag.v_flag != 1) {
        file = fopen(*ARGV, "r");
        int amount_str_2 = 0;
        int more_counters = 0;
        size_t j = 0;
        while ((read_char = fgets(string, LINE_MAX, file)) != NULL) {
            amount_str_2++;
            for (;j != strlen(string); j++) {
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
                        } else { // для 2+ файлов
                            if (flag.n_flag != 1) { // мало условий // ищет только первый паттерн в файле
                                if (more_counters > 0){
                                    fprintf(stdout, "%s\n", pattern);
                                } else {
                                    fprintf(stdout, "%s:%s\n", *ARGV, pattern);
                                    more_counters++;
                                }
                                k = 0;
                            } else if (flag.n_flag == 1) {
                                if (more_counters > 0) {
                                    fprintf(stdout, "%s\n", pattern);
                                } else {
                                    fprintf(stdout, "%s:%d:%s\n", *ARGV, amount_str_2, pattern);
                                    more_counters++;
                                }
                                k = 0;
                            }
                        }
                    }
                }
            }
            k = 0;
            j = 0; // это мб лишнее 
            more_counters = 0;
        }
    }
        //---------------------------------------------------------------------//

        if (flag.c_flag == 1 && flag.l_flag != 1) {
            if (count_file > 1) {
                fprintf(stdout, "%s:%d\n", *ARGV, same_str);
            } else {
                fprintf(stdout, "%d\n", same_str);
            }
        } else if (flag.c_flag == 1 && flag.l_flag == 1) {
            if (count_file > 1) {
                if (same_str > 0) {
                    same_str = 1;
                }
                fprintf(stdout, "%s:%d\n%s\n", *ARGV, same_str, *ARGV);
            } else {
                if (same_str > 0) {
                    same_str = 1;
                }
                fprintf(stdout, "%d\n%s\n", same_str, *ARGV);
            }
        } else if (flag.l_flag == 1 && same_str > 0) {
            fprintf(stdout, "%s\n", *ARGV);
        }
    regfree(&preg);
    fclose(file);
    }
}

void output_string(int amount_str, char* string, char* ARGV[], int amount_file) {
    if (amount_file > 1) { // если файлов > 1
        if (flag.n_flag == 1) {
            fprintf(stdout, "%s:%d:%s", *ARGV, amount_str, string);
        } else {
            fprintf(stdout, "%s:%s", *ARGV, string);
        }
    } else { // если файл 1
        if (flag.n_flag == 1 && flag.h_flag == 1) {
            fprintf(stdout, "%d:%s", amount_str, string);
        } else if (flag.n_flag != 1 && flag.h_flag == 1) {
            fprintf(stdout, "%s", string);
        } else if (flag.n_flag == 1) {
            fprintf(stdout, "%d:%s", amount_str, string);
        } else{
            fprintf(stdout, "%s", string);
        }
    }
}
