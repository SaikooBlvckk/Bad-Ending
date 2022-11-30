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

typedef struct{
    char Name[30];
    HashMap *PassedLevel;
    List *Robbeditems;
}Player;

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
                Player *pl = (Player *)malloc(sizeof(Player));
                pl->PassedLevel = createMap(1);
                pl->Robbeditems = createList();
                printf("Ingrese su nombre de usuario\n");
                scanf("%s", &pl->Name);
                play_game(pl);
                break;
            case 2:
                printf("Cargar Partida!\n");
                system(C);
                chamullo();
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

void play_game(Player *pl){
    char file[50];
    int choice, choice2, choice3;
    do{
        printf("Seleccione el nivel que desea jugar\n");
        printf("1-. Casa nivel facil\n");
        printf("2-. Casa nivel medio\n");
        printf("3-. Casa nivel dificil\n");
        scanf("%d",&choice);
        switch (choice){
            case 1:
                strcpy(file, "./Casas/Casa-Facil-1.csv");
                break;
            case 2:
                strcpy(file, "./Casas/Casa-Medio-1.csv");
                break;
            case 3:
                strcpy(file, "./Casas/Casa-Dificil-1.csv");
                break;
        }
        choice2 = passedLevel(file, pl->PassedLevel);
    }while(choice2 != 2);
    sleepProgram();
    HashMap *Map = importHouse(file);
    List *bag = createList();
    bad_ending(Map, bag);
    pushBack(pl->Robbeditems, bag);
    insertMap(pl->PassedLevel, file, file);
    printf("Quieres seguir jugando?\n");
    printf("1.- Si\n2.- No\n");
    scanf("%d", &choice3);
    if(choice3 == 1) play_game(pl);
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

void bad_ending(HashMap *Map, List *bag){
    char a[5];
    int i = 0, box;
    box = rand() % 100 + 1;
    system(C);
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
    system(C);
    printf("Eliges entrar por %s... Tal vez sea la mejor opcion\n", room->name);
    printf("Una vez dentro...\n");
    while(1){
        printf("Que deseas hacer?\n");
        i = printRoomItems(room->items);
        printf("%d-. Cambiar de habitacion\n", ++i);
        printf("%d-. Salir de la casa\n", ++i);
        printf("%d-. Revisar mochila\n", ++i);
        scanf("%d", &choice);
        if(choice == i){
            printBag(bag);
        }else if (choice == i - 1){
            printf("Decides salir de la casa lo mas rapido posible...\n");
            sleepProgram();
            return;
        }else if (choice == i - 2){
            room = changeRoom(room, aux, Map);
        }else{
            stealItem(choice, room, box, bag);
        }
        sleepProgram();
        system(C);
    }
}

int printRoomItems(List *room){
    printf("--Robar--\n");
    int i = 0;
    Item *item = firstList(room);
    if (item == NULL) return i;
    do{
        printf("%d-. %s\n", ++i, item->name);
        item = nextList(room);
    }while(item != NULL);
    printf("------\n");
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

Room *changeRoom(Room *room, Pair *aux, HashMap *Map){
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
    return room;
}

void sleepProgram(){
#ifdef _WIN32
	 Sleep(1000);
#else
	 usleep(100000);
#endif
}

void printBag(List *bag){
    Item *item = firstList(bag);
    if(item !=  NULL){
        printf("En la mochila tienes los siguientes items\n");
        do{
            printf("%s\n",item->name);
            item = nextList(bag);
        }while(item != NULL);
    }else printf("No tienes items en tu mochila\n");
}

int passedLevel(char *file, HashMap *pl){
    int choice = 2;
    if (searchMap(pl,file) != NULL){
        printf("Nivel ya jugado, deseas repetirlo?\n1-. Si\n2-. No\n");\
        scanf("%d", &choice);
        return choice;
    }else return choice;
}

void stealItem(int choice, Room *room, int box, List *bag){
    system(C);
    int j = -1, choice2, choice3;
    Item *itemaux = firstList(room->items);
    itemaux = steal(j, choice, itemaux, room->items);
    if(strcmp(itemaux->name, "cajafuerte") == 0){
        if(box & 2 == 0){
            printf("Lograste abrirla!\n");
            j = -1;
            int i = printRoomItems(room->cofre);
            scanf("%d", &choice2);
            if(i < choice2){
                printf("Opcion incorrecta\n");
                stealItem(choice, room, box, bag);
            }else{
                itemaux = steal(j, choice2, itemaux, room->cofre);
                printf("Tomas %s y lo guardas en tu mochila\n", itemaux->name);
                pushBack(bag, itemaux);
                popCurrent(room->cofre);
            }
        }else{
            printf("No lograste abrirla, deseas intentarlo de nuevo?\n1-. Si\n2-. No\n");
            scanf("%d", &choice3);
            if (choice3 == 1){
                box = rand() % 100 + 1;
                stealItem(choice, room, box, bag);
            }
        }
    }else{
        printf("Tomas %s y lo guardas en tu mochila\n", itemaux->name);
        pushBack(bag, itemaux);
        popCurrent(room->items);
    }
}
Item *steal(int j, int choice, Item *itemaux, List *room){
    do{
        j++;
        if (j == choice-1) break;
        else itemaux = nextList(room);
    }while(j == choice);
    return itemaux;
}


void chamullo(){
    printf("Entras al Living y los duenos de la casa te ven, llaman a la policia\n");
    printf("Ellos te retienen el tiempo suficiente para que la policia llegue...\n");
    printf("Te llevan detenido...\n");
    printf("Te caen 5 anos y 1 dia de condena...\n");
    printf("GAME OVER\n");
    scanf("%d");
}