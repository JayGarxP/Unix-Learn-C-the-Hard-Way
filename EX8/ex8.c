#include <stdio.h>

int main(int argc, char * argv[])
{
	int i = 0;
	if (argc == 1) {
		puts("one argument");
	}
	else if (argc > 1 && argc < 4) {
		puts("Your args: ");

		for (i = 1; i < argc; i++) {
		printf("%s ", argv[i]);
		}
		printf("\n");
	}
	else {
		puts("More than two arguments");
	}
	return 0;
}
