/*********************
create ability to buy items and cycle through menu in loop
menu to buy should always be available
food
clothing
oxen
ammunition 
spare parts : wheels, axels, tongues
medicine 

all purchases are based on amount of money player starts with. 

*******************/


#include <stdio.h>

void shopDisplay(int choice){

printf ("--------------- /n");
printf ("Welcome to the shop. /n");
printf ("Please select an item you would like to buy /n");
printf (" 1. food /n 2. clothing /n 3. oxen /n 4. ammunition /n 5. medicine /n 6. spare parts/n Enter 0 to exit. /n");
printf ("--------------- /n");
scanf ("%d", &choice);

}

void buyFood(int Food){

if/ifelse or switch case 
	printf ("Food costs 20 cents per pound.");
	printf ("Please enter the quantity you would like to buy in pounds : ");
	scanf ("%d", &Food); 
	Money = Money - (Food * 0.2);
	printf ("You have bought %d pounds of food and have %f dollars left. /n", Food, Money);

costs 20 cents/lb

}

void buyClothing(int Clothes){

	printf ("clothing costs $10 per set.");
	printf ("Please enter the quantity you would like to buy in sets : ");
	scanf ("%d", &Clothes); 
	Money = Money - (Clothes * 10 );
	printf ("You have bought %d sets of clothes and have %f dollars left. /n", Clothes, Money);


}

void buyOxen(int Yokes){

	printf ("Oxen costs $40 per yoke, it is recommended you buy 3.");
	printf ("Please enter the quantity you would like to buy in yokes : ");
	scanf ("%d", &Yokes); 
	Money = Money - (Yokes * 40);
	printf ("You have bought %d yokes of oxen and have %f dollars left. /n", Yokes, Money);



}

void buyAmmo(){

	printf ("Ammunition costs $2 per box, each box contains 20 bullets.");
	printf ("Please enter the quantity you would like to buy in boxes : ");
	scanf ("%d", &Ammo); 
	Money = Money - (Ammo * 2);
	printf ("You have bought %d boxes of ammunition and have %f dollars left. /n", Ammo, Money);

}

void buyMeds(int Meds){

	printf ("Medicine costs $5 for a set, each set comes with 2 pills.");
	printf ("Please enter the quantity you would like to buy in sets : ");
	scanf ("%d", &Meds); 
	Money = Money - (Meds * 5);
	printf ("You have bought %d sets of pills and have %f dollars left. /n", Meds, Money);


}

void buyParts(){
include wheels axel tongue seperately 

if part buy selected offer 3 options (same format as shop options) 
wheels : $50 (pair of 2)
axel :$75
tongue : $50 

}

int main(){


make shopdisplay permanent loop for all options 
switch case
if total exceeds initial wallet amount 
give error



return 0;
}
