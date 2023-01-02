#ifndef __PROGTEST__
#include <stdio.h>
#include <assert.h>
#endif /* __PROGTEST__ */
#define DAILY 180 //cuckoos per day
#define YEARLY 65700 //cuckoos per regular year = DAILY * 365
#define YEARLYL 65880 //cuckoos per leap year = DAILY * 366
int monthDay[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; //days in each month

//leap year check
int isLeap(int year){
  if(year%4000 == 0){
    return 0;
  }
  if(year%400 == 0){
    return 1;
  }
  if(year%100 == 0){
    return 0;
  }
  if(year%4 == 0){
    return 1;
  }
  return 0;
}

//right values check
int inputCheck(int year, int month, int day, int hour, int minute){
  if(isLeap(year)){
    monthDay[1] = 29;
  }else{
    monthDay[1] = 28;
  }
  if(year < 1600 || month < 1 || month > 12 || hour < 0 || hour > 23 || day < 1 || day > monthDay[month - 1] || minute < 0 || minute > 59){
    return 1;       //2013, 10,  1,  0,  0
  }                 //2013, 10,  1, 12,  0
  return 0;
}

//count cuckoos by entire years at a time, returns sum of all years cuckoos
long long int yearsC(int year1, int year2){
  long long int cuckood = 0;
  int years = year2 - year1;
  for(int i = 0; i < years; i++){
    if(isLeap(year1 + i)){
      cuckood += YEARLYL;
    }else{
      cuckood += YEARLY;
    }
  }
  return cuckood;
}

//count how many cuckoos are in particular hour
int hourC(int hour){
  if(hour > 12){
    return hour - 12;
  }
  if(hour == 0){//not used... or is it? And do I dare to erase it? edit: It is used after all...
    return 12;
  }
  return hour;
}

int cuckooClock ( int y1, int m1, int d1, int h1, int i1, int y2, int m2, int d2, int h2, int i2, long long int * cuckoo ){
  if(inputCheck(y1,m1,d1,h1,i1) || inputCheck(y2,m2,d2,h2,i2)){
    return 0;
  }
  long long int count = 0; //is bit more readable to me than *cuckoo but it's the same thing

  //wrong input check vol. 2
  if(y1 == y2){
    if(m1 == m2){
      if(d1 == d2){
        if(h1 == h2){
          if(i1 > i2){
            return 0;
          }
        }else if(h1 > h2){
          return 0;
        }
      }else if(d1 > d2){
        return 0;
      }
    }else if(m1 > m2){
      return 0;
    }
  }else if(y1 > y2){
    return 0;
  }

  int same = 0;
  if(i1 == i2 && h1 == h2 && d1 == d2 && m1 == m2 && y1 == y2){
    same = 1;
  }

  if(i1 == 0 && !same){
    count += hourC(h1);
  }
  if(i1 == 30 && !same){
    count++;
  }

  while (i1 != i2) {
    i1++;
    if(i1 == 30){
      count++;
    }else if(i1 == 60){
      i1 = 0;
      h1++;
      if(h1 == 24){
        h1 = 0;
        d1++;
        if(d1 == monthDay[m1 - 1] + 1){
          d1 = 1;
          m1++;
          if(m1 == 13){
            m1 = 1;
            y1++;
          }
        }
      }
      count += hourC(h1);
    }
  }


  while (h1 != h2) {
    h1++;
    if(h1 == 24){
      h1 = 0;
      d1++;
      if(d1 == monthDay[m1 - 1] + 1){
        d1 = 0;
        m1++;
        if(m1 == 13){
          m1 = 1;
          y1++;
        }
      }
    }
    count += hourC(h1) + 1;// +1
  }

  if(i1 == 30 && same){
    count++;
  }
  if(i1 == 0 && same){
    count += hourC(h1);
  }

  while (d1 != d2) {
    d1++;
    if(d1 == monthDay[m1 - 1] + 1){
      d1 = 1;
      m1++;
      if(m1 == 13){
        m1 = 1;
        y1++;
      }
    }
    count += DAILY;
  }
  //25*180 = 9.2.
//printf("+%lld\n",count );
  while(m1 != m2){
    m1++;
    if(m1 == 14){
      m1 = 1;
      y1++;
    }
    count += monthDay[m1 - 2] * DAILY;
    //printf("m1 = %d, m1 \n", m1,);
    //printf("count = %lld, m1 = %d, monthday = %d\n",count, m1, monthDay[m1 - 1]);
  }

  if(y1 != y2){
    count += yearsC(y1, y2);
  }

  *cuckoo = count;
  //printf("%lld\n", count);
  return 1;

}








#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  long long int cuckoo = 0;
/*
  printf("%d - ", cuckooClock ( 2105, 1, 15, 0, 1, 2105, 3, 9, 0, 1, &cuckoo ) == 1 && cuckoo == 9540 );
  printf("%lld\n", cuckoo );
*/
/*
  assert ( cuckooClock ( 1600, 11,  30, 0, 0,
                         1600, 12,  31, 0, 0, &cuckoo ) == 1 && cuckoo == 0); */
  assert ( cuckooClock ( 2000, 12,  31, 0, 1,
                         2000, 12,  31, 0, 1, &cuckoo ) == 1 && cuckoo == 0);
  assert ( cuckooClock ( 2006, 12,  31, 0, 1,
                         2007, 12,  31, 0, 1, &cuckoo ) == 1 && cuckoo == YEARLY);
  assert ( cuckooClock ( 2005, 12,  31, 0, 0,
                         2005, 12,  31, 0, 31, &cuckoo ) == 1 && cuckoo == 13);
  assert ( cuckooClock ( 2005, 12,  31, 0, 0,
                         2005, 12,  31, 1, 0, &cuckoo ) == 1 && cuckoo == 14);
  assert ( cuckooClock ( 2005, 12,  1, 1, 1,
                         2005, 12,  31, 1, 1, &cuckoo ) == 1 && cuckoo == 5400);
  assert ( cuckooClock ( 2000, 10,  1, 13, 15,
                         4000, 10,  1, 18, 45, &cuckoo ) == 1);
  assert ( cuckooClock ( 2013, 10,  1, 13, 15,
                         2013, 10,  1, 18, 45, &cuckoo ) == 1 && cuckoo == 26 );
  assert ( cuckooClock ( 2013, 10,  1, 13, 15,
                         2013, 10,  2, 11, 20, &cuckoo ) == 1 && cuckoo == 165 );
  assert ( cuckooClock ( 2013,  1,  1, 13, 15,
                         2013, 10,  5, 11, 20, &cuckoo ) == 1 && cuckoo == 49845 );
  assert ( cuckooClock ( 2012,  1,  1, 13, 15,
                         2012, 10,  5, 11, 20, &cuckoo ) == 1 && cuckoo == 50025 );
  assert ( cuckooClock ( 1900,  1,  1, 13, 15,
                         1900, 10,  5, 11, 20, &cuckoo ) == 1 && cuckoo == 49845 );
  assert ( cuckooClock ( 2013, 10,  1,  0,  0,
                         2013, 10,  1, 12,  0, &cuckoo ) == 1 && cuckoo == 102 );
  assert ( cuckooClock ( 2013, 10,  1,  0, 15,
                         2013, 10,  1,  0, 25, &cuckoo ) == 1 && cuckoo == 0 );
  assert ( cuckooClock ( 2013, 10,  1, 12,  0,
                         2013, 10,  1, 12,  0, &cuckoo ) == 1 && cuckoo == 12 );
  assert ( cuckooClock ( 2013, 11,  1, 12,  0,
                         2013, 10,  1, 12,  0, &cuckoo ) == 0 );
  assert ( cuckooClock ( 2013, 10, 32, 12,  0,
                         2013, 11, 10, 12,  0, &cuckoo ) == 0 );
  assert ( cuckooClock ( 2100,  2, 29, 12,  0,
                         2100,  2, 29, 12,  0, &cuckoo ) == 0 );
  assert ( cuckooClock ( 2400,  2, 29, 12,  0,
                         2400,  2, 29, 12,  0, &cuckoo ) == 1 && cuckoo == 12 );
  assert ( cuckooClock ( 1928, 7, 20, 15, 28, 1988, 3, 2, 15, 55, &cuckoo ) == 1 && cuckoo == 3919501);




  return 0;
}
#endif /* __PROGTEST__ */
