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

void travelLoop(struct gameState *game) {
    int paceChoice, rationChoice;
    int foodUsed, milesToday, healthChange;
    int oxenBonus, randomMiles;

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

        game->milesTraveled += milesToday;
        if (game->milesTraveled > 2170) {
            game->milesTraveled = 2170;
        }

        changePartyHealth(game, healthChange);

        if ((rand() % 100) < 10) {
            printf(YELLOW "Someone in the party got sick.\n" RESET);
            changePartyHealth(game, -15);
        }

        printf(GREEN "You traveled %d miles today.\n" RESET, milesToday);

        nextDay(game);
    }

    if (aliveCount(game) <= 0) {
        printf(RED "\nYour party has died. Game over.\n" RESET);
    } else if (game->milesTraveled >= 2170) {
        printf(GREEN "\nYou made it to Oregon!\n" RESET);
    }
}
