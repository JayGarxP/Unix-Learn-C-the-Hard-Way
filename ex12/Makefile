OBJS = ex12.o
CC = -gcc
DEBUG = -g
CFLAGS = -Wall -Wextra $(DEBUG)
MESG = "MAKE YANNERS HAPPY"

all: clean jp
	@echo $(MESG)

clean:
	rm -f $(OBJS)

jp : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o jp
