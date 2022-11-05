#include <stdio.h>
#include "loadingBar.c"
#include "Functions.h"

// Verification if is Windows or Linux

#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

#define TITLE  "### Bad Ending ###"

// Main Code

int main(){
    print_title();
    menu();
}

void print_title(){
    system("clear");
    printf("%30s\n", TITLE);
    loadingBar();
    printf("\n");
}

void menu(){
    system("clear");
    printf("%30s   The Game!\n", TITLE);
    printf("1. Jugar!\n");
    printf("2. Cargar Partida\n");
    printf("3. Instrucciones\n");
    printf("4. Table de puntajes\n");
    printf("0. Salir del juego\n");
}