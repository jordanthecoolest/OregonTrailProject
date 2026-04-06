#ifndef OREGON_TRAIL_H
#define OREGON_TRAIL_H
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
  float money;
  int ammo;
  int medicine;
  //spare parts
  int wheels;
  int axles;
  int tongues;
  int parts;
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
