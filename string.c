#include <stdio.h>
#include <string.h>
#include <stdbool.h>

void revstr(char *str) {
    char temp;
    int len = strlen(str);
    for (int i = 0, j = len - 1; i < len / 2; i++, j--) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

bool ispaldrm(char *str) {
    const int len = strlen(str);
    char pal[len];
    for (int i = 0, j = len-1; i < len; i++, j--){
        pal[i] = str[j];
    }
    for (int i = 0; i < len; i++){
        if(pal[i] != str[i])
            return false;
    }
    return true;
}

/// @brief splits a string
char** spltstr(const char *str) {
    char s[10][10];
    short row = 0, col = 0;
    const int len = strlen(str);
    for (short i = 0; i < len; i++) {
        if (str[i] != ' ') {
            s[row][col++] = str[i];
        } else if (col > 0) {
            s[row][col] = '\0';
            row++;
            col = 0;
        }
    }
    if (col > 0) {
        s[row][col] = '\0';
    }
    return s;
}

int search_str(char *string, char *search)
{
    if (!string || !search) return -1;

    int start;

    const int len_str = strlen(string);
    const int len_ser = strlen(search);

    for (int i = 0; i < len_str; i++) {
        if(string[i] == search[0] && string[i+(len_ser-1)] == search[len_ser-1]) {
            start = i;
            for (int j = 1; j < (len_ser-1);) {
                if(string[start+j] == search[j]) j++; else break;
                if(j == len_ser-1 && string[start+j] == search[j]) return start;
            }
        }
    }
    return -1;
}

int main()
{
    
    return 0;
}