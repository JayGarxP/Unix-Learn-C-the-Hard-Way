#include <stdio.h>

int main(int argc, char * argv[]){
	int i = 0;

	for (i = 1; i < argc; i++){
		printf("arg %d: %s\n", i, argv[i]);
	}

	//B e r s e r k
	char* states[] = {
		"Dark Souls I", "Dark Souls II", "Demon's Souls", "Dark Souls III"
	}; //Bloodborne is less King's Field Berserk

	int num_gaymes = 4;
	//Cprintf("len 1 = %zu\n",sizeof(names1)/sizeof(names1[0]));
	int num_games = sizeof(states)/sizeof(states[0]);
	int num_gims = sizeof(states)/sizeof(char*);
	printf("num games should be 4 it is: %d \n", num_games);
	printf("num gimes should be 4 it is: %d \n", num_gims);

	for (i = 0; i < num_gaymes; i++){
		printf("Rate thread %d: %s\n", i, states[i]);
	}


	return 0;
}
