OBJS = ex15.o
CC = -gcc
DEBUG = -g
CFLAGS = -Wall -Wextra $(DEBUG)
MESG = "Don't Crowd Me"

all: clean jp
	@echo $(MESG)

clean:
	rm -f $(OBJS)

jp : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o jp
