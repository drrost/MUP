NAME = endgame

SRC = src/initSDL.c \
 src/cleanup.c \
 src/note_falling.c \
 src/main.c \
 src/player.c \
 src/menu.c

SDL2 = -I ./Frameworks/SDL2.framework/Versions/A/Header -F ./Frameworks -framework SDL2 -rpath ./Frameworks
SDL2_IMAGE = -I ./Frameworks/SDL2_image.framework/Versions/A/Header -F ./Frameworks/ -framework SDL2_image -rpath ./Frameworks
SDL2_MIXER = -I ./Frameworks/SDL2_mixer.framework/Versions/A/Header -F ./Frameworks -framework SDL2_mixer -rpath ./Frameworks
SDL2_TTF = -I ./Frameworks/SDL2_ttf.framework/Versions/A/Headers -F ./Frameworks/ -framework SDL2_ttf -rpath ./Frameworks

INC = inc/header.h

CC = 
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: install clean
install:
	@clang ${CFLAGS} $(SRC) -o ${NAME} ${SDL2} ${SDL2_IMAGE} $(SDL2_MIXER) ${SDL2_TTF} -I $(INC)
uninstall: clean
	rm -rf ${NAME}
clean:
	rm -rf header.h
reinstall: uninstall all
