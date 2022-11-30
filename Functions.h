#ifndef Functions_h
#define Functions_h
#include "hashmap.h"
#include "chargeHouse.h"

void menu();
void print_title();
void select_option();
void play_game();
void load_game();
void score_table();
void bad_ending();
int printRoomItems();
void printOtherRooms();
Pair *searchRoom();
Room *changeRoom();
void sleepProgram();
void printBag();
int passedLevel();
int stealItem();
int movementInteractions();
void getOut();
int theyComeBack();
int endGame();

#endif /* Funtions_h*/