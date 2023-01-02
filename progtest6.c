#include "stdio.h"
#include "string.h"
#include "stdlib.h"

typedef struct user{char * number; char * name; user * next; user * prev;}USER;

USER * parseStr(char * str, char * cmd){
  USER * tmp = (USER*) malloc (sizeof(USER));
  int len = strlen(str);
  if(str[0] != '-' && str[0] != '+' && str[0] != '?'){
    free(str);
    free(tmp);
    return NULL;
  }
  *cmd = str[0];
  if(str[1] != ' '){
    free(str);
    free(tmp);
    return NULL;
  }
  int i = 1;
  int offset = 0;
  while(str[i] == ' '){
    offset++;
    i++;
  }
  if(str[i] < '0' || str[i] > '9'){
    free(str);
    free(tmp);
    return NULL;
  }
  int size = 10;
  char * num = (char*) malloc (sizeof(char) * size);
  for(; i < len; i++){
    if(i - offset + 1 == size){
      size *= 2;
      num = (char*) realloc (num, sizeof(char) * size);
    }
    if(str[i] == ' '){
      num[i - offset - 1] = '\0';
      break;
    }
    if(str[i] == '\n' && *cmd == '-'){
      num[i - offset - 1] = '\0';
      break;
    }
    if(str[i] == '\n' && *cmd == '?'){
      num[i - offset - 1] = '\0';
      break;
    }
    if(str[i] < '0' || str[i] > '9'){
      free(str);
      free(num);
      free(tmp);
      return NULL;
    }
    num[i - offset - 1] = str[i];
  }
  tmp->number = num;
  if(*cmd == '-' || *cmd == '?'){
    if(str[i] != '\n'){
      free(str);
      free(tmp->number);
      free(tmp);
      return NULL;
    }
    free(str);
    return tmp;
  }

  if(str[i] != ' '){
    free(str);
    free(tmp->number);
    free(tmp);
    return NULL;
  }
  i++;
  while(str[i] == ' '){
    i++;
  }
  if(str[i] != '"' || str[len - 2] != '"' || str[len - 1] != '\n'){
    free(str);
    free(tmp->number);
    free(tmp);
    return NULL;
  }
  i++;
  size = 10;
  char * nm = (char*) malloc (sizeof(char) * size);
  nm[0] = '"';
  int start = i;
  for(; i < len; i++){
    if(i - start + 3 == size){//+3 + offset??
      size *= 2;
      nm = (char*) realloc (nm, sizeof(char) * size);
    }
    nm[i - start + 1] = str[i];
  }
  nm[i - start] = '\0';
  free(str);
  tmp->name = nm;
  tmp->next = NULL;
  tmp->prev = NULL;
  return tmp;
}

void freeC(USER * tmp){
  while(tmp){
    USER * next = tmp->next;
    free(tmp->name);
    free(tmp->number);
    free(tmp);
    tmp = next;
  }
}

USER * findNumber(USER * tmp, USER * start){
  if(start == NULL){
    return NULL;
  }
  USER * iterator = start;
  while(iterator){
    if(!strcmp(iterator->number,tmp->number)){
      return iterator;
    }
    iterator = iterator->next;
  }
  return NULL;
}

USER * addNew(USER * tmp, USER * end){
  if(end == NULL){
    tmp->prev = NULL;
    tmp->next = NULL;
    return tmp;
  }
  end->next = tmp;
  tmp->next = NULL;
  tmp->prev = end;

  return tmp;
}

void update(USER * tmp, USER * position){
  int len = strlen(tmp->name);
  len++;
  free(position->name);
  position->name = (char*) malloc (sizeof(char) * len);
  strcpy(position->name,tmp->name);
  free(tmp->name);
  free(tmp->number);
  free(tmp);
}

void delUser(USER * position){
  USER * prev, * next;
  prev = position->prev;
  next = position->next;
  if(prev){
    prev->next = next;
  }
  if(next){
    next->prev = prev;
  }
  free(position->number);
  free(position->name);
  free(position);
}

USER * findT9(USER * tmp, USER * start, int * counter, USER * found1){
  USER * iterator = start;
  USER * found = NULL;;// = (USER*) malloc (sizeof(USER));
  char * name;
  while(iterator){
    int len = strlen(iterator->name);
    name = (char*) malloc (sizeof(char) * (len + 2));
    //len - 1?
    int i;
    for(i = 1; i < len - 1; i++){
      char c = iterator->name[i];
      if(c == ' ' || c == '1'){
        name[i - 1] = '1';
        continue;
      }
      if(c == '2' || c == 'a' || c == 'b' || c == 'c' || c == 'A' || c == 'B' || c == 'C'){
        name[i - 1] = '2';
        continue;
      }
      if(c == '3' || c == 'd' || c == 'e' || c == 'f' || c == 'D' || c == 'E' || c == 'F'){
        name[i - 1] = '3';
        continue;
      }
      if(c == '4' || c == 'g' || c == 'h' || c == 'i' || c == 'G' || c == 'H' || c == 'I'){
        name[i - 1] = '4';
        continue;
      }
      if(c == '5' || c == 'j' || c == 'k' || c == 'l' || c == 'J' || c == 'K' || c == 'L'){
        name[i - 1] = '5';
        continue;
      }
      if(c == '6' || c == 'm' || c == 'n' || c == 'o' || c == 'M' || c == 'N' || c == 'O'){
        name[i - 1] = '6';
        continue;
      }
      if(c == '7' || c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 'P' || c == 'Q' || c == 'R' || c == 'S'){
        name[i - 1] = '7';
        continue;
      }
      if(c == '8' || c == 't' || c == 'u' || c == 'v' || c == 'V' || c == 'U' || c == 'V'){
        name[i - 1] = '8';
        continue;
      }
      if(c == '9' || c == 'w' || c == 'x' || c == 'y' || c == 'z' || c == 'W' || c == 'X' || c == 'Y' || c == 'Z'){
        name[i - 1] = '9';
        continue;
      }
      name[i - 1] = '0';
    }
    name[i - 1] = '\0';
    if(!strcmp(name,tmp->number)){
      if(!(iterator == found1)){
        *counter += 1;
      }
      found = iterator;
    }
    iterator = iterator->next;
    free(name);
  }
  return found;
}

int main(int argc, char const *argv[]) {
  printf("PBX configuration (+ = set, - = delete, ? = test, EOF = quit):\n");
  size_t buffer = 1;
  USER * start = NULL;
  USER * end = NULL;
  while(1){
    char * str = (char*) malloc (sizeof(char) * buffer);
    if(getline(&str, &buffer, stdin) == -1){
      free(str);
      break;
    }
    char cmd;
    USER * tmp = parseStr(str, &cmd);
    if(tmp == NULL){
      printf("INVALID COMMAND\n");
      continue;
    }

    if(cmd == '+'){
      USER * position;
      if((position = findNumber(tmp, start))){
        update(tmp, position);
        printf("UPDATED\n");
        continue;
      }else{
        end = addNew(tmp, end);
        if(start == NULL){
          start = end;
        }
        printf("NEW\n");
        continue;
      }
    }

    if(cmd == '-'){
      USER * position;
      if((position = findNumber(tmp, start))){
        free(tmp->number);
        free(tmp);
        if(position == start){
          start = start->next;
        }
        if(position == end){
          end = end->prev;
        }
        delUser(position);
        printf("DELETED\n");
        continue;
      }else{
        printf("NOT FOUND\n");
        free(tmp->number);
        free(tmp);
        continue;
      }
    }

    if(cmd == '?'){
      USER * found1, * found2;
      int counter = 0;
      if((found1 = findNumber(tmp, start))){
        counter++;
      }
      if((found2 = findT9(tmp, start, &counter, found1))){
      }
      if(counter == 0){
        printf("NOT FOUND\n");
        free(tmp->number);
        free(tmp);
        continue;
      }
      if(counter == 1){
        if(found1){
          int len = strlen(found1->name);
          found1->name[0] = '(';
          found1->name[len -1] = ')';
          printf("FOUND %s %s\n",found1->number, found1->name);
          found1->name[0] = '"';
          found1->name[len -1] = '"';
          free(tmp->number);
          free(tmp);
          continue;
        }
        int len = strlen(found2->name);
        found2->name[0] = '(';
        found2->name[len -1] = ')';
        printf("FOUND %s %s\n", found2->number, found2->name);
        found2->name[0] = '"';
        found2->name[len -1] = '"';
        free(tmp->number);
        free(tmp);
        continue;
      }
      printf("AMBIGUOUS (%d matches)\n", counter);
      free(tmp->number);
      free(tmp);
      continue;
    }
  }

  freeC(start);
  return 0;
}
