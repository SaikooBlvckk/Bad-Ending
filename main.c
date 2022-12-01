#include <stdio.h>
#include "loadingBar.c" // Archivo para mostrar la barra de carga
#include "Functions.h" // Header para las funciones
#include "charge-house.c" // Archivo para cargar las casas
#include "list.h" // Header para las funciones de List.c
#include "hashmap.h" // Header para las funciones de List.h
#include "LoadGame.c" // Archivo para cargar partida y mostrar la tabla d puntajes

// Verification if is Windows or Linux

#ifdef _WIN32 // Sirve para verificar si el usuario esta en linux o windows
	#include <windows.h>
    #define C "cls"
#else
	#include <unistd.h>
    #define C "clear"
#endif

#define TITLE  "### Bad Ending ###"

// Main Code

int main(){ // Main
    print_title();
    select_option();
}

void print_title(){ // Imprimee el titulo del jeugo y llama a a funcion para poner la barra de carga
    system(C);
    printf("%30s\n", TITLE);
    loadingBar();
    printf("\n");
}

void menu(){ // sirve para imprimir el menu del juego
    system(C);
    printf("%30s\n", TITLE);
    printf("1. Jugar!\n");
    printf("2. Cargar Partida\n");
    printf("3. Instrucciones\n");
    printf("4. Table de puntajes\n");
    printf("0. Salir del juego\n");
}

void select_option(){ //funcion principal para seleccionar que es lo que el usuario quiere hacer
    int choice = -1;
    Player *pl = (Player *)malloc(sizeof(Player));
    while (choice != 0){
        char a[5];
        menu();
        printf("Seleccione una opción\n");
        scanf("%d", &choice);
        switch(choice){
            case 1: // en esta parte el usuario da inicio a jugar
                printf("Jugar!\n");
                pl->PassedLevel = createMap(1);
                pl->Robbeditems = createList();
                printf("Ingrese su nombre de usuario\n");
                scanf("%s", &pl->Name);
                play_game(pl);
                break;
            case 2: // en esta parte el usuario puede cargar la partida anterior
                pl = loadGame();
                if (pl == NULL) pl = (Player *)malloc(sizeof(Player));
                else{
                    printf("Cargado con exito %s\n", pl->Name);
                    sleepProgram();
                    play_game(pl);
                }
                system(C);
                break;
            case 3: // se imprime una breve descripcion de como se juega
                printf("--Instrucciones--\n");
                printf("Saldran por pantalla las opciones a realizar enumeradas\n");
                printf("Por consola tendras que ingresar el numero de la opcion elegida\n");
                printf("Ingrese un caracter y pulse enter para continuar\n");
                scanf("%s", &a);
                break;
            case 4: // imprime la tabla de puntajes
                printScoreTable();
                scanf("%s", &a);
                break;
            case 0: // finaliza el juego
                printf("Saliendo del juego :(\n");
                return;
            default:
                printf("Opción no valida!\n");
                break;
        }
    }
}

void saveGame(Player *pl){ // funcion para generar un .csv donde se guardan los datos del jugador
    char file[30];
    strcpy(file, pl->Name);
    strncat(file,".csv", 15);
    FILE *fp = fopen(file, "w");
    Pair *aux = firstMap(pl->PassedLevel);
    Player *playerAux;
    do{
        playerAux = aux->value;
        fprintf(fp, "%s,", pl->Name);
        fprintf(fp,"%s\n",aux->key);
        aux = nextMap(pl->PassedLevel);
    }while(aux!= NULL);
    fclose(fp);
}

void play_game(Player *pl){ // funcion que da inicio al juego
    char file[50];
    int choice, choice2, choice3, lvl;
    do{
        system(C);
        printf("Seleccione el nivel que desea jugar\n");
        printf("1-. Casa nivel facil\n");
        printf("2-. Casa nivel medio\n");
        printf("3-. Casa nivel dificil\n");
        scanf("%d",&choice);
        
        printf("1-. Nivel 1\n2-. Nivel 2\n3-. Nivel 3\n");
        scanf("%d", &lvl);
        
        switch (choice){ // en esta parte el jugador selecciona que casa jugará
            case 1:
                if(lvl == 1) strcpy(file, "./Casas/Casa-Facil-1.csv");
                else if (lvl == 2) strcpy(file, "./Casas/Casa-Facil-2.csv");
                else strcpy(file, "./Casas/Casa-Facil-3.csv");
                break;
            case 2:
                if(lvl == 1) strcpy(file, "./Casas/Casa-Medio-1.csv");
                else if (lvl == 2) strcpy(file, "./Casas/Casa-Medio-2.csv");
                else strcpy(file, "./Casas/Casa-Medio-3.csv");
                break;
            case 3:
                if(lvl == 1) strcpy(file, "./Casas/Casa-Dificil-1.csv");
                else if (lvl == 2) strcpy(file, "./Casas/Casa-Dificil-2.csv");
                else strcpy(file, "./Casas/Casa-Dificil-3.csv");
                break;
        }
        choice2 = passedLevel(file, pl->PassedLevel);
    }while(choice2 != 1);
    sleepProgram();
    HashMap *Map = importHouse(file);
    List *bag = createList();
    pl->playerMovement = 0;
    bad_ending(Map, bag, pl); // aqui se da inicio al juego
    pushBack(pl->Robbeditems, bag);
    insertMap(pl->PassedLevel, file, pl);   
    printf("Quieres seguir jugando?\n");
    printf("1.- Si\n2.- No\n");
    scanf("%d", &choice3);
    if(choice3 == 1) play_game(pl);
    else{
        saveGame(pl);
        createScoreTable(pl);
    }
}

void createScoreTable(Player *pl){ // se crea la tabla de puntuaciones NO ALCANZAMOS A ORDENARLA :(
    FILE *fp = fopen("scoreTable.csv", "a");
    int total = 0, puntaje;
    fprintf(fp, "%s,%d,",pl->Name,pl->playerMovement);
    List *itemListAux = firstList(pl->Robbeditems);
    Item *itemAux;
    do{
        itemAux = firstList(itemListAux);
        do{
            total += itemAux->price;
            itemAux = nextList(itemListAux);
        } while (itemAux != NULL);
        itemListAux = nextList(pl->Robbeditems);
    } while (itemListAux != NULL);

    fprintf(fp,"%d,",total);
    puntaje = (pl->playerMovement * total) / 200;
    fprintf(fp,"%d\n",puntaje);
    fclose(fp);
}

void bad_ending(HashMap *Map, List *bag, Player *pl){ // El juego
    int i = 0, box;
    box = rand() % 100;
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
    scanf("%d", &choice); // Se eligue la habitacion por la cual se entrara a a la casa
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
    while(1){ // da inicio al bucle del juego
        int interactions = movementInteractions(pl, bag, room->name); // verificador de interacciones con el usuario
        if(interactions == 2){
            getOut(room, aux, Map, pl); // funcion por si el usuario quiere salir del juego
            sleepProgram();
            return;
        }
        printf("Que deseas hacer?\n");
        i = printRoomItems(room->items); // imprime los items de las habitaciones
        printf("%d-. Cambiar de habitacion\n", ++i);
        printf("%d-. Salir de la casa\n", ++i);
        printf("%d-. Revisar mochila\n", ++i);
        scanf("%d", &choice); // se selecciona que quiere hacer el usuario
        if(choice == i){
            printBag(bag); // imprime la mochila del usuario
        }else if (choice == i - 1){
            getOut(room, aux, Map, pl);
            sleepProgram();
            return;
        }else if (choice == i - 2){
            room = changeRoom(room, aux, Map, pl); // cambia de habitacion
        }else{
            box = stealItem(choice, room, box, bag, pl); //roba un item
        }
        sleepProgram();
        system(C);
        pl->playerMovement++; // contador de movimiento para interacciones
    }
}

int printRoomItems(List *room){ // imprime el item de las habitaciones
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

void printOtherRooms(Room *room){ // imprime las otras habitaciones cercanas
    if (strcmp(room->up, "NO") != 0)
        printf("%d-. ir a %s\n", 1, room->up);
    if (strcmp(room->down, "NO") != 0)
        printf("%d-. ir a %s\n", 2, room->down);
    
    if (strcmp(room->left, "NO") != 0)
        printf("%d-. ir a %s\n", 3, room->left);
    
    if (strcmp(room->right, "NO") != 0)
        printf("%d-. ir a %s\n", 4, room->right);
}

Room *changeRoom(Room *room, Pair *aux, HashMap *Map, Player *pl){ // cambia de habitacion
    int nextRoom;
    printOtherRooms(room);
    scanf("%d",&nextRoom);
    if(nextRoom == 1){
        if(strcmp(room->up, "NO") != 0) aux = searchMap(Map, room->up);
        else{
            printf("Caminas en esa direccion y... te chocas con una pared ;-;\n");
            pl->playerMovement += 2;
        }
    }
    if(nextRoom == 2){
        if(strcmp(room->down, "NO") != 0) aux = searchMap(Map, room->down);
        else{
            printf("Caminas en esa direccion y... te chocas con una pared ;-;\n");
            pl->playerMovement += 2;
        }
    }
    if(nextRoom == 3){
        if(strcmp(room->left, "NO") != 0) aux = searchMap(Map, room->left);
        else{
            printf("Caminas en esa direccion y... te chocas con una pared ;-;\n");
            pl->playerMovement += 2;
        }
    }
    if(nextRoom == 4){
        if(strcmp(room->right, "NO") != 0) aux = searchMap(Map, room->right);
        else{
            printf("Caminas en esa direccion y... te chocas con una pared ;-;\n");
            pl->playerMovement += 2;
        }
    }
    room = aux->value;
    return room;
}

void sleepProgram(){ // funcion para verificar el sleep linux o windows
#ifdef _WIN32
	 Sleep(1000);
#else
	 usleep(1000000);
#endif
}

void printBag(List *bag){
    char a[5];
    Item *item = firstList(bag);
    if(item !=  NULL){
        printf("En la mochila tienes los siguientes items\n");
        do{
            printf("%s precio: %d peso: %d\n",item->name, item->price, item->weight);
            item = nextList(bag);
        }while(item != NULL);
    }else printf("No tienes items en tu mochila\n");
    printf("Ingrese un caracter y luego enter para continuar\n");
    scanf("%s", &a);
}

int passedLevel(char *file, HashMap *pl){ // para verificar los niveles que se jugaron
    int choice = 1;
    if (searchMap(pl,file) != NULL){
        printf("Nivel ya jugado, deseas repetirlo?(Se borraran los datos de la partida anterior)\n1-. Si\n2-. No\n");\
        scanf("%d", &choice);
        if (choice == 1) eraseMap(pl,file);
        return choice;
    }else return choice;
}

int stealItem(int choice, Room *room, int box, List *bag, Player *pl){ //funcion para robar un item
    system(C);
    int j = -1, choice2, choice3;
    Item *itemaux = firstList(room->items);
    do{
        j++;
        if (j == choice-1) break;
        else itemaux = nextList(room->items);
    }while(j != choice);
    if(strcmp(itemaux->name, "cajafuerte") == 0){
        if(box % 2 == 0){
            printf("Lograste abrirla!\n");
            j = -1;
            int i = printRoomItems(room->cofre);
            scanf("%d", &choice2);
            if(i < choice2){
                printf("Opcion incorrecta\n");
                sleepProgram();
                pl->playerMovement++;
                box = stealItem(choice, room, box, bag, pl);
            }else{
                Item *itemauxbox = firstList(room->cofre);
                do{
                    j++;
                    if (j == choice2-1) break;
                    else itemauxbox = nextList(room->cofre);
                }while(j != choice2);
                printf("Tomas %s y lo guardas en tu mochila\n", itemauxbox->name);
                pushBack(bag, itemauxbox);
                popCurrent(room->cofre);
            }
            if(firstList(room->cofre) == NULL) popCurrent(room->items);
        }else{
            printf("No lograste abrirla, deseas intentarlo de nuevo?\n1-. Si\n2-. No\n");
            scanf("%d", &choice3);
            if (choice3 == 1){
                box = rand() % 100;
                pl->playerMovement++;
                box = stealItem(choice, room, box, bag, pl);
            }
        }
    }else{
        printf("Tomas %s y lo guardas en tu mochila\n", itemaux->name);
        pushBack(bag, itemaux);
        popCurrent(room->items);
    }
    return box;
}

int movementInteractions(Player *pl, List *bag, char *room){ // funcion para interacciones por movimiento
    Item *itemaux = firstList(bag);
    if (itemaux == NULL) return 0;
    int totalWeight = 0;
    do{
        totalWeight += itemaux->weight;
        if(strcmp(itemaux->name, "TV") == 0) pl->playerMovement++;
        if(strcmp(itemaux->name, "computador") == 0) pl->playerMovement++;
        if(strcmp(itemaux->name, "tocadiscos") == 0) pl->playerMovement++;
    }while(nextList(bag) != NULL);
    if(totalWeight <= 200 && 100 <= totalWeight) pl->playerMovement++;
    if(200 < totalWeight) pl->playerMovement += 2;

    if(pl->playerMovement >= 65 && strcmp(room, "Living") == 0) return endGame();
    if(pl->playerMovement >= 40) return theyComeBack();

    return 0;
}

void getOut(Room *room, Pair *aux, HashMap *Map, Player *pl){ // funcion apra salir de la casa
    while (1){
        int cantWindows = 0;
        if (strcmp(room->up, "NO") == 0) cantWindows++;
        if (strcmp(room->down, "NO") == 0) cantWindows++;
        if (strcmp(room->left, "NO") == 0) cantWindows++;
        if (strcmp(room->right, "NO") == 0) cantWindows++;

        if (cantWindows >= 2){
            printf("Te acercas a la ventana mas cercana, la abres y sales sin ninguna complicacion...\n");
            return;
        }else{
            printf("Esta habitacion no tiene ningun lugar seguro para escapar...\n");
            room = changeRoom(room, aux, Map, pl);
        }
    }
}

int theyComeBack(){ // funcion que avisa una de las interacciones
    printf("Escuchas un ruido afuera de la casa, vez por la ventana y...\n");
    printf("SON LOS DUENOS DE LA CASA, LLEGARON!\n");
    printf("Que deseas hacer?\n1-. Continuar robo\n2-. Salir de la casa YA!\n");
    int choice;
    scanf("%d", &choice);
    return choice;
}

int endGame(){// funcion que avisa una de las interacciones (se finaliza el juego perdiendo)
    char a[5];
    printf("Entras al Living y los duenos de la casa te ven, llaman a la policia\n");
    printf("Ellos te retienen el tiempo suficiente para que la policia llegue...\n");
    printf("Te llevan detenido...\n");
    printf("Te caen 5 anos y 1 dia de condena...\n");
    printf("GAME OVER\n");
    printf("\n\nIngrese un caracter y presione enter para continuar\n\n");
    scanf("%s",&a);
    return -1;
}