#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "list.c"
#include "hashmap.c"

typedef struct{
  char name[30];
  List items;

  char up[30];
  char down[30];
  char right[30];
  char left[30];
}Room;

typedef struct{
  char name[30];
  int weight;
  int price; 
}item;

const char *get_csv_field_coma(char *tmp, int k) {
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

const char *get_csv_field_slash(char *tmp, int k) {
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

void createHouse(HashMap *Map, Room *room){
  insertMap(Map, room->name, room);
}

void import_file(char *file, HashMap *Map) {
  FILE *fp = fopen(file, "r");

  char line[1024];
  char *aux;
  char *aux2;
  fgets(line, 1023, fp);
  while (fgets(line, 1023, fp) != NULL) {
    //int j = 0;
    Room *room = (Room *)malloc(sizeof(Room));
    strcpy(room->name, get_csv_field_coma(line, 0));
    strcpy(room->up, get_csv_field_coma(line, 1));
    strcpy(room->down, get_csv_field_coma(line, 2));
    strcpy(room->left, get_csv_field_coma(line, 3));
    strcpy(room->right, get_csv_field_coma(line, 4));

    createHouse(Map, room);

    /*if(i == 5 || i == 6){
        while (aux2 != NULL){
          if (get_csv_field_slash(aux, j) != NULL){
            strcpy(aux2, get_csv_field_slash(aux, j));
            printf("%s ", aux2);
            j++;
          }else aux2 = NULL;
        }
      printf("\n");
    }*/
  }
  printf("\n");
}

int main(){
  int i = 1;
  char *file;
  HashMap *Map = createMap(10);
  file = (char *)malloc(sizeof(char) * 50);

  file = "./Casas/Casa-Dificil-1.csv";
  printf("Cargando %s\n", file);
  import_file(file, Map);

  Pair *aux = firstMap(Map);
  Room *room = (Room *)malloc(sizeof(Room));
  do{
    room = aux->value;
    printf("%s\n arriba: %s\n abajo: %s\n izquierda: %s\n derecha: %s\n", room->name, room->up, room->down, room->left, room->right);
    aux = nextMap(Map);
  }while(aux != NULL);
}