#include <stdio.h>
#include "loadingBar.c"
#include "Functions.h"

// Verification if is Windows or Linux

#ifdef _WIN32
	#include <windows.h>
    #define C "cls"
#else
	#include <unistd.h>
    #define C "clear"
#endif

#define TITLE  "### Bad Ending ###"

// Main Code

int main(){
    print_title();
    menu();
}

void print_title(){
    system(C);
    printf("%30s\n", TITLE);
    loadingBar();
    printf("\n");
}

void menu(){
    system(C);
    printf("%30s\n", TITLE);
    printf("1. Jugar!\n");
    printf("2. Cargar Partida\n");
    printf("3. Instrucciones\n");
    printf("4. Table de puntajes\n");
    printf("0. Salir del juego\n");
    select_option();
}

void select_option(){
    int choice = -1;
    while (choice != 0){
        printf("Seleccione una opción\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Jugar!\n");
                break;
            case 2:
                printf("Cargar Partida!\n");
                break;
            case 3:
                printf("Instrucciones!\n");
                break;
            case 4:
                printf("Tabla de puntajes!\n");
                break;
            case 0:
                printf("Saliendo del juego :(\n");
                return;
            default:
                printf("Opción no valida!\n");
                break;
        }
    }
}