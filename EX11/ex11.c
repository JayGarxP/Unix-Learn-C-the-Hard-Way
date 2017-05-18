#include <stdio.h>

int main( int argc, char * argv[]){
	int number[4] = { 0 }; //initialize all elements to 0
	char name[4] = {'a'};

	//print one by one like a caveman
	printf("numbas: %d %d %d %d\n", number[0], number[1], number[2], number[3]);
	printf("name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);
	printf("name[2]: %c\n", name[2]);
	printf("Name as string %s\n", name); //prints only 'a' because of '\0'
//Press 'Y' in vim command mode to copy a line - p to paste it 'P' will paste on line above
	number[0] = 6;
	number[1] = 7;
	number[2] = 8;
	number[3] = 9;

	name[0] = 'J';
	name[1] = 'P';
	name[2] = 'X';
	name[3] = '\0';


	printf("numbas: %d %d %d %d\n", number[0], number[1], number[2], number[3]);
	printf("name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);
	printf("name as string after initing %s\n", name);

	char * JOB_CEBA = "BUBbuhdudUH";
	printf("His nabe? %s \n", JOB_CEBA);
	printf("Perfect size = %c", JOB_CEBA[0]); //#flatisjustice


	return 0;
}
