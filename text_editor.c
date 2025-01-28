#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define MAX_LINE_LEN 256

void load_file(const char *filename, char ***content, int *line_count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Ошибка открытия файла");
        return;
    }
    *content = NULL;
    *line_count = 0;
    char buffer[MAX_LINE_LEN];
    while (fgets(buffer, MAX_LINE_LEN, file)) {
        char **temp = realloc(*content, (*line_count + 1) * sizeof(char *));
        if (!temp) {
            perror("Ошибка выделения памяти");
            fclose(file);
            return;
        }
        *content = temp;
        (*content)[*line_count] = malloc(strlen(buffer) + 1);
        if (!(*content)[*line_count]) {
            perror("Ошибка выделения памяти для строки");
            fclose(file);
            return;
        }
        strcpy((*content)[*line_count], buffer);
        (*content)[*line_count][strcspn((*content)[*line_count], "\n")] = '\0';

        (*line_count)++;
    }
    fclose(file);
}

void save_file(const char *filename, char **content, int line_count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Ошибка сохранения файла");
        fclose(file);
        return;
    }
    for (int i = 0; i < line_count; i++) {
        fprintf(file, "%s\n", content[i]);
    }
    fclose(file);
}

void display_content(char **content, int line_count) {
    system("cls");
    for (int i = 0; i < line_count; i++) {
        printf("%d|%s\n", i + 1, content[i]);
    }
    putchar('\n');
}

void edit_line(char **content, int line_count) {
    int line_num = 0;
    printf("Введите номер строки для редактирования (1-%d): ", line_count);
    scanf("%d", &line_num);
    if (line_num < 1 || line_num > line_count) {
        perror("Ошибка: Неверный номер строки.\n");
        return;
    }
    printf("Введите новый текст для строки %d: ", line_num);
    while (getchar() != '\n');
    fgets(content[line_num - 1], MAX_LINE_LEN, stdin);
    content[line_num - 1][strcspn(content[line_num - 1], "\n")] = '\0';
}

void input_name(char *filename)
{
    int i = 0;
    char ch;
    printf("Введи название файла текущей директории: ");
    while((ch = getchar()) != '\n') {
        filename = realloc(filename, sizeof(ch));
        filename[i++] = ch;
    }
    filename[i++] = '\0';
}

int main() {
    char *filename = malloc(sizeof(char));
    char **content;
    int line_count = 0;
    char action;
    input_name(filename);
    load_file(filename, &content, &line_count);
    if (line_count == 0) {
        perror("Файл пуст или не существует.\n");
        return 1;
    }
    while (1) {
        display_content(content, line_count);
        puts("1. Редактировать строку");
        puts("2. Сохранить и выйти");
        printf("\nВыберите действие: ");
        action = getchar();
        switch (action) {
            case '1':
                edit_line(content, line_count);
                break;
            case '2':
                save_file(filename, content, line_count);
                puts("\nФайл сохранен.");
                free(content);
                return 0;
            default:
                puts("Неверный выбор. Попробуйте снова.");
                break;
        }
    }
    free(content);
    return 0;
}