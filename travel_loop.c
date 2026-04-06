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
    int forts[16] = {2005, 2015, 2025, 2035, 2045, 2055, 2065, 2075, 2085, 2095, 2105, 2115, 2125, 2135, 2145, 2155};

    for (int i = 0; i < 16; i++) {
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
            printf("Shop not programmed here.\n");
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
    int paceChoice, rationChoice;
    int foodUsed, milesToday, healthChange;
    int oxenBonus, randomMiles;
    int oldMiles, newMiles;
    int restedToday;

    if (game->milesTraveled < 2000 || game->milesTraveled > 2170) {
        game->milesTraveled = 2000 + (rand() % 171);
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
        printf(GREEN "\nYou made it to Oregon!\n" RESET);
    }
}
