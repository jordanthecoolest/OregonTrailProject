#include <stdio.h>
//initializing stat variables
struct person {
  char name[20];
  int health;
  int isAlive;
};
struct gameState {
  //party
  struct person party[5];
  int job;
  //resources
  int food;
  int oxen;
  int money;
  int ammo;
  int medicine;
  //spare parts
  int wheels;
  int axles;
  int tongues;
  //progress
  int milesTraveled
  int day;
  int month;
};
//defining colors to keep code clean
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"
int main() {
  int mainMenu=0;
  int jobSelect=0;
  printf(GREEN"~~~~~~~~~~The Oregon Trail~~~~~~~~~~\n"RESET);
  printf("1. Travel the trail\n");
  printf("2. Learn about the trail\n");
  while ((mainMenu != 1) || (mainMenu != 2)) {
    printf("What is your choice? ");
    scanf("%d", &mainMenu);
  }
  if (mainMenu == 1) {
    printf("\nMany kinds of people made the trip to Oregon.\n");
    printf("You may:\n");
    printf("1. Be a banker from Boston\n");
    printf("2. Be a carpenter from Ohio\n");
    printf("3. Be a farmer from Illinois\n");
    printf("4. Find out the differences between these choices\n");
    while ((jobSelect != 1) && (mainMenu != 2) && (mainMenu != 3) && (mainMenu != 4))
      printf("What is your choice? ");
      scanf("%d", &jobSelect);
  }
  else {
    printf("\nBlahBlahBlah");
    
}
