#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[])
{
	////	int ages[] = {23, 43, 12, 89, 2};
	//	char* names[] = {
	//	"Alien", "Fritz", "Maurice", "Joseph", "Abe"
	//	};
	//
	//	int count = sizeof(ages) / sizeof(int);
	//	int i = 0;
	//
	//	for (i = 0; i < count; i++){
	//		printf("%s has %d years left to live \n", names[i], ages[i]);
	//	}
	//
	//	int* cur_age = ages;
	//	char** cur_name = names;
	//
	//	for(i = 0; i < count; i++){
	//	printf("%s is %d years old...\n", *(cur_name + i), *(cur_age + i));
	//	}
	//
	//	printf("----\n");
	//
	//	for (cur_name = names, cur_age = ages;
	//			(cur_age - ages) < count; cur_name++, cur_age++){
	//		printf("%s lived %d years so far \n", *cur_name, *cur_age);
	//	}

	//rewrite all the arrays as pointers
	int * ayjizz;
	if (argc > 1){
		int number = -1;
		number = strtol(argv[1], NULL, 10); 
		ayjizz = &number;
		printf("\nPapa Bless: %d\n\n", *ayjizz);
	} else {printf("\nCome on now homey\n");}
	int six = 6;
	ayjizz = &six;

	printf("Who dat boi: %d \n", *ayjizz);


	return 0;
}

/*
 * type * ptrname
 * *ptrvalue
 * *(ptr + i)    == value of whater ptr is pointed at plus i
 * &thing the actual address of thing
 * type *ptr = &thing   ==  ptr now points to thing
 * ptr++ increment where ptr points more c++ thing
 */
