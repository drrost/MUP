# Usage:
# make          # compile all binary

BINARY=endgame

C_FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I./inc

all: ${BINARY}

${BINARY}:
	@clang ${C_FLAGS} ./src/*.c ./src/minilib/*.c -o ${BINARY}

clean:
	@rm -f *.o

uninstall: clean
	@rm -f ${BINARY}

reinstall: uninstall all
