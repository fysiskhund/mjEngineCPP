#include "../extLibs/util/mjMultiPlatform.h"
#include <SDL2/SDL.h>

#include "../game/gl_code.h"
#include <core/mjVector3.h>

#ifdef OSX
    #include <SDL2_mixer/SDL_mixer.h>
#else
    #include <SDL2/SDL_mixer.h>
#endif
struct SDLStruct {
    SDL_Window* window;
    SDL_GLContext context;
};

float t_elapsed = 0.016f;

int width = 768;
int height = 768;

int xWindow = 0;//3840 - width - 50;
int yWindow = 0;//1080 - width - 20;

mjEngine::mjVector3 lJoystick;
mjEngine::mjVector3 rJoystick;

SDL_Joystick* joystick;

int InitSDL(SDLStruct* sdlData) {
   SDL_Init(SDL_INIT_VIDEO|SDL_INIT_GAMECONTROLLER | SDL_INIT_JOYSTICK|SDL_INIT_AUDIO);
    SDL_JoystickEventState(SDL_ENABLE);
    joystick = SDL_JoystickOpen(0);

    #ifdef USE_GL3
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    #elif USE_GLES2
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    #else
        #error "Either USE_GL3 or USE_GLES2 need to be specified."
    #endif


    #ifdef USE_SDL_AUDIO
    Mix_Init(MIX_INIT_OGG);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 512);
    #endif



    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32 );
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 4);

    sdlData->window = SDL_CreateWindow("mjEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    sdlData->context = SDL_GL_CreateContext(sdlData->window);


    if (!sdlData->context)
    {
    	SDL_GetError();
    }

    #if defined(USE_GL3) && !defined(OSX)
    glewInit();
    #endif

    const unsigned char* versionStr = glGetString(GL_VERSION);

    printf("GL Version: %s\n", versionStr);

    printf("context: %p\n", sdlData->context);


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

            int axis = event.jaxis.axis;
            switch(axis)
            {

                case MJ_LEFT_JOYSTICK_X:
                    lJoystick.x  = axisValue;
                break;
                case MJ_LEFT_JOYSTICK_Y:
                    lJoystick.y = axisValue;
                break;
                case MJ_RIGHT_JOYSTICK_X:
                    rJoystick.x = axisValue;
                break;
                case MJ_RIGHT_JOYSTICK_Y:
                    rJoystick.y = axisValue;
                    break;
                default:
                    //axis = event.jaxis.axis;
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

    #ifndef WIN32
        std::string pathPrefix = "/sdcard/mjEngineCPP";
    #else
        std::string pathPrefix = "C:/mjEngineCPP";
    #endif
    setupGame(width, height, new mjResourceManager(pathPrefix));

    int beforeFrame;
    int exitResult;
    do{

        beforeFrame = SDL_GetTicks();
        exitResult = stepFunc(&data);
        int total = SDL_GetTicks() - beforeFrame;
        if (total < 16) // lock to 60 fps. In case SDL is not following vertical sync
        {
            SDL_Delay(16-total);
        }

    } while(!exitResult);

    QuitSDL(&data);

    return 0;
}
