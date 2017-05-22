#include <stdio.h>
//autoformat code with gg=G in vim, set:cindent set:autoindent not working for me
int main(int argc, char * argv[]){
	int area[] = {10, 12, 13, 14, 20};
	char name[] = "Abraham";

	char full_name[] = { 'A', 'b', 'e', '\0' };
	printf("Size of int: %ld\n", sizeof(int));

	printf("Size of int array with 5 elements: %ld\n", sizeof(area));

	printf("Sizeof array divided by size of element: %ld\n", 
			sizeof(area) / sizeof(int));
	printf("My she is a dimepiece, she is a %d\n", area[0]);

	printf("Size of char: %ld\n", sizeof(char));
	printf("Size of %s char[]: %ld\n", name, sizeof(name));
	printf("Number of chars: %ld\n", sizeof(name) / sizeof(char));

	printf("Size of fullname %ld\n", sizeof(full_name));
	printf("Its number of charizards %ld\n", sizeof(full_name) / sizeof(char));
	printf("Ishmael... call me... %s\n", full_name);

	return 0;
}
