#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Functions.h"
#include "hashmap.h"

char *get_csv_field(char *tmp, int k) {
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

Player *loadGame(){
  char name[30];
  printf("Ingrese el nombre del Usuario a cargar\n");
  scanf("%s", &name);
  strcat(name, ".csv");
  FILE *fp = fopen(name, "r");
  Player *pl = (Player *)malloc(sizeof(Player));
  if (fp == NULL){
      printf("Error al abrir archivo\n");
      pl = NULL;
  }
  else{
      pl->PassedLevel = createMap(1);
      int i = 0;
      char line[1024];
      while(fgets(line, 1023, fp) != NULL){
        for (int i = 1; i < 10; i++){
            if(get_csv_field(line, i) != NULL){
                pl->playerMovement = -1;
                pl->Robbeditems = createList();
                strcpy(pl->Name, get_csv_field(line, 0));
                insertMap(pl->PassedLevel, get_csv_field(line, i), pl);
            }
        }
      }
  }
  return pl;
}

void printScoreTable(){
  FILE *fp = fopen("scoreTable.csv", "r");
  char line[1024];
  if (fp == NULL) printf("Error al abrir archivo de la tabla de puntuaciones\n");
  else{
    printf("Player, Movimientos, Dinero Total Robado, Puntaje\n");
    while(fgets(line, 1023, fp) != NULL){
      printf("%s, %s, %s, %s",get_csv_field(line, 0), get_csv_field(line, 1), get_csv_field(line, 2), get_csv_field(line, 3));
    }
  }
  fclose(fp);
}
