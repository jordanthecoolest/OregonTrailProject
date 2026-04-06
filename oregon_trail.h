#define OREGON_TRAIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

//colors
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

struct person {
    char name[20];
    int health;
    int isAlive;
};

struct gameState {
    struct person party[5];
    int job;
    
    //resources
    int food;
    int oxen;
    float money;
    int ammo;
    int medicine;
    int clothing;
    
    //parts
    int wheels;
    int axles;
    int tongues;
    int parts;
    
    //progress
    int milesTraveled;
    int day;
    int month;
};

//logic & stats
int aliveCount(struct gameState *game);
void nextDay(struct gameState *game);
void changePartyHealth(struct gameState *game, int amount);

//menus & travel
void travelLoop(struct gameState *game);
int fortMenu(struct gameState *game);
int landmarkMenu(struct gameState *game);
int checkStops(struct gameState *game, int oldMiles, int newMiles);
int isFort(int miles);
int isLandmark(int miles);

//events
void shop(struct gameState *game);
void hunt(struct gameState *game);
void cross_river(struct gameState *game);
void restStop(struct gameState *game);
void sink_wagon(struct gameState *game);

//utility & systems
int errorCheck(int min, int max);
void displayLogo();
void winScreen(struct gameState *game);
void saveScore(struct gameState *game, int finalScore);
