#include <GLES2/gl2.h>
#include <SDL2/SDL.h>

#include "../game/gl_code.h"

struct SDLStruct {
    SDL_Window *window;
    SDL_GLContext context;
};

float t_elapsed = 0.016f;

int width = 512;
int height = 512;

int InitSDL(SDLStruct* sdlData) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);


    sdlData->window = SDL_CreateWindow("mjEngine", 0, 0, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    sdlData->context = SDL_GL_CreateContext(sdlData->window);

    printf("context: %p\n", sdlData->context);
    if (!sdlData->context)
    {
    	SDL_GetError();
    }


    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);




    return 0;
}

int InitGL(SDLStruct* sdlData) {


    return 0;
}

int stepFunc(SDLStruct* sdlData) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return 1;
        }
    }

    renderFrame(t_elapsed);

    SDL_GL_SwapWindow(sdlData->window);

    return 0;
}

void QuitSDL(SDLStruct* sdlData) {
    SDL_GL_DeleteContext(sdlData->context);
    SDL_DestroyWindow(sdlData->window);
    SDL_Quit();
    return;
}

int main() {
    SDLStruct data;

    InitSDL(&data);

    InitGL(&data);

    setupGraphics(width, height);

    while (!stepFunc(&data));

    QuitSDL(&data);

    return 0;
}
