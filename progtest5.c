#include "stdio.h"
#include "stdlib.h"
#include "string.h"


//checks for bad chars in line
//return 1 on fail
//return 0 on success
int checkDiagonal(char * line, int buffer){
  for(int i = 0; i < buffer - 1; i++){
    if(line[i] != '\\' && line[i] != '/'){
      return 1;
    }
  }
  return 0;
}

//scans diagonals lines
//returns NULL on fail
//returns filled char** on success
char ** scanDiagonals(int * counter, int * mainBuffer){
  int size = 2, buffer;
  char ** diagonals = (char**) malloc (sizeof(char*) * size);
  while(1){
    size_t buff = 1;
    char * line = (char*) malloc (sizeof(char*) * buff);

    buffer = getline(&line, &buff, stdin);
    if(*counter == 0){//set the first length of line to check if every line is the same length
      *mainBuffer = buffer;
    }
    if(line[0] == '\n'){
      free(line);
      return diagonals;
    }
    if(checkDiagonal(line, buffer) || buffer != *mainBuffer){
      printf("Nespravny vstup.\n");
      for(int i = 0; i < *counter; i++){
        free(diagonals[i]);
      }
      free(diagonals);
      free(line);
      return NULL;
    }

    if(*counter == size - 1){
      size *= 2;
      diagonals = (char**) realloc (diagonals, sizeof(char*) * size);
    }
    diagonals[*counter] = line;
    *counter += 1;
  }
}

//checks for bad chars in line
//return 1 on fail
//return 0 on success
int checkMaskLine(char * line, int buffer){
  for(int i = 0; i < buffer - 1; i++){
    if(line[i] != '#' && line[i] != '.'){
      printf("\n");
      return 1;
    }
  }
  return 0;
}

//scans mask lines
//returns NULL on fail
//returns filled char** on success
char ** scanMask(int counter, int mainBuffer){
  int buffer;
  char ** mask = (char**) malloc (sizeof(char*) * (counter + 1));
  for(int i = 0; i < counter + 1; i++){
    size_t buff = 1;
    char * line = (char*) malloc (sizeof(char*) * buff);

    buffer = getline(&line, &buff, stdin);
    if(checkMaskLine(line, buffer) || buffer != mainBuffer + 1){
      printf("Nespravny vstup.\n");
      for(int i = 0; i < counter + 1; i++){
        free(mask[i]);
      }
      free(mask);
      free(line);
      return NULL;
    }
    mask[i] = line;
  }
  return mask;
}

//compute how many diagonals each point of mask has
//returns edited char **
char ** sumDiagonals(char ** result, char ** diagonals, int counter, int mainBuffer){
  for(int i = 0; i < counter; i++){
    for(int j = 0; j < mainBuffer - 1; j++){
      if(diagonals[i][j] == '\\'){
        result[i][j] += 1;
        result[i+1][j+1] += 1;
      }else {
        result[i][j+1] += 1;
        result[i+1][j] += 1;
      }
    }
  }
  return result;
}

//implements mask into result, puts dots from mask wherever they are into result array
//returns edited char**
char ** useMask(char ** result, char ** mask, int counter, int mainBuffer){
  for(int i = 0; i < counter; i++){
    for(int j = 0; j < mainBuffer; j++){
      if(mask[i][j] == '.'){
        result[i][j] = '.';
      }
    }
  }
  return result;
}

//allocates result array, fills it with '0' for further use
//calls functions for further fill and edit the result array
//returns finished char **
char ** compute(char ** diagonals, char ** mask, int counter, int mainBuffer){
  char ** result = (char**) malloc (sizeof(char*) * (counter + 1));
    for(int i = 0; i < counter + 1; i++){
      char * line = (char*) malloc (sizeof(char) * (mainBuffer + 1));
      for(int j = 0; j < mainBuffer; j++){
        line[j] = '0';
      }
      line[mainBuffer] = '\0';
      result[i] = line;
    }

    result = sumDiagonals(result, diagonals, counter, mainBuffer);
    result = useMask(result, mask, counter + 1, mainBuffer + 1);

    return result;
}

int main(int argc, char const *argv[]) {
  int counter = 0, mainBuffer = 0;
  char ** diagonals;
  printf("Vypln:\n");
  if((diagonals = scanDiagonals(&counter, &mainBuffer)) == NULL){
    return 0;
  }
  printf("Maska:\n");
  char ** mask;
  if((mask = scanMask(counter, mainBuffer)) == NULL){
    for(int i = 0; i < counter + 1; i++){
      free(diagonals[i]);
    }
    free(diagonals);
    return 0;
  }

  char ** result = compute(diagonals, mask, counter, mainBuffer);

  for(int i = 0; i < counter + 1; i++){
    printf("%s\n", result[i]);
  }

  for(int i = 0; i < counter; i++){
    free(diagonals[i]);
  }
  free(diagonals);
  for(int i = 0; i < counter + 1; i++){
    free(mask[i]);
  }
  free(mask);
  for(int i = 0; i < counter + 1; i++){
    free(result[i]);
  }
  free(result);
  return 0;
}
