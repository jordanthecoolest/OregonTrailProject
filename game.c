#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
  int milesTraveled;
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
  struct gameState game = {0};
  int mainMenu=0;
  int jobSelect=0;
  printf(GREEN"~~~~~~~~~~The Oregon Trail~~~~~~~~~~\n"RESET);
  printf("1. Travel the trail\n");
  printf("2. Learn about the trail\n");
  while ((mainMenu != 1) && (mainMenu != 2)) {
    printf("What is your choice? ");
    scanf("%d", &mainMenu);
  }
  if (mainMenu == 1) {
    while ((jobSelect < 1) || (jobSelect > 3)) {
      printf("\nMany kinds of people made the trip to Oregon.\n");
      printf("You may:\n");
      printf("1. Be a banker from Boston\n");
      printf("2. Be a carpenter from Ohio\n");
      printf("3. Be a farmer from Illinois\n");
      printf("4. Find out the differences between these choices\n");
      printf("What is your choice? ");
      scanf("%d", &jobSelect);
      if (jobSelect == 4) {
        printf("\nTravelling to Oregon Isn't easy! But if you're a banker,\n");
        printf("you'll have more money for supplies and services than a\n");
        printf("carpenter or a farmer.\n");
        printf("\n");
        printf("However, the harder you have to try, the more points you\n");
        printf("deserve! Therefore, the farmer earns the greatest number\n");
        printf("of points and the banker earns the least.\n");
        jobSelect=0;
      }
    }
    game.job = jobSelect;
    if (game.job == 1) game.money = 1600;
    else if (game.job == 2) game.money = 800;
    else if (game.job == 3) game.money = 400;
    printf("What is the first name of your wagon leader?: ");
    scanf("%s", game.party[0].name);
    game.party[0].health = 100;
    game.party[0].isAlive = 1;
    printf("\nWho are the other members of your party?:");
    for (int i = 1; i < 4; i++) {
        printf("\nName of member %d: ", i + 1);
        scanf("%s", game.party[i].name);
        game.party[i].health = 100;
        game.party[i].isAlive = 1;
    }
    printf("\n\nIt is 1848. Your jumping off place for Oregon is Independence,\n");
    printf("Missouri. You must decide which month to leave Independence.\n\n");
    printf("1. March\n2. April\n3. May\n4. June\n5. July\n6. Ask for advice");
    
  }
  else {
    printf("\nBlahBlahBlah");
  }
}
