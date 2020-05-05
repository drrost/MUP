CC = clang
CFLAG = -std=c11 -Wall -Wextra -Werror -Wpedantic -I./inc

SDL2 = -I ./resource/Frameworks/SDL2.framework/Versions/A/Header \
	-F ./resource/Frameworks -framework SDL2
SDL2_IMAGE = -I ./resource/Frameworks/SDL2_image.framework/Versions/A/Header \
	-F ./resource/Frameworks/ -framework SDL2_image
SDL2_TTF = -I ./resource/Frameworks/SDL2_ttf.framework/Versions/A/Headers \
	-F ./resource/Frameworks/ -framework SDL2_ttf
SDL2_MIX = -I ./resource/Frameworks/SDL2_mixer.framework/Versions/A/Headers \
	-F ./resource/Frameworks/ -framework SDL2_mixer

NAME = endgame

all: install clean
install:
	cp src/scene/*.c src/*.c src/util/*.c src/application/*.c inc/*.h .
	${CC} ${CFLAG} *.c -o ${NAME} ${SDL2} ${SDL2_IMAGE} ${SDL2_TTF} \
	${SDL2_MIX} -rpath ./resource/Frameworks
uninstall:
	rm -rf ${NAME}
clean:
	rm -rf *.c
	rm -rf *.h
	rm -rf *.o
reinstall: uninstall all
