#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "str2int.h"
//CygWin contains does NOT support all of POSIX, it actually sux. Can't check for memory leaks easily or fork() reliably. Going to have to switch to new environment. :(
//typing this within ubuntu terminal on different machine from year 2010
//struct Person {
//	char*name;
//	int age;
//	int height;
//	int weight;
//};

//On certain machines and worse versions of C you will have to use gory syntax to avoid namespace issues;
//for example, if you were using this struct in another file (forward declaration)
typedef struct UnimportantPerson {
	char*name;
	int age;
	int height;
	int weight;
}Person;

//struct Person* Person_create(char*name, int age, int height, int weight)
Person * Person_create(char*name, int age, int height, int weight)
{
	//struct Person* newPerson = malloc(sizeof(struct Person));
	Person * newPerson = malloc(sizeof(Person));
	assert(newPerson != NULL); //malloc will point to NULL if malloc couldn't allocate any memory for ya

	newPerson->name = strdup(name);
	newPerson->age = age;
	newPerson->height = height;
	newPerson->weight = weight;

	return newPerson;
}

//VALGRIND is not supported in CygWin :( going to try 'dmalloc' custom tool; dmalloc isn't working either, I'm either missing packages or it doesn't work on x64 CygWin :(
//void Person_destroy(struct Person * whomst)
void Person_destroy(Person * whomst)
{
	assert(whomst != NULL);
	free(whomst->name);
	free(whomst);
}

//If only I'd thought of the right words, I could have held onto your heart
//void Person_print(struct Person *who)
void Person_print(Person* who)
{
	assert(who != NULL);
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
	printf("\tHeight: %d\n", who->height);
	printf("\tWeight: %d\n", who->weight);
}

void Person_printStack(Person hoo)
{
	printf("Name: %s\n", hoo.name);
	printf("\tAge: %d\n", hoo.age);
	printf("\tHighness: %d\n", hoo.height);
	printf("\tWeight: %d\n\n", hoo.weight);
}

//If only I'd thought of the right words, I wouldn't be breaking apart

int main(int argc, char * argv[])
{
	//struct Person * Qui = Person_create("BonQuiQui", 32, 64, 140);
	Person * Qui = Person_create("BonQuiQui", 32, 64, 140);
	//struct Person * SarahBarthel = Person_create("Sarah", 20, 72, 180);
	Person * SarahBarthel = Person_create("Sarah", 20, 72, 180);

	printf("Qui is at memory location %p: \n", Qui);
	Person_print(Qui);

	printf("Sarah is at memory location %p:\n", SarahBarthel);
	Person_print(SarahBarthel);

	Qui->age += 20;
	Person_print(Qui);


	Person_print(SarahBarthel);

	Person_destroy(Qui);
	Person_destroy(SarahBarthel);

	//Assert test
//	Person_destroy(NULL);
//	C security check
//	Person_print(NULL);


	char Tsumtin[100]  = "Process";

	Person Sampha;
	Sampha.name = Tsumtin;
	Sampha.age = 23;
	Sampha.height = 1;
	Sampha.weight = 6;

	Person_printStack(Sampha);

	Person* PlasticSampha = &Sampha;

	Person_print(PlasticSampha);


return 0;
}

