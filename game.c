#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
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
void hunt(struct gameState *game) {
  if (game->ammo < 1) {
    printf(RED "You don't have any ammunition!\n" RESET);
    return;
  }
  //game instructions
  printf("\n" GREEN "~~~ HUNTING INSTRUCTIONS ~~~" RESET "\n");
  printf("1. An animal will appear\n");
  printf("2. Wait for the " CYAN "!!! NOW !!!" RESET " prompt.\n");
  printf("3. Type the keyword " RED "BANG" RESET " exactly as shown.\n");
  printf("4. Speed is key!: < 2.5 seconds rewards max meat!\n");
  printf(GREEN "\nPress enter when you are ready to start hunting..." RESET);
  //buffer clear and wait for enter
  while(getchar() != '\n');
  getchar();
  //game start
  printf("\n" YELLOW "Searching for game..." RESET "\n");
  //randomized delay
  int delay = (rand() % 4000000) + 1000000;
  usleep(delay);
  char *targetWord = "BANG";
  time_t start, end;
  //start reflex test
  printf(CYAN "!!! NOW !!!" RESET "\n");
  time(&start);
  char input[20];
  scanf("%s", input);
  time(&end);
  double elapsed = difftime(end, start);
  game->ammo -= 1;
  //logic based on reflex speed
  if (strcmp(input, targetWord) == 0) {
    if (elapsed < 2.5) {
      printf(GREEN "Incredible reflexes! You got 100 lbs of food.\n" RESET);
      game->food += 100;
    }
    else {
      printf(YELLOW "You got it, but you were slow. You got 20 lbs of food.\n" RESET);
      game->food += 20;
    }
  }
  else {
    printf(RED "You missed! The animal escaped.\n" RESET);
  }
}
void cross_river(struct gameState *game) {
    //generating river conditions
    int depth = (rand() % 5) + 2;
    int choice = 0;

    printf("\n" BLUE "~~~ RIVER CROSSING ~~~" RESET "\n");
    printf("The river is %d feet deep.\n", depth);
    printf("1. Ford the river (drive across)\n");
    printf("2. Caulk the wagon and float\n");
    printf("3. Pay $5 for the ferry\n");
    printf("What is your choice? ");
    scanf("%d", &choice);
    int chance = rand() % 10;
    //fording the river
    if (choice == 1) {
        if (depth > 3) {
            if (chance < 7) sink_wagon(game); 
            else printf(GREEN "You barely made it across!\n" RESET);
        } else {
            printf(GREEN "You crossed safely.\n" RESET);
        }
    } 
    //caulking across the river
    else if (choice == 2) {
        if (chance < 2) sink_wagon(game);
        else printf(GREEN "The wagon floated across successfully!\n" RESET);
    }
    //ferry across the river
    else if (choice == 3) {
        if (game->money >= 5) {
            game->money -= 5;
            printf(GREEN "The ferryman takes you across safely.\n" RESET);
        } else {
            printf(RED "You don't have enough money for the ferry!\n" RESET);
            cross_river(game);
        }
    }
}
void random_event(struct gameState *game) {
  int chance = ramd() % 100;
  if (chance < 75) {
    return;
  }
  if (chance >= 75 && chance < 85) {
    printf(YELLOW "\nYou found an abandoned wagon! You scavenged 20 lbs of food." RESET);
    game->food += 20;
  }
  else if (chance >= 80 && chance < 85) {
    printf(RED "\nRough terrain! One of your wheels broke." RESET "\n");
    game->wheels--;
    if (game->wheels < 0) game->wheels = 0;
  }
  else if (chance >= 85 && chance < 90) {
    int victim = rand() % 5;
    if (game->party[victim].isAlive) {
      printf(RED "\n%s has contracted dysentary." RESET "\n", game->party[victim].name);
      game->party[victim].health -= 20;
    }
  }
  else if (chance >= 90 && chance < 95) {
    printf(GREEN "\nHeavy rain! The grass is lush; your oxen are rested (+5 miles)." RESET "\n");
    game->milesTraveled += 5;
  }
  else {
    printf(MAGENTA "\nA traveling trader approaches." RESET "\n");
    //ADD TRADING LOGIC HERE LATER!!!!!
  }
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
    //prompting user for character names
    printf("What is the first name of your wagon leader?: ");
    scanf("%s", game.party[0].name);
    game.party[0].health = 100;
    game.party[0].isAlive = 1;
    printf("\nWho are the other members of your party?:");
    for (int i = 1; i < 5; i++) {
        printf("\nName of member %d: ", i + 1);
        scanf("%s", game.party[i].name);
        game.party[i].health = 100;
        game.party[i].isAlive = 1;
    }
    //prompting user for departure month
    printf("\n\nIt is 1848. Your jumping off place for Oregon is Independence,\n");
    printf("Missouri. You must decide which month to leave Independence.\n\n");
    printf("1. March\n2. April\n3. May\n4. June\n5. July\n6. Ask for advice");
    int monthChoice = 0;
    while (monthChoice < 1 || monthChoice > 5) {
      printf("\nWhat is your choice?: ");
      scanf("%d", &monthChoice);
      if (monthChoice == 6) {
        printf("\nIf you leave too early, there won't be any grass for your oxen");
        printf("\nto eat. If you leave too late, you may not get to Oregon before");
        printf("\nwinter comes. If you leave at just the right time, there will be");
        printf("\ngreen grass and the weather will still be cool.");
        monthChoice = 0;
      }
    }
    game.month = monthChoice + 2;
    game.day = 1
  }
  else {
    printf("\nBlahBlahBlah");
  }
}
