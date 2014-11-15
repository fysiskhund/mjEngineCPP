#include "../extLibs/util/mjMultiPlatform.h"
#include <SDL2/SDL.h>

#include "../game/gl_code.h"
#include "../core/mjVector3.h"

struct SDLStruct {
    SDL_Window* window;
    SDL_GLContext context;
};

float t_elapsed = 0.016f;

int width = 768;
int height = 768;

int xWindow = 3840 - width - 50;
int yWindow = 1080 - width - 20;

mjEngine::mjVector3 lJoystick;
mjEngine::mjVector3 rJoystick;

SDL_Joystick* joystick;

int InitSDL(SDLStruct* sdlData) {
   SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK);
    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);

    #ifndef USE_GLES
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    #else
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    #endif // NON_GLES_CONTEXT






    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32 );
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 4);

    sdlData->window = SDL_CreateWindow("mjEngine", xWindow, yWindow, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    sdlData->context = SDL_GL_CreateContext(sdlData->window);

    const unsigned char* versionStr = glGetString(GL_VERSION);

    printf("GL Version: %s\n", versionStr);

    printf("context: %p\n", sdlData->context);
    if (!sdlData->context)
    {
    	SDL_GetError();
    }
    #ifndef USE_GLES
    glewInit();
    #endif
    return 0;
}

int InitGL(SDLStruct* sdlData) {


    return 0;
}

int stepFunc(SDLStruct* sdlData) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {

        switch(event.type)
        {

        case SDL_QUIT: {
            return 1;
        }
        break;
        case SDL_JOYAXISMOTION:
        {
            float axisValue = (float) event.jaxis.value / 32767.0;

            switch(event.jaxis.axis)
            {

                case 0: // x
                    lJoystick.x  = axisValue;
                break;
                case 1: // y
                    lJoystick.y = axisValue;
                break;
                case 3:
                    rJoystick.x = axisValue;
                break;
                case 4:
                    rJoystick.y = axisValue;
                default:
                break;
            }
            //printf("Joystick event\n");


        }
        break;
        case SDL_JOYBUTTONDOWN:
        {
            JoystickButtonEvent(0, event.jbutton.button, true);
        }
        break;
        break;
        default:
        /*
        {
           printf("event %d\n", event.type);
        }*/
        break;
        }
    }

    JoystickEvent(0, 0, lJoystick.x, lJoystick.y);
    JoystickEvent(0, 1, rJoystick.x, rJoystick.y);
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

int main(int argc, char* argv[]) {
    SDLStruct data;

    InitSDL(&data);

    InitGL(&data);

    std::string pathPrefix = "/sdcard/mjEngineCPP";
    setupGame(width, height, new mjResourceManager(pathPrefix));

    while (!stepFunc(&data));

    QuitSDL(&data);

    return 0;
}
