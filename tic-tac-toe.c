#include <stdio.h>
#include <stdbool.h>

#define POL_LEN 3

// Функция для отрисовки игрового поля
void draw_pol(char (*pol)[POL_LEN]) {
    for (int i = 0; i < POL_LEN; i++) {
        printf("|%c|%c|%c|\n", pol[i][0], pol[i][1], pol[i][2]);
    }
}

// Функция для проверки выигрыша
void win_check(char (*pol)[POL_LEN], bool *is_game_active) {
    // Проверка строк и столбцов
    for (int i = 0; i < POL_LEN; i++) {
        if ((pol[i][0] == pol[i][1] && pol[i][1] == pol[i][2] && pol[i][0] != ' ') || // строки
            (pol[0][i] == pol[1][i] && pol[1][i] == pol[2][i] && pol[0][i] != ' ')) { // столбцы
            printf("Победил игрок %c!\n", pol[i][i]);
            *is_game_active = false;
            return;
        }
    }
    // Проверка диагоналей
    if ((pol[0][0] == pol[1][1] && pol[1][1] == pol[2][2] && pol[0][0] != ' ') || 
        (pol[0][2] == pol[1][1] && pol[1][1] == pol[2][0] && pol[0][2] != ' ')) {
        printf("Победил игрок %c!\n", pol[1][1]);
        *is_game_active = false;
        return;
    }
    // Проверка на ничью
    bool is_draw = true;
    for (int i = 0; i < POL_LEN; i++) {
        for (int j = 0; j < POL_LEN; j++) {
            if (pol[i][j] == ' ') {
                is_draw = false;
                break;
            }
        }
        if (!is_draw) break;
    }
    if (is_draw) {
        printf("Ничья!\n");
        *is_game_active = false;
    }
}

// Функция для выполнения хода игрока
void pl_move(char (*pol)[POL_LEN], const char ch) {
    short x = -1, y = -1;
    draw_pol(pol);
    printf("Играет %c\n", ch);
    while (1) {
        printf("Введите координаты (x y): ");
        if (scanf("%hd %hd", &x, &y) != 2) {
            printf("Ошибка ввода. Введите два числа.\n");
            while (getchar() != '\n');
            continue;
        }
        if (x >= 0 && x < POL_LEN && y >= 0 && y < POL_LEN) {
            if (pol[y][x] != 'X' && pol[y][x] != 'O') {
                pol[y][x] = ch;
                break;
            } else {
                printf("Клетка занята. Выберите другую.\n");
            }
        } else {
            printf("Координаты вне диапазона. Введите значения от 0 до %d.\n", POL_LEN - 1);
        }
    }
}

int main() {
    char pol[POL_LEN][POL_LEN] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    bool is_game_active = true;
    while (is_game_active) {
        pl_move(pol, 'X');
        win_check(pol, &is_game_active);
        if (!is_game_active) break;

        pl_move(pol, 'O');
        win_check(pol, &is_game_active);
    }
    return 0;
}
