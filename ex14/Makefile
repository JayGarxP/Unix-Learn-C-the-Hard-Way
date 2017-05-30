OBJS = ex14.o
CC = -gcc
DEBUG = -g
CFLAGS = -Wall -Wextra $(DEBUG)
MESG = "It's not worth it..."

all: clean jp
	@echo $(MESG)

clean:
	rm -f $(OBJS)

jp : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o jp
