OBJS = ex8.o
CC = -gcc
DEBUG = -g
CFLAGS = -Wall -Wextra $(DEBUG)
MESG = "JP ROCKS"

all: clean jp
	@echo $(MESG)

clean:
	rm -f $(OBJS)

jp : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o jp
