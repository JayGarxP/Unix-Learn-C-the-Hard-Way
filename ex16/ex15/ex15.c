#include <stdio.h>
#include <stdlib.h>
#include "str2int.h"

//Zelda BotW Korok upgrade calculator, can't figure out this algebra :(
int main(int argc, char * argv[])
{

	int i = 0;
	int korokSeedsNeeded = -1;
	int nthSlot = 7;
	int tax = -1;
	int totalNeeded = 0;
	for (i = 0; i < nthSlot + 1; i++){
		if(korokSeedsNeeded == -1){
			korokSeedsNeeded = 1;
			totalNeeded = 1;
		}else if (korokSeedsNeeded == 1){
			korokSeedsNeeded = 2;
			totalNeeded = 2;
			tax++;
		}else{
			korokSeedsNeeded = korokSeedsNeeded + tax;
			totalNeeded += korokSeedsNeeded;

		tax++;
		}
	}
printf("korok seeds needed to upgrade %d: %d \n for total of: %d", nthSlot, korokSeedsNeeded, totalNeeded);
	return 0;
}

