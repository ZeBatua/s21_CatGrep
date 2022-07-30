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

int find_flag(int ARGC, char **ARGV);
void cycle_output_string(int amount_str, char* string, char *fp, int count_file);
void s21_grep(char* filenames, char* pattern_names, int counter_pars_files);
void once_output_string(char* fp, int count_file, int same_str);
void print_for_flag_o(char* fp, int count_file, char* string, char* p_pattern, char* pattern);
char pars_files(char **ARGV, char* filenames, int* counter_pars_files);
int pars_string(int ARGC, char **ARGV, int *mass);
char *eq_flag_status(char **ARGV, char *ch);
char pars_patterns(char* ARGV[], char* pattern_names, int* counter_pars_patterns);
void disable_flag (char *ch);



int main(int ARGC, char **ARGV) { // нужна проверка то что присутствует необходимое кол-во файлов 
    char filenames[4096] = {'\0'};
    char pattern_names[4096] = {'\0'};
    int mass[1024] = {0};
    int counter_pars_patterns = 0;
    int counter_pars_files = 0;
    int amount_some_file = 0;

    for (int i = 0; i < ARGC; i++) {
        find_flag(ARGC, ARGV);
    }
    //----------change_flags----------//
    if (flag.c_flag == 1) {
        flag.l_flag = 0;
    }
    //----------change_flags----------//



    amount_some_file = pars_string(ARGC, ARGV, mass); // массив 3 2 1

  

    for (int b = 0; b <= ARGC; b++) {
        if (mass[b] == 1) {
            // printf("|||%s|||", ARGV[b]);
            // printf("|||%d|||", b);
            pars_files(&ARGV[b], filenames, &counter_pars_files); 
        }
    }
    // printf("counter_pars_files %d\n", counter_pars_files);

    // printf("files: ");
    // for (int j = 0; j < 40; j++) {
    //     printf("%c", filenames[j]);
    // } 
    // printf("\n");


    // printf("mass: ");
    // for (int j = 0; j < 40; j++) {
    //     printf("%c", mass[j]);
    // } 
    // printf("\n");




    for (int b = 0; b < ARGC; b++) {
        if (mass[b] == 2) {
          pars_patterns(&ARGV[b], pattern_names, &counter_pars_patterns); 
        }
    }

    s21_grep(filenames, pattern_names, amount_some_file);  

    return 0;
}

char pars_patterns(char* ARGV[], char* pattern_names, int* counter_pars_patterns) {
        if (*counter_pars_patterns > 0) {
            strcat(pattern_names, "|");
        }
        strcat(pattern_names, *ARGV);
        *counter_pars_patterns++;
    return *pattern_names;
}


void s21_grep(char* filenames, char* pattern_names, int counter_pars_files) {
    char string[LINE_MAX];
    
    // int e_counter = 0;
    int amount_str = 0;
    int same_str = 0;

    regex_t preg;
    regmatch_t pmatch[1] = {0};
  
    char pattern_for_f[4096] = {'\0'};

    char *fp = NULL;

    fp = strtok(filenames, "|");
    // int abv = 0;
    // MFOENFOUBWEFUBWUFBWIEBUFIWUFBIBEFUIBWEFB
    while (fp != NULL) {
        same_str = 0;
        // abv++;
        FILE *file;
        if ((file = fopen(fp, "r")) != NULL) {
            if (flag.f_flag == 1) { // куда это
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
                    regcomp(&preg, pattern_names, REG_ICASE | REG_EXTENDED);
                } else {
                    regcomp(&preg, pattern_names, REG_EXTENDED);
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
                            // printf("pattern = %s\n", pattern);
                            cycle_output_string(amount_str, string, fp, counter_pars_files);

                        }
                    } else if (flag.f_flag == 1) {
                        if (regexec(&preg, string, 1, pmatch, 0) == 0) {
                            cycle_output_string(amount_str, string, fp, counter_pars_files);

                        }
                    } else if ((flag.o_flag != 1)){  // свободный выход // i не обрабатывает "("
                        // printf("строка %s\n", string);
                        // printf("паттерн %s\n", pattern);
                        if (regexec(&preg, string, 1, pmatch, 0) == 0) {
                            cycle_output_string(amount_str, string, fp, counter_pars_files);
                        }
                    }
                }
            }
            print_for_flag_o(fp, counter_pars_files, string, p_pattern, pattern_names);
            once_output_string(fp, counter_pars_files, same_str);
            fclose(file);
        }
        fp = strtok(NULL, "|");
    }
    regfree(&preg);
}

int pars_string(int ARGC, char **ARGV, int *mass) { // не обработаны частные случаи флагов 
    int counter_for_mass = 1;
    int amount_file = 0;
    char ch[1024] = {'\0'};
    FILE *check;
    char* e_check = "-e";
    char* f_check = "-f";
    for (int i = 1; i < ARGC; i++) { // 1 - файл, 2 - паттерн, 3 - флаг.
        if ((check = fopen(ARGV[i], "r")) == NULL) {
            // printf("%s\n\n", ARGV[i - 1]);
            if ((strcmp(ARGV[i - 1], e_check) == 0) && 
            (strcmp(ARGV[i], eq_flag_status(&ARGV[i], ch)) == 0) &&
            flag.e_flag == 1) {
                disable_flag(ch);
                mass[counter_for_mass] = 2;
                counter_for_mass++;
            } else if (strcmp(ARGV[i - 1], f_check) == 0 && flag.f_flag == 1) {
                fprintf(stdout, "grep: %s: No such file or directory\n", ARGV[i]);
                exit(0);
            } else if (strcmp(ARGV[i], eq_flag_status(&ARGV[i], ch)) == 0) {
                mass[counter_for_mass] = 3;  // проверка что i флаг 
                counter_for_mass++;
                memset(ch, '\0', sizeof(ch));
            } else if (strcmp(ARGV[i - 1], "./s21_grep") == 0) {
                mass[counter_for_mass] = 2; // перед i запуск и i не флаг -> паттерн
                counter_for_mass++;
            } else if (strcmp(ARGV[i - 1], eq_flag_status(&ARGV[i - 1], ch)) == 0) {
                mass[counter_for_mass] = 2; // если  i не флаг, а i - 1 не флаг 
                counter_for_mass++;
                memset(ch, '\0', sizeof(ch));
            } else {
                fprintf(stdout, "grep: %s: No such file or directory\n", ARGV[i]);
                counter_for_mass++;
                amount_file++;
            }
        } else if (strcmp(ARGV[i - 1], "-e") == 0) {
                mass[counter_for_mass] = 2;
                counter_for_mass++;
        } else if (strcmp(ARGV[i - 1], "./s21_grep") == 0) { //  пока не обрабатываю same_name
            mass[counter_for_mass] = 2; // паттерн перед s21_grep
            counter_for_mass++;
        } else if (strcmp(ARGV[i - 1], eq_flag_status((&ARGV[i - 1]), ch)) == 0) {
            mass[counter_for_mass] = 2; // паттерн перед флагом
            counter_for_mass++;
            memset(ch, '\0', sizeof(ch));
        } else {
            mass[counter_for_mass] = 1; // найден файл
            counter_for_mass++;
            amount_file++;
        }
    }
    return amount_file;
}

void disable_flag (char *ch) {
    if (strcmp(&ch[1], "e") == 0){
        flag.e_flag = 0;
    } else if (strcmp(&ch[1], "v") == 0) {
        flag.v_flag = 0;
    } else if (strcmp(&ch[1], "c") == 0) {
        flag.c_flag = 0;
    } else if (strcmp(&ch[1], "l") == 0) {
        flag.l_flag = 0;
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

char *eq_flag_status(char **ARGV, char *ch) {
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
    }

    for ()

    strcmp(*ARGV, ) == 0
    // здесь должно быть 2 перменных i  и j. одна не меняется другая бывает во всех вохможных значениях
    // когда она всех значениях побывала - другая должна изменится. каждая комбинация должна быть в стркмп
    // как только ты находишь ту самую комбинации делаешь стоп и записываешь в ch получившееся значение.
    // Однако помни про случаи f или e будут первыми, более того даже если они будут вторыми, то тебе надо будет
    // то тебе это тоже надо не проебать! удачи RoflanPominki
    // тут мне нужно проверять на комбинации типа -iv -ef -ee и тд
    return ch;
}


char pars_files(char* ARGV[], char *filenames, int* counter_pars_files) { //   вызови эту хуйню и 
    // FILE *f;
    // if ((f = fopen(*ARGV, "r")) != NULL) {
    //     fclose(f);
        if (*counter_pars_files > 0) {
            strcat(filenames, "|");
        }
        strcat(filenames, *ARGV);
        *counter_pars_files+=1;
        // printf("329 %d\n", *counter_pars_files);
    // } /* else {
            // if (flag.c_flag == 0) {
            //     fprintf(stdout, "s21_grep: %s: No such file or directory\n", ARGV[i]);
            // }
            // counter_pars_files++;
        // } */
    return *filenames;
}


int find_flag(int ARGC, char **ARGV) {
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



void cycle_output_string(int amount_str, char* string, char* fp, int count_file) {
    if (count_file > 1) { // если файлов > 1
        if (flag.n_flag == 1) {
            fprintf(stdout, "%s:%d:%s", fp, amount_str, string);
        } else {
            fprintf(stdout, "%s:%s", fp, string);
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

void once_output_string(char* fp, int count_file, int same_str) {
    if (flag.c_flag == 1 && flag.l_flag != 1) {
        if (count_file > 1) {
            fprintf(stdout, "%s:%d\n", fp, same_str);
        } else {
            fprintf(stdout, "%d\n", same_str);
        }
    } else if (flag.c_flag == 1 && flag.l_flag == 1) {
        if (count_file > 1) {
            if (same_str > 0) {
                same_str = 1;
            }
            fprintf(stdout, "%s:%d\n%s\n", fp, same_str, fp);
        } else {
            if (same_str > 0) {
                same_str = 1;
            }
            fprintf(stdout, "%d\n%s\n", same_str, fp);
        }
    } else if (flag.l_flag == 1 && same_str > 0) {
        fprintf(stdout, "%s\n", fp);
    }
}

void print_for_flag_o(char* fp, int count_file, char* string, char* p_pattern, char* pattern) {
    if (flag.o_flag == 1 && flag.c_flag != 1 && flag.l_flag != 1 && flag.v_flag != 1) {
        FILE *file = NULL;
        file = fopen(fp, "r"); // тут мб хуйня
        char* read_char = NULL;
        int amount_str_2 = 0;
        int more_counters = 0;
        size_t j = 0;
        size_t k = 0;
// ARG
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
                }
            }
            k = 0;
            j = 0; // это мб лишнее 
            more_counters = 0;
        }
    }
}

   /*
    1) получение флагов
    2) принять за файлы то что открывается. Если один из "файлов" соответсвует флагу /
       ошибку не выводить, иначе вывести ошибку что файла не существует.
    3) в случае флага е уточнить что после него 100% паттерн.
    4) похоже нужен парсер для регулярок 

    итого: получение флагов. инициализация элементов строки файл / не файл
    */

// добавить обработку s в парсере
// у меня количество файлов считает amount_file

// -o не обработает регулярки
// -e создает едиственный возможный паттерн за исключением тех случаев когда -е вызван несколько раз
// следовательно то что типа паттерн но не стоит после -е надо вывести несуществующий файл
//  а что если -e -e получается я выключу -e. Получается мне нужно исключение 
// если  f не нашел файл то мы ливаем нахуй grep develop ➜ grep -e 123 -f qwe regular.txt
//                                          grep: qwe: No such file or directory
// возможно следует отказаться от первого гетопта и включать флаги только тогда когдя я захочу в парсере
// если e в конце то ебаш grep: option requires an argument -- e