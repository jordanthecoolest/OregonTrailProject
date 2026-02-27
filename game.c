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
  //resources
  int food;
  int oxen;
  int money;
  int ammo;
  //spare parts
  int wheels;
  int axles;
  int tongues;
  //progress
  int milesTraveled
  int day;
  int month;
};
  
int main() {

}
