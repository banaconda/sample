PROG = test
SRCS = $(wildcard *.c)
OBJS = $(SRCS:%.c=%.o)

CFLAGS  = -Wall -g -std=c99
LIBS = -lm

$(PROG) : $(OBJS)
	$(CC) -o $@ ${OBJS} $(LIBS)

$(OBJS) : %.o : %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	@rm *.o
	@rm ${PROG}
