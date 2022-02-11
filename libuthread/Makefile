# Target library
lib := libuthread.a
objs := queue.o uthread.o preempt.o context.o

CC := gcc
CFLAGS := -Wall -Wextra -Werror
CFLAGS += -g

all: $(lib)

$(lib): $(objs)
	ar rcs $(lib) $(objs)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(lib) $(objs)
