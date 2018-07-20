all:	compdir

compdir:	compdir.o
	gcc -o compdir compdir.o 

compdir.o:	compdir.c
	gcc -c compdir.c 

clean:
	rm -f *.o
	rm -f compdir
