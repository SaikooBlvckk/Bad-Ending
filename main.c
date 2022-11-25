#include <stdio.h>
#include "loadingBar.c"
#include "Functions.h"
#include "charge-house.c"
#include "list.h"
#include "hashmap.h"

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
    printf("Aquí se imprimirá el menu de selección de dificultades\n");
    printf("se imprimirán 3 casas de la misma dificultad (facil al inicio del juego) para que el usuario seleccione una\n");
    printf("se seleccionara una casa por el numero que se le asigne a esta (1 , 2 o 3)\n");
    char enter[5];
    scanf("%s", &enter);
    printf("se jugara la Casa Dificil 1 (nombre de prueba)\n");
    HashMap *Map = importHouse();
    bad_ending(Map);
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

void bad_ending(HashMap *Map){
    List *bag = createList();
    char a[5];
    int i = 0;
    printf("JUEGO EN DESARROLLO, NO ES LA VERSION FINAL!\n");
    printf("Llegas a la casa de los Villagran, tal como te dijo tu contacto, esa era la hora perfecta...\n");\
    printf("Tomas una bocanada de aire y te decides a entrar por...\n");

    Pair *aux = firstMap(Map);
    Room *room;
    do{
        room = aux->value;
        printf("%d-. %s\n", ++i, room->name);
        aux = nextMap(Map);
    }while(aux != NULL);
    int choice;
    scanf("%d", &choice);
    i = -1;
    aux = firstMap(Map);
    do{
        i++;
        if (i == choice-1) break;
        else aux = nextMap(Map);
    }while(i != choice);
    room = aux->value;

    printf("Eliges entrar por %s... Tal vez sea la mejor opcion\n", room->name);
    printf("Una vez dentro...\n");
    while(1){
        printf("Que deseas hacer?\n");
        i = printRoomItems(room);
        printf("%d-. Cambiar de habitacion\n", ++i);
        printf("%d-. Salir de la casa\n", ++i);
        scanf("%d", &choice);
        if (choice == i){
            printf("Decides salir de la casa lo mas rapido posible...\n");
            scanf("%s",&a);
            return;
        }else if (choice == i - 1){
            int nextRoom;
            printOtherRooms(room);
            scanf("%d",&nextRoom);
            if(nextRoom == 1){
                if(strcmp(room->up, "NO") != 0)
                    aux = searchMap(Map, room->up);
                else printf("Caminas en esa direccion y... te chocas con una pared ;-;\n");
            }
            if(nextRoom == 2){
                if(strcmp(room->down, "NO") != 0)
                    aux = searchMap(Map, room->down);
                else printf("Caminas en esa direccion y... te chocas con una pared ;-;\n");
            }
            if(nextRoom == 3){
                if(strcmp(room->left, "NO") != 0)
                    aux = searchMap(Map, room->left);
                else printf("Caminas en esa direccion y... te chocas con una pared ;-;\n");
            }
            if(nextRoom == 4){
                if(strcmp(room->right, "NO") != 0)
                    aux = searchMap(Map, room->right);
                else printf("Caminas en esa direccion y... te chocas con una pared ;-;\n");
            }
            room = aux->value;
        }else{
            int j = -1;
            Item *itemaux = firstList(room->items);
            do{
                j++;
                if (j == choice-1) break;
                else itemaux = nextList(room->items);
            }while(j == choice);
            printf("decides guardar %s en tu mochila\n", itemaux->name);
            popCurrent(room->items);
        }
    }
    
}

int printRoomItems(Room *room){
    int i = 0;
    Item *item = firstList(room->items);
    if (item == NULL) return i;
    do{
        printf("%d-. %s\n", ++i, item->name);
        item = nextList(room->items);
    }while(item != NULL);
    return i;
}

void printOtherRooms(Room *room){
    if (strcmp(room->up, "NO") != 0)
        printf("%d-. ir a %s\n", 1, room->up);
    if (strcmp(room->down, "NO") != 0)
        printf("%d-. ir a %s\n", 2, room->down);
    
    if (strcmp(room->left, "NO") != 0)
        printf("%d-. ir a %s\n", 3, room->left);
    
    if (strcmp(room->right, "NO") != 0)
        printf("%d-. ir a %s\n", 4, room->right);
}
