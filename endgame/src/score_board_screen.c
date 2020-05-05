#include "header.h"

int scoreboard(SDL_Renderer *renderer) {
	bool running = true;
	SDL_Event event;
	if(TTF_Init() ==-1) {
		printf("TTF_Init:%s\n", TTF_GetError());
		exit(2);
	}
	int page = 0;
	TTF_Font *font = TTF_OpenFont(path_for_res("ARIAL.TTF"), 25);

	SDL_Color colorGR = {255, 255, 0, 255};
    // SDL_Color colorGR = {155, 255, 0, 255};


    SDL_Rect backgroundRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_Texture *imageBackground = IMG_LoadTexture(renderer, "resources/empty_back.png");

    while(running) {
    	int file = open("scoreboard/scoreboard.txt", O_RDWR | O_APPEND, S_IRUSR | S_IWUSR | S_IXUSR);
    	int status = 1;
    	int i = 0;
    	int y = 6;
    	int z = 0;
    	int topage = 6;
    	SDL_RenderCopy(renderer, imageBackground, NULL, &backgroundRect);
    	draw_text(colorGR, 800, 100, "Scoreboard", renderer, font);
    	draw_text(colorGR, 100, 200, "Name", renderer, font);
    	draw_text(colorGR, 100, 200, "Games", renderer, font);
    	draw_text(colorGR, 100, 200, "Name", renderer, font);
    	draw_text(colorGR, 100, 200, "Wins", renderer, font);
    	while(status) {
    		i = 0;

    		char *name = mx_strnew(100);
    		char *games = mx_strnew(100);
    		char *win = mx_strnew(100);
    		while((status = read(file, &z, 1)) && z != ' ') {
    			name[i] = z;
    			i++;
    		}
    		name[i] = 0;
    			i = 0;
    				while(read(file, &z, 1) && z != ' ') {
    					games[i] = z;
    					i++;
    		}
    		i = 0;
    		while(read(file, &z, 1) && z != '\n') {
    			win[i] = z;
    			i++;
    		}
    		if (((y - 6) >= page * 14) && ((y - 6) < (page + 1) * 14)) {
    			draw_text(colorGR, 100, 50*topage, name, renderer, font);
    			draw_text(colorGR, 100, 50*topage, games, renderer, font);
    			draw_text(colorGR, 100, 50*topage, win, renderer, font);
    			topage++;
    		}
    		while(SDL_PollEvent(&event)) {
            	if (event.type == SDL_KEYUP) {
                	if(event.key.keysym.sym == SDLK_RIGHT) {
                    	page++;
                    	printf("%d",page);
                	}
                	if(event.key.keysym.sym == SDLK_LEFT) {
                    	if (page > 0) page -- ;
                	}
                	if(event.key.keysym.sym == SDLK_ESCAPE) {
                    	return 6;
                	}
             	}
        	}
        usleep(10000);
        SDL_RenderPresent(renderer);
        close(file);
    }
    SDL_DestroyTexture(imageBackground);

    }
    return 1;
}
