#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define GAME_POL_LEN 15
#define SNK_MAX_LEN  64

typedef enum {W, A, S, D} KEYS; // Клавиши управления

// Змейка
struct snake {
    short x[SNK_MAX_LEN];
    short y[SNK_MAX_LEN];
    short len;
};

void draw_pol(char (*pol)[GAME_POL_LEN]) {
    system("cls"); // Очистка экрана
    for (short i = 0; i < GAME_POL_LEN; ++i) {
        for (short j = 0; j < GAME_POL_LEN; ++j) {
            putchar(pol[i][j]);
        }
        putchar('\n');
    }
}

void spawn_apple(char (*pol)[GAME_POL_LEN]) {
    short x, y;
    do {
        x = rand() % (GAME_POL_LEN - 2) + 1;
        y = rand() % (GAME_POL_LEN - 2) + 1;
    } while (pol[x][y] != ' '); // Ищет свободную клетку
    pol[x][y] = '+';
}

void snk_move(struct snake *snk, char (*pol)[GAME_POL_LEN], short dx, short dy) {
    // Стирает хвост с поля
    pol[snk->x[snk->len - 1]][snk->y[snk->len - 1]] = ' ';
    // Перемещение тела змейки
    for (short i = snk->len - 1; i > 0; --i) {
        snk->x[i] = snk->x[i - 1];
        snk->y[i] = snk->y[i - 1];
    }
    // Обновление позиции головы
    snk->x[0] += dx;
    snk->y[0] += dy;
    // Проверка столкновения с яблоком
    if (pol[snk->x[0]][snk->y[0]] == '+') {
        // Увеличение длины змейки
        snk->len++;
        if (snk->len > SNK_MAX_LEN) {
            printf("You win!\n");
            exit(0);
        }
        // Респавн яблока
        spawn_apple(pol);
    }
    // Проверка столкновения со стенами
    if (pol[snk->x[0]][snk->y[0]] == '#' || pol[snk->x[0]][snk->y[0]] == '@') {
        printf("Game Over!\n");
        exit(0);
    }
    // Обновление поля
    for (short i = 0; i < snk->len; ++i) {
        pol[snk->x[i]][snk->y[i]] = (i == 0) ? '@' : '@';
    }
}

int main() {
    srand(time(NULL));
    char pol[GAME_POL_LEN][GAME_POL_LEN] = {
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
    struct snake snk = {.x = 5, .y = 5, .len = 1};
    pol[snk.x[0]][snk.y[0]] = '@';
    spawn_apple(pol);
    KEYS key;
    while (1) {
        draw_pol(pol);
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
            case W: snk_move(&snk, pol, -1, 0); break;
            case A: snk_move(&snk, pol, 0, -1); break;
            case S: snk_move(&snk, pol, 1, 0); break;
            case D: snk_move(&snk, pol, 0, 1); break;
        }
        printf("Snake length: %d", snk.len);
        Sleep(200); // Задержка
    }
    return 0;
}