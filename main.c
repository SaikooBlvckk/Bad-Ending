#include <stdio.h>
#include "loadingBar.c"
#include "Functions.h"
#include "charge-house.c"

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
    select_option();
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
}

void select_option(){
    int choice = -1;
    while (choice != 0){
        menu();
        printf("Seleccione una opción\n");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                printf("Jugar!\n");
                play_game();
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

void play_game(){
    importHouse();
    printf("Aquí se imprimirá el menu de selección de dificultades\n");
    printf("se imprimirán 3 casas de la misma dificultad (facil al inicio del juego) para que el usuario seleccione una\n");
    printf("se seleccionara una casa por el numero que se le asigne a esta (1 , 2 o 3)\n");
    char enter[5];
    scanf("%s", &enter);
}

void load_game(){
    printf("Aquí saldrá la opción para cargar partidas\n");
    printf("la seleccion de partidas será colocando el nombre de usuarion que jugó (preseleccionado anteriormente)\n");
    printf("y el programa buscará y cargará los datos del usuario\n");
    char enter[5];
    scanf("%s", &enter);
}

void score_table(){
    printf("Aquí se imprimirá la tabla de puntuaciones por usuario ordenada de mayor a menor puntaje\n");
    char enter[5];
    scanf("%s", &enter);
}