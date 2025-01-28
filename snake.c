#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define GAME_POL_LEN 15
#define SNK_MAX_LEN  64

typedef enum {W, A, S, D} KEYS; // Клавиши управления

// Змейка
typedef struct {
    short x[SNK_MAX_LEN];
    short y[SNK_MAX_LEN];
    short len;
} Snake;

// Яблоко
typedef struct {
    short x;
    short y;
} Apple;

void draw_pol(char (*pole)[GAME_POL_LEN]) {
    system("cls"); // Очистка экрана
    for (short i = 0; i < GAME_POL_LEN; ++i) {
        for (short j = 0; j < GAME_POL_LEN; ++j) {
            putchar(pole[i][j]);
        }
        putchar('\n');
    }
}

void spawn_apple(char (*pole)[GAME_POL_LEN]) {
    Apple apple;
    do {
        apple.x = rand() % (GAME_POL_LEN - 2) + 1;
        apple.y = rand() % (GAME_POL_LEN - 2) + 1;
    } while (pole[apple.x][apple.y] != ' '); // Ищет свободную клетку
    pole[apple.x][apple.y] = '+';
}

void snk_move(Snake *snake, char (*pole)[GAME_POL_LEN], short dx, short dy) {
    // Стирает хвост с поля
    pole[snake->x[snake->len - 1]][snake->y[snake->len - 1]] = ' ';
    // Перемещение тела змейки
    for (short i = snake->len - 1; i > 0; --i) {
        snake->x[i] = snake->x[i - 1];
        snake->y[i] = snake->y[i - 1];
    }
    // Обновление позиции головы
    snake->x[0] += dx;
    snake->y[0] += dy;
    // Проверка столкновения с яблоком
    if (pole[snake->x[0]][snake->y[0]] == '+') {
        // Увеличение длины змейки
        snake->len++;
        if (snake->len > SNK_MAX_LEN) {
            printf("You win!\n");
            exit(0);
        }
        // Респавн яблока
        spawn_apple(pole);
    }
    // Проверка столкновения со стенами
    if (pole[snake->x[0]][snake->y[0]] == '#' || pole[snake->x[0]][snake->y[0]] == '@') {
        printf("Game Over!\n");
        exit(0);
    }
    // Обновление поля
    for (short i = 0; i < snake->len; ++i) {
        pole[snake->x[i]][snake->y[i]] = (i == 0) ? '@' : '@';
    }
}

int main() {
    srand(time(NULL));
    char pole[GAME_POL_LEN][GAME_POL_LEN] = {
        "###############",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "#             #",
        "###############"
    };
    Snake snake = {.x = 5, .y = 5, .len = 1};
    pole[snake.x[0]][snake.y[0]] = '@';
    spawn_apple(pole);
    KEYS key;
    while (1) {
        draw_pol(pole);
        // Чтение клавиш
        if (_kbhit()) {
            char input = _getch();
            switch (input) {
                case 'w': key = W; break;
                case 'a': key = A; break;
                case 's': key = S; break;
                case 'd': key = D; break;
            }
        }
        // Движение змейки
        switch (key) {
            case W: snk_move(&snake, pole,-1, 0); break;
            case A: snk_move(&snake, pole, 0,-1); break;
            case S: snk_move(&snake, pole, 1, 0); break;
            case D: snk_move(&snake, pole, 0, 1); break;
        }
        printf("Snake length: %d", snake.len);
        Sleep(200); // Задержка
    }
    return 0;
}