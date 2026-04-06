#include "oregon_trail.h"

void saveScore(struct gameState *game, int finalScore) {
  FILE *fptr = fopen("highscores.txt", "a");
  if (fptr == NULL) {
    printf("Error: Could not save high score.\n");
    return;
  }
  fprintf(fptr, "Name %s | Score: %d\n", game->party[0].name, finalScore);
  fclose(fptr);
  printf(CYAN "Your score has been saved to highscores.txt!" RESET "\n");
}
void winScreen(struct gameState *game){
  printf("\n\n" GREEN "*****************************************" RESET);
  printf("\n" GREEN "   CONGRATULATIONS! YOU MADE IT TO OREGON!   " RESET);
  printf("\n" GREEN "*****************************************" RESET "\n");
  int survivors = aliveCount(game);
  int survivorPoints = survivors * 500;
  int resourcePoints = (game->money / 10) + (game->food / 5);
  int multiplier = 1;
  if (game->job == 2) multiplier = 2;
  if (game->job == 3) multiplier = 3;
  int finalScore = (survivorPoints + resourcePoints) * multiplier;
  printf("\n--- FINAL STATS ---");
  printf("\nSurvivors: %d (%d pts)", survivors, survivorPoints);
  printf("\nRemaining Resources: %d pts", resourcePoints);
  printf("\nJob Multiplier: x%d", multiplier);
  printf("\n" YELLOW "TOTAL SCORE: %d" RESET "\n", finalScore);
  saveScore(game, finalScore);
  printf("\nPress Enter to exit the game...");
  while(getchar() != '\n');
  getchar();
}
int aliveCount(struct gameState *game) {
    int count = 0;
    for (int i = 0; i < 5; i++) {
        if (game->party[i].isAlive == 1) {
            count++;
        }
    }
    return count;
}
void nextDay(struct gameState *game) {
    game->day++;
    if (game->day > 30) {
        game->day = 1;
        game->month++;
    }
}
void changePartyHealth(struct gameState *game, int amount) {
    for (int i = 0; i < 5; i++) {
        if (game->party[i].isAlive == 1) {
            game->party[i].health += amount;
            if (game->party[i].health > 100) {
                game->party[i].health = 100;
            }
            if (game->party[i].health <= 0) {
                game->party[i].health = 0;
                game->party[i].isAlive = 0;
                printf(RED "%s has died.\n" RESET, game->party[i].name);
            }
        }
    }
}

int isFort(int miles) {
    int forts[5] = {102, 304, 640, 1032, 1808};
    for (int i = 0; i < 5; i++) {
        if (miles == forts[i]) {
            return 1;
        }
    }
    return 0;
}
int isLandmark(int miles) {
    if (miles >= 2010 && miles <= 2150 && miles % 20 == 10) {
        return 1;
    }
    return 0;
}
void restStop(struct gameState *game) {
    printf(CYAN "Your party rests here.\n" RESET);
    changePartyHealth(game, 10);
    if (game->food >= 10 * aliveCount(game)) {
        game->food -= 10 * aliveCount(game);
    } else {
        game->food = 0;
        changePartyHealth(game, -10);
    }
    nextDay(game);
}
int fortMenu(struct gameState *game) {
    int choice;
    while (1) {
        printf("\nYou have arrived at a fort.\n");
        printf("1. Rest\n");
        printf("2. Shop\n");
        printf("3. Leave\n");
        printf("Choice: ");
        scanf("%d", &choice);
        while (choice < 1 || choice > 3) {
            printf("Enter 1, 2, or 3: ");
            scanf("%d", &choice);
        }
        if (choice == 1) {
            restStop(game);
            return 1;
        } else if (choice == 2) {
            shop(game);
        } else {
            return 0;
        }
    }
}
int landmarkMenu(struct gameState *game) {
    int choice;
    while (1) {
        printf("\nYou have arrived at a landmark.\n");
        printf("1. Rest\n");
        printf("2. Leave\n");
        printf("Choice: ");
        scanf("%d", &choice);
        while (choice < 1 || choice > 2) {
            printf("Enter 1 or 2: ");
            scanf("%d", &choice);
        }
        if (choice == 1) {
            restStop(game);
            return 1;
        } else {
            return 0;
        }
    }
}
int checkStops(struct gameState *game, int oldMiles, int newMiles) {
    int targetMiles = newMiles;
    for (int i = oldMiles + 1; i <= newMiles; i++) {
        if (isFort(i)) {
            int choice;
            printf(YELLOW "\nYou passed a fort at mile %d.\n" RESET, i);
            printf("1. Stop here\n");
            printf("2. Pass through\n");
            printf("Choice: ");
            scanf("%d", &choice);
            while (choice < 1 || choice > 2) {
                printf("Enter 1 or 2: ");
                scanf("%d", &choice);
            }
            if (choice == 1) {
                game->milesTraveled = i;
                if (fortMenu(game) == 1) {
                    return 1;
                }
                game->milesTraveled = targetMiles;
            }
        } else if (isLandmark(i)) {
            int choice;
            printf(YELLOW "\nYou passed a landmark at mile %d.\n" RESET, i);
            printf("1. Stop here\n");
            printf("2. Pass through\n");
            printf("Choice: ");
            scanf("%d", &choice);
            while (choice < 1 || choice > 2) {
                printf("Enter 1 or 2: ");
                scanf("%d", &choice);
            }
            if (choice == 1) {
                game->milesTraveled = i;
                if (landmarkMenu(game) == 1) {
                    return 1;
                }
                game->milesTraveled = targetMiles;
            }
        }
    }
    return 0;
}
void travelLoop(struct gameState *game) {
    int paceChoice, rationChoice, actionChoice;
    int foodUsed, milesToday, healthChange;
    int oxenBonus, randomMiles;
    int oldMiles, newMiles;
    int restedToday;
    if (game->milesTraveled == 0) {
      printf(YELLOW "\nYou are departing from Independence, Missouri!\n" RESET);
    }
    while (game->milesTraveled < 2170 && aliveCount(game) > 0) {
        printf("\n" CYAN "===== TRAVEL DAY =====\n" RESET);
        printf("Date: %d/%d/1848\n", game->month, game->day);
        printf("Miles traveled: %d\n", game->milesTraveled);
        printf("Miles remaining: %d\n", 2170 - game->milesTraveled);
        printf("Food: %d\n", game->food);
        printf("Oxen: %d\n", game->oxen);
        printf("Living party members: %d\n", aliveCount(game));
        printf("\nChoose pace:\n");
        printf("1. Steady\n");
        printf("2. Strenuous\n");
        printf("3. Grueling\n");
        printf("Choice: ");
        scanf("%d", &paceChoice);
        while (paceChoice < 1 || paceChoice > 3) {
            printf("Enter 1, 2, or 3: ");
            scanf("%d", &paceChoice);
        }
        printf("\nChoose rations:\n");
        printf("1. Filling\n");
        printf("2. Meager\n");
        printf("3. Bare bones\n");
        printf("Choice: ");
        scanf("%d", &rationChoice);
        while (rationChoice < 1 || rationChoice > 3) {
            printf("Enter 1, 2, or 3: ");
            scanf("%d", &rationChoice);
        }
        printf("\nDaily Action:\n");
        printf("1. Continue Traveling\n");
        printf("2. Stop to hunt (Costs 1 day, uses 1 box of ammo)\n");
        printf("Choice: ");
        scanf("%d", &actionChoice);
        if (actionChoice == 2) {
            hunt(game);
        }
        healthChange = 0;
        if (rationChoice == 1) {
            foodUsed = 15 * aliveCount(game);
        } else if (rationChoice == 2) {
            foodUsed = 10 * aliveCount(game);
            healthChange -= 5;
        } else {
            foodUsed = 5 * aliveCount(game);
            healthChange -= 10;
        }
        if (game->food >= foodUsed) {
            game->food -= foodUsed;
        } else {
            printf(RED "Not enough food. Your party is starving.\n" RESET);
            game->food = 0;
            healthChange -= 15;
        }
        oxenBonus = game->oxen / 10;
        randomMiles = rand() % 11;
        if (paceChoice == 1) {
            milesToday = 15 + oxenBonus + randomMiles;
        } else if (paceChoice == 2) {
            milesToday = 25 + oxenBonus + randomMiles;
            healthChange -= 5;
        } else {
            milesToday = 35 + oxenBonus + randomMiles;
            healthChange -= 10;
        }
        if (game->food == 0) {
            milesToday -= 10;
            if (milesToday < 5) {
                milesToday = 5;
            }
        }

        oldMiles = game->milesTraveled;
        game->milesTraveled += milesToday;
        if (game->milesTraveled > 2170) {
            game->milesTraveled = 2170;
        }
        newMiles = game->milesTraveled;
        if ((oldMiles <500 && newMiles >= 500) ||
            (oldMiles <1000 && newMiles >= 1000) ||
            (oldMiles < 1500 && newMiles >= 1500)) {
            cross_river(game);
        }
        changePartyHealth(game, healthChange);
        if ((rand() % 100) < 10) {
            printf(YELLOW "Someone in the party got sick.\n" RESET);
            changePartyHealth(game, -15);
        }
        printf(GREEN "You traveled %d miles today.\n" RESET, milesToday);
        restedToday = checkStops(game, oldMiles, newMiles);
        if (restedToday == 0) {
            nextDay(game);
        }
    }
    if (aliveCount(game) <= 0) {
        printf(RED "\nYour party has died. Game over.\n" RESET);
    } else if (game->milesTraveled >= 2170) {
        winScreen(game);
    }
}
void shop(struct gameState *game) {
    int choice, qty;
    int inv[6] = {0};
    char *items[] = {"Food", "Clothing", "Oxen", "Ammunition", "Medicine", "Spare Parts"};
    float prices[] = {0.20, 10.00, 40.00, 2.00, 5.00, 50.00};
    char *units[] = {"lbs", "sets", "yokes", "boxes", "sets", "sets"};
    int running = 1;
    do {
        printf("\nMoney: $%.2f\n", game->money);
        printf("1. Food (20¢/lb)\n");
        printf("2. Clothing ($10/set)\n");
        printf("3. Oxen ($40/yoke)\n");
        printf("4. Ammunition ($2/box)\n");
        printf("5. Medicine ($5/set)\n");
        printf("6. Spare Parts ($50/set)\n");
        printf("0. Exit shop\n");
        printf("Choice: ");
        scanf("%d", &choice);
        if (choice == 0) {
            running = 0;
        }
        else if (choice >= 1 && choice <= 6) {
            printf("How many %s? ", items[choice-1]);
            scanf("%d", &qty);
            if (qty > 0) {
                float cost = qty * prices[choice-1];
                if (cost <= game->money) {
                    game->money -= cost;
                    switch(choice) {
                      case 1: game->food += qty; break;
                      case 2: game->clothing += qty; break;
                      case 3: game->oxen += (qty * 2); break;
                      case 4: game->ammo += (qty * 20); break;
                      case 5: game->medicine += qty; break;
                      case 6: game->parts += qty; break;
                    }
                    printf("Bought %d %s of %s. Remaining: $%.2f\n", 
                           qty, units[choice-1], items[choice-1], game->money);
                    if (choice == 3 && inv[2] < 3)
                        printf("Tip: It's recommended to have at least 3 yokes of oxen\n");
                } else {
                    printf("Not enough money! Need $%.2f\n", cost);
                }
            } else {
                printf("Quantity must be positive.\n");
            }
        } else {
            printf("Invalid choice. Please select 0-6.\n");
        }
    } while (running);
    printf("\n--- Final Inventory ---\n");
    for (int i = 0; i < 6; i++)
        printf("%s: %d %s\n", items[i], inv[i], units[i]);
}
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
void sink_wagon(struct gameState *game) {
  printf(RED "\nYour wagon swamped while crossing! You lost supplies\n" RESET);
  game->food -= (rand() % 50 + 10);
  if (game->food < 0) game->food = 0;
  game->oxen -=1;
  if (game->oxen < 0) game->oxen = 0;
  changePartyHealth(game, -20);
}
int main() {
  struct gameState game = {0};
  int mainMenu=0;
  int jobSelect=0;
  int gameRunning = 1;
  while (gameRunning) {
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
    game.day = 1;
    shop(&game);
    travelLoop(&game);
  }
  else if (mainMenu == 2) {
    printf("\n" CYAN "--- ABOUT THE OREGON TRAIL ---" RESET "\n");
    printf("Your journey begins in Independence, Missouri, and ends 2,170 miles\n");
    printf("later in Oregon City. You will face harsh weather, deep rivers,\n");
    printf("and the constant threat of disease and starvation.\n\n");
    
    printf("SUCCESS DEPENDS ON THREE THINGS:\n");
    printf("1. " YELLOW "Resources:" RESET " Manage your food and oxen wisely.\n");
    printf("2. " YELLOW "Pace:" RESET " Moving too fast kills your party; moving too slow invites winter.\n");
    printf("3. " YELLOW "Luck:" RESET " Even the best leaders can be taken down by a broken axle.\n\n");
    
    printf("Choose your profession wisely—bankers have it easy, but farmers\n");
    printf("earn the most glory (and points) at the end of the trail!\n");
    printf("\nPress Enter to return to the main menu...");
    
    while(getchar() != '\n');
    getchar();
  }
  else {
    gameRunning = 0;
  }
return 0;
}
}
