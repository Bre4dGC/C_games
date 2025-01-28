#include <stdio.h>
#include <string.h>

#define NAME_LEN 16
#define MAX_STUD 20

struct student {
    char name[NAME_LEN];
    short age;
    float av_score;
};

void addstud(const char *name, short age, float score, struct student students[]) {
    for (short i = 0; i < MAX_STUD; i++) {
        if (students[i].name[0] == '\0') {
            strncpy(students[i].name, name, NAME_LEN - 1);
            students[i].name[NAME_LEN - 1] = '\0';
            students[i].age = age;
            students[i].av_score = score;
            return;
        }
    }
    puts("Ошибка: Список студентов заполнен.");
}

void getstud(const struct student students[]) {
    struct student sorted[MAX_STUD];
    memcpy(sorted, students, MAX_STUD * sizeof(struct student));
    for (short i = 0; i < MAX_STUD - 1; i++) {
        for (short j = i + 1; j < MAX_STUD; j++) {
            if (sorted[i].av_score < sorted[j].av_score) {
                struct student temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    for (short i = 0; i < MAX_STUD; i++) {
        if (sorted[i].name[0] != '\0') {
            printf("Имя: %s, Возраст: %d, Средний балл: %.1f\n",
                   sorted[i].name, sorted[i].age, sorted[i].av_score);
        }
    }
}

void getbyname(const struct student students[], const char *name) {
    for (short i = 0; i < MAX_STUD; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Имя: %s, Возраст: %d, Средний балл: %.1f\n",
                   students[i].name, students[i].age, students[i].av_score);
            return;
        }
    }
    puts("Студент с таким именем не найден.");
}

void action(char act, struct student students[]) {
    while (getchar() != '\n');
    switch (act) {
        case '1': {
            char name[NAME_LEN];
            short age;
            float score;
            printf("Введите имя, возраст, средний балл через пробел: ");
            scanf("%15s %hd %f", name, &age, &score);
            while (getchar() != '\n');
            addstud(name, age, score, students);
            break;
        }
        case '2':
            getstud(students);
            break;
        case '3': {
            char name[NAME_LEN];
            printf("Введите имя студента: ");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0';
            getbyname(students, name);
            break;
        }
        default:
            puts("Ошибка: Неверный ввод.");
            break;
    }
}

void main() {
    struct student students[MAX_STUD] = {0};
    while (1) {
        puts("\n1. Добавить студента\n2. Вывести всех студентов\n3. Найти студента по имени");
        printf("Выберите действие: ");        
        char act = getchar();
        action(act, students);
    }
}