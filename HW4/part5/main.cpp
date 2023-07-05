#include <stdio.h>
#include <windows.h>

int main(){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    int count = 1;
    for(int i = 1; i < 8; i++){
        for(int j = 21 - i; j > 0; j--){
            printf(" ");
        }

        for(int k = i + i - 1; k > 0; k--){
            if(count % 7 == 0) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // RED
                printf("*");
            }
            else if(count % 9 == 0) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE); // BLUE
                printf("*");
            }
            else if(count % 11 == 0) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE); // WHITE
                printf("*");
            }
            else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // GREEN
                printf("*");
            }
            count++;
        }
        printf("\n");
    }

    for(int i = 5; i < 15; i++){
        for(int j = 21 - i; j > 0; j--){
            printf(" ");
        }

        for(int k = i + i - 1; k > 0; k--){
            if(count % 7 == 0) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // RED
                printf("*");
            }
            else if(count % 9 == 0) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE); // BLUE
                printf("*");
            }
            else if(count % 11 == 0) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE); // WHITE
                printf("*");
            }
            else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // GREEN
                printf("*");
            }
            count++;
        }
        printf("\n");
    }

    for(int i = 9; i < 22; i++){
        for(int j = 21 - i; j > 0; j--){
            printf(" ");
        }
        for(int k = i + i - 1; k > 0; k--){
            if(count % 7 == 0) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED); // RED
                printf("*");
            }
            else if(count % 9 == 0) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE); // BLUE
                printf("*");
            }
            else if(count % 11 == 0) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE); // WHITE
                printf("*");
            }
            else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN); // GREEN
                printf("*");
            }
            count++;
        }

        printf("\n");
    }

    for(int i = 5; i > 0; i--){
        for(int j = 17; j > 0; j--){
            printf(" ");
        }
        for(int k = 7; k > 0; k--){
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED); // Light Yellow
            printf("|");
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE); // Light Yellow
        }
        printf("\n");
    }
}