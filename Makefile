SRC = main.c    \
	  src/launcher.c    \
	  src/game.c     \

CC = gcc
CFLAGS = -I include/ -Wextra -Wall -o ./build/out -no-pie

RM = rm -f

all: $(SRC)
	gcc $(SRC) $(CFLAGS)

clean:
	$(RM) ./build/*

re: clean all