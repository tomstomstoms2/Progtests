#include "stdio.h"
#include "math.h"
#include "float.h"

typedef struct circle{double x; double y; double radius;}CIRCLE;

CIRCLE inputCircle(void){
  CIRCLE circle;
  double x, y, radius;
  if(scanf("%lf %lf %lf", &x, &y, &radius) != 3 || radius <= 0){
    printf("Nespravny vstup.\n");
    circle.radius = -1;
    return circle;
  }
  circle.x = x;
  circle.y = y;
  circle.radius = radius;
  return circle;
}


int equal(CIRCLE c1, CIRCLE c2){
  if(c1.x == c2.x && c1.y == c2.y && c1.radius == c2.radius){
    printf("Kruznice splyvaji, ");
    return 1;
  }
  return 0;
}
void intersection(CIRCLE c1, CIRCLE c2, double dist){
  //printf("c1.r = %lf, c2.r = %lf\n",c1.radius, c2.radius );
  if(dist == 0){
    double minRadius;
    if(c1.radius < c2.radius){
      minRadius = c1.radius;
    }else{minRadius = c2.radius;}
    printf("prekryv: %lf\n", M_PI * pow(minRadius, 2));
  }else {
    double minRadius = c1.radius;
    double maxRadius = c2.radius;
    if(c1.radius > c2.radius){
      minRadius = c2.radius;
      maxRadius = c1.radius;
    }
    if(dist + minRadius < maxRadius){
      printf("prekryv: %lf\n", M_PI * pow(minRadius, 2));
    }else {

    double a = acos((pow(dist, 2) + pow(minRadius, 2) - pow(maxRadius, 2)) / (dist * minRadius * 2));
    double b = acos((pow(dist, 2) + pow(maxRadius, 2) - pow(minRadius, 2)) / (dist * maxRadius * 2));
    double area = pow(minRadius, 2) * a + pow(maxRadius, 2) * b - 0.5 * (pow(minRadius, 2) * sin(a * 2) + pow(maxRadius, 2) * sin(b * 2));

    printf("prekryv: %lf\n", area);
  }
  }
}

int main(int argc, char const *argv[]) {
  printf("Zadejte parametry kruznice #1:\n");
  CIRCLE circle1 = inputCircle();
  if(circle1.radius == -1){
    return 0;
  }
  printf("Zadejte parametry kruznice #2:\n");
  CIRCLE circle2 = inputCircle();
  if(circle2.radius == -1){
    return 0;
  }

  double centreDistance = fabs(sqrt(pow(circle2.x - circle1.x, 2) + pow(circle2.y - circle1.y, 2)));

  double low;
  if(centreDistance > circle1.radius){
    if(centreDistance > circle2.radius){
      if(circle1.radius > circle2.radius){
        low = circle2.radius;
      } else {low = circle1.radius;}
    }else {low = circle1.radius;}
  }else if(circle1.radius > circle2.radius){
    if(circle2.radius > centreDistance){
      low = centreDistance;
    }else {low = circle2.radius;}
  }else {low = circle1.radius;}

  if(equal(circle1, circle2)){
  }else if(circle1.radius - (circle2.radius + centreDistance) > DBL_EPSILON * low){
    printf("Kruznice #2 lezi uvnitr kruznice #1, ");
  }else if(circle2.radius - (circle1.radius + centreDistance) > DBL_EPSILON * low){
    printf("Kruznice #1 lezi uvnitr kruznice #2, ");
  }else if(centreDistance - (circle1.radius + circle2.radius) > DBL_EPSILON * low){
    printf("Kruznice lezi vne sebe, zadny prekryv.\n");
    return 0;
  }else if(fabs(centreDistance - (circle1.radius + circle2.radius)) < DBL_EPSILON * low){
    //printf(" vypocet = %.50lf\n", abs(centreDistance - (circle1.radius + circle2.radius)));
    //printf("dbl epsilon * 10000 = %.50lf\n", DBL_EPSILON * 10000);
    printf("Vnejsi dotyk, zadny prekryv.\n");
    return 0;
  }else if(fabs(centreDistance - fabs(circle1.radius - circle2.radius)) < DBL_EPSILON * low){
    if(circle1.radius - circle2.radius > DBL_EPSILON * 10000){
      printf("Vnitrni dotyk, kruznice #2 lezi uvnitr kruznice #1, ");
    }else{printf("Vnitrni dotyk, kruznice #1 lezi uvnitr kruznice #2, ");}
  }else {
    printf("Kruznice se protinaji, ");
  }
  intersection(circle1, circle2, centreDistance);
  return 0;
}
