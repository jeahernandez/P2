# Target library
lib := libuthread.a
objs := queue.o uthread.o preempt.o context.o

CC := gcc
CFLAGS := -Wall -Wextra -Werror
CFLAGS += -g

all: $(lib)

$(lib): $(objs)
 	ar rcs $(lib) $(objs)
 	#https://stackoverflow.com/questions/11344547/how-do-i-compile-a-static-library

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
    rm -f $(lib) $(objs)
