#include "stdio.h"
#include "math.h"
#include "float.h"

int counter = 0, size = 100;
int * perfects = (int*) malloc (sizeof(int) * size);

int cmp(const void *a, const void *b){
  int m = *(const int*)a;
  int n = *(const int*)b;
  return (m > n) - (m < n);
}

void addNum(int num){
  if(counter + 2 > size){
    size *= 2;
    perfects = (int*) realloc (perfects, sizeof(int) * size);
  }
  perfects[counter] = num;
  counter++;
  qsort(perfects, counter, sizeof(int), cmp);
}

int findInArray(int num, int start, int end){
  if (end >= start) {
    int half = start + (end - start)/2;
    if(perfects[half] == num){
      return 1;
    }else if(perfects[half] > num){
      return findInArray(num, start, half - 1);
    }else {return findInArray(num, half + 1, end);}
  }
  return 0;
}

int compute(int num){
  for(int i = 2; i <= sqrt(num); i++){
    if (num%i == 0) {
      int power = log(num)/log(i) + DBL_EPSILON * 1e5;
      if(pow(i, power) == num){
        addNum(num);
        return 1;
      }
    }
  }
  return 0;
}

int count(int start, int end){
  int count = 0;
  for(int i = start; i <= end; i++){
      if(findInArray(i, 0, counter - 1)){
        count++;
      }else if(compute(i)){
        count++;
      }
  }
  if(start == 1){
    count++;
  }
  return count;
}


int main(int argc, char const *argv[]) {
  int start, end, endCount, check;

  printf("Intervaly:\n");
  while(1){
    if((check = scanf(" %d %d", &start, &end)) == EOF){
      return 0;
    }
    if(check != 2 || start > end || start < 1){
      printf("Nespravny vstup.\n");
      return 0;
    }

    endCount = end - start - count(start, end) + 1;
    printf("<%d;%d> -> %d\n",start, end, endCount);

  }

  free(perfects);
  return 0;
}
