#include <stdio.h>

#define ADD(A, B)       ((A) + (B))
#define SUBTRACT(A, B)  ((A) - (B))
#define MULTIPLY(A, B)  ((A) * (B))
#define DIVIDE(A, B)    ((A) / (B))

float action(char act, float a, float b) {
    switch (act) {
        case '+':
            return ADD(a, b);
        case '-':
            return SUBTRACT(a, b);
        case '*':
            return MULTIPLY(a, b);
        case '/':
            if (b != 0) {
                return DIVIDE(a, b);
            } else {
                puts("Error: Division by zero!");
                return 0;
            }
        default:
            puts("Error: Invalid action!");
            return 0;
    }
}

void main(void) {
    char act;
    float a = 0, b = 0, result;

    scanf("%f %c %f", &a, &act, &b);
    while (getchar() != '\n');
    result = action(act, a, b);
    printf("Result: %.2f\n\n", result);
}
