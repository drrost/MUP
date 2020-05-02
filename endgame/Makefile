NAME = endgame

SRC = src/.c \
	src/.c \
	src/.c \

SDL2 = -I ./Frameworks/SDL2.framework/Versions/A/Header -F ./Frameworks -framework SDL2
SDL2_IMAGE = -I ./Frameworks/SDL2_image.framework/Versions/A/Header -F ./Frameworks/ -framework SDL2_image
SDL2_TTF = -I ./Frameworks/SDL2_ttf.framework/Versions/A/Headers -F ./Frameworks/ -framework SDL2_ttf

INC = inc/header.h

CC = 
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean
install:
	@clang ${CFLAGS} $(SRC) -o ${NAME} ${SDL2} ${SDL2_IMAGE} ${SDL2_TTF} -rpath ./frameworks -I $(INC)
uninstall: clean
	rm -rf ${NAME}
clean:
	rm -rf header.h
reinstall: all

