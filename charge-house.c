#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "list.c"
#include "hashmap.c"

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

char *get_csv_field_coma(char *tmp, int k) {
  int open_mark = 0;
  char *ret = (char *)malloc(100 * sizeof(char));
  int ini_i = 0, i = 0;
  int j = 0;
  while (tmp[i + 1] != '\0') {

    if (tmp[i] == '\"') {
      open_mark = 1 - open_mark;
      if (open_mark)
        ini_i = i + 1;
      i++;
      continue;
    }

    if (open_mark || tmp[i] != ',') {
      if (k == j)
        ret[i - ini_i] = tmp[i];
      i++;
      continue;
    }

    if (tmp[i] == ',') {
      if (k == j) {
        ret[i - ini_i] = 0;
        return ret;
      }
      j++;
      ini_i = i + 1;
    }

    i++;
  }

  if (k == j) {
    ret[i - ini_i] = 0;
    return ret;
  }

  return NULL;
}

char *get_csv_field_slash(char *tmp, int k) {
  int open_mark = 0;
  char *ret = (char *)malloc(100 * sizeof(char));
  int ini_i = 0, i = 0;
  int j = 0;
  while (tmp[i + 1] != '\0') {

    if (tmp[i] == '\"') {
      open_mark = 1 - open_mark;
      if (open_mark)
        ini_i = i + 1;
      i++;
      continue;
    }

    if (open_mark || tmp[i] != '/') {
      if (k == j)
        ret[i - ini_i] = tmp[i];
      i++;
      continue;
    }

    if (tmp[i] == '/') {
      if (k == j) {
        ret[i - ini_i] = 0;
        return ret;
      }
      j++;
      ini_i = i + 1;
    }

    i++;
  }

  if (k == j) {
    ret[i - ini_i] = 0;
    return ret;
  }

  return NULL;
}

void import_file(char *file, HashMap *Map) {
  FILE *fp = fopen(file, "r");

  char line[1024];
  char *aux;
  char *aux2;
  fgets(line, 1023, fp);
  while (fgets(line, 1023, fp) != NULL) {
    int j = 0;
    Room *room = (Room *)malloc(sizeof(Room));
    room->items = createList();
    room->cofre = createList();
    aux = (char *)malloc(sizeof(char));
    aux2 = (char *)malloc(sizeof(char));
    strcpy(room->name, get_csv_field_coma(line, 0));
    strcpy(room->up, get_csv_field_coma(line, 1));
    strcpy(room->down, get_csv_field_coma(line, 2));
    strcpy(room->left, get_csv_field_coma(line, 3));
    strcpy(room->right, get_csv_field_coma(line, 4));

    strcpy(aux, get_csv_field_coma(line, 5));
    printf("se agrega %s\n", room->name);
    printf("wail\n");
    while (aux2 != NULL){
      printf("entra al wail\n");
      Item *items = (Item *)malloc(sizeof(Item));
      printf("asigna memoria\n");
      if (get_csv_field_slash(aux, j) != NULL){
        printf("entra al if\n");
        strcpy(items->name, get_csv_field_slash(aux, j));
        printf("strincopi\n");
        items->price = rand() % (100 + 1)* 100;
        printf("ciopre\n"); 
        items->weight = rand() % (100);
        printf("sope\n");
        pushBack(room->items, items);
        printf("pushbak\n");
        j++;
      }else aux2 = NULL;
      printf("%d ", j);
    }
    printf("\nse agregan items\n");
    j = 0;
    aux2 = "a";
    strcpy(aux, get_csv_field_coma(line, 6));
    if (strcmp(aux, "NO ") != 0){
      while (aux2 != NULL){
        Item *items = (Item *)malloc(sizeof(Item));
        if (get_csv_field_slash(aux, j) != NULL){
          strcpy(items->name, get_csv_field_slash(aux, j));
          items->price = rand() % (100 + 1)* 100; 
          items->weight = rand() % (50); 
          pushBack(room->cofre, items);
          j++;
        }else aux2 = NULL;
      }
    }else pushBack(room->cofre, get_csv_field_slash(aux, 0));
    printf("se agregan items del cofre\n");
    insertMap(Map, room->name, room);
  }
}

void main(){
  int i = 1;
  char *file;
  HashMap *Map = createMap(10);
  file = (char *)malloc(sizeof(char) * 50);

  file = "./Casas/Casa-Dificil-1.csv";
  printf("Cargando %s\n", file);
  import_file(file, Map);
  printf("se cargaron los archivos!:)\n");
  return 0;
}