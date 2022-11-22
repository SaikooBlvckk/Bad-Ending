#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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

void import_file(char *file) {
  FILE *fp = fopen(file, "r");

  char line[1024];
  char *aux;
  char *aux2;
  fgets(line, 1023, fp);
  while (fgets(line, 1023, fp) != NULL) {
    for(int i = 0; i < 7; i++){
        int j = 0;
        aux = (char *)malloc(sizeof(char) * 1024);
        aux2 = (char *)malloc(sizeof(char) * 1024);
        if (i < 5)
            printf("%s \n", get_csv_field_coma(line, i));
        strcpy(aux, get_csv_field_coma(line, i));
        if(i == 5 || i == 6){
            while (aux2 != NULL){
                if (get_csv_field_slash(aux, j) != NULL){
                    strcpy(aux2, get_csv_field_slash(aux, j));
                    printf("%s ", aux2);
                    j++;
                }else aux2 = NULL;
            }
            printf("\n");
        }
    }
  }
  printf("\n");
}

int main(){
    int i = 1;
    char *file;

    file = (char *)malloc(sizeof(char) * 50);

    file = "Casa-Dificil-1.csv";
    printf("Cargando %s\n", file);
    import_file(file);
}