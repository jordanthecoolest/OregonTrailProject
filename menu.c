#include <stdio.h>
#include <stdlib.h>


void startGame(char start){

printf ("would you like to start the game? y/n : ");
scanf (" %c", &start);

if (start == 'n' || start == 'N'){
	exit(0);
}
else if (start == 'y' || start == 'Y'){
	printf ("starting your journey... \n");
}
else {
	printf ("invalid input");
	exit(0);
}
}

void roleSelect(int character){
	printf ("Please select your role: \n 1. Banker \n 2. carpenter \n 3. farmer \n");
	printf ("You may enter the number associated with the role you want. Enter '4' to learn more about the differences in role. \n");
	scanf("%d", &character);
  
  if (character == 4){
   
			printf ("Selecting certain roles will make the game easier or harder, with banker being the easiest, and farmer being the hardest, based on the amount of money you start with.");
			printf (" Keep in mind, each role earns various points based on difficulty, the easier your character is, the less points you earn. \n");
	roleSelect(character);	
	return; 

      } 
  
	switch (character) {

		case 1: 
			printf ("You have selected the banker role, you start the game with $1600. \n");
		break;
		
		case 2: 
			printf ("You have selected the carpenter role, you start the game with $800. \n");
		break;
		
		case 3:
			printf ("You have selected the farmer role, you start the game with $400. \n");
		break;	

		default: 
			printf ("Please select one of the given options. \n");

	}


exit(0);
}


int main(){

char start;
int character;

startGame(start);
roleSelect(character);


return 0;
}
