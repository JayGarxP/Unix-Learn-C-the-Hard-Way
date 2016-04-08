#include <stdio.h>

int main(int argc, char * argv[])
{
    int distance = 32;
    float power = 2.345f;
    double super_power = 56789.45321;
    char initial = 'A';
    char first_name[] = "$$$ZED$$$";
    char last_name[] = "$hawman";


    printf("distance: %d \n",distance);
    printf("float: %f \n",power);
    printf("double: %f \n",super_power);
    printf("char: %c \n",initial);
    printf("char array: %s \n",first_name);
    printf("char array: %s \n",last_name);
    printf("Lethal Combo: %s %c %s \n",first_name, initial, last_name);


    printf("Octal Nummer: %o \n",distance);
    printf("Hex Nummer: %x \n",distance);

    return 0;
}
