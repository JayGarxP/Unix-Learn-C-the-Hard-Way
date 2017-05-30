//JP IS COOL GUY
#include <stdio.h>
#include <ctype.h> //isalpha
#include <string.h>

//forward declaration is giving a function prototype {empty} before the compiler sees its definition {full of crap}
//Proper use of forward declaration reduces build times and stops dependent reference circles

int can_print_it(char ch);
void print_letters(char arg[]);
void print_strings(char arg[], int len);

void print_arguments(int argc, char*argv[])
{
	int i = 0;
	for (i = 0; i < argc; i++) {
		int strLangff = strlen(argv[i]);
		print_strings(argv[i], strLangff);
		//print_letters(argv[i]);
	}

}

void print_letters(char arg[])
{
	int i = 0;
	for (i = 0; arg[i] != '\0'; i++){
	char ch = arg[i];

	if (can_print_it(ch)) {
		printf("'%c' == %d ", ch, ch);
	}
	}

	printf("\n");
}

void print_strings(char arg[], int strLength)
{
	int i = 0;
	for(i = 0; i < strLength; i++){
	char ch = arg[i];	
	if (can_print_it(ch)) {
		printf("'%c' == %d ", ch, ch);
	}
	
	}
	printf("\n");
}

//return 1 if ch is an alphabet simble or be a blank simbull
int can_print_it(char ch)
{
	int bigifTrue = 777;
	bigifTrue = isalpha((int)ch) || isblank((int)ch);
	//printf("  bigifTrue: %d   ",bigifTrue);
	return bigifTrue;
}

int main(int argc, char * argv[])
{
	print_arguments(argc, argv);
	return 0;
}
