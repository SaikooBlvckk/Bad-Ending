#ifndef chargeHouse_h
#define chargeHouse_h
#include "list.h"
#include "hashmap.h"

typedef struct{
  char name[30];
  List *items;
  List *cofre;

  char up[30];
  char down[30];
  char right[30];
  char left[30];
}Room;

typedef struct{
  char name[30];
  int weight;
  int price; 
}Item;

char *get_csv_field_coma(char *tmp, int k);
char *get_csv_field_slash(char *tmp, int k);
void import_file(char *file, HashMap *Map);
HashMap *importHouse();

#endif /* chargeHouse.h*/