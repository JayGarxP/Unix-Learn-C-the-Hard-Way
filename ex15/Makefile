OBJS = ex15.o
HEADERS = str2int.h
CC = -gcc
DEBUG = -g
CFLAGS = -Wall -Wextra $(DEBUG)
MESG = "Don't Crowd Me"

all: clean jp
	@echo $(MESG)

clean:
	rm -f $(OBJS)

jp : $(OBJS) $(HEADERS)
	$(CC) $(CFLAGS) $(OBJS) -o jp
