#include "Game_Utils.h"
#include "LTexture.h"

//load characters music ...
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, const char* WINDOW_TITLE)
{
    bool success = true;
    // Initialize SDL and SDL_mixer
    if(SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO) < 0)
    {
        cout << "Could not initialize SDL and SDL_mixer! SDL Error: " << SDL_GetError() << endl;
        success = false;
    }
    else
    {
        // Create window
        gWindow = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(gWindow == NULL)
        {
            cout << "Could not create window! SDL Error: " << SDL_GetError() << endl;
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if(gRenderer == NULL)
            {
                cout << "Could not create renderer! SDL Error:" << SDL_GetError() << endl;
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);

                // Initialize SDL_image
                int imgFlags = IMG_INIT_PNG;
                if(!(IMG_Init(imgFlags) && imgFlags))
                {
                    cout << "Could not initialize SDL_image! SDL_image Error: " << IMG_GetError() << endl;
                    success = false;
                }

                //Initialize SDL_mixer
                // Mix_OpenAudio(sound frequency, the sample format, number of hardware channels, size of chunk sound)
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    cout << "SDL_mixer could not initialize! SDL_mixer Error:" << Mix_GetError() << endl;
                    success = false;
                }

                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    cout << "SDL_ttf could not initialize! SDL_ttf Error:" << TTF_GetError() << endl;
                    success = false;
                }

            }
        }
    }
    return success;
}

bool loadMedia(LTexture &gPlayer_jump, LTexture &gPlayer_background, LTexture &gThreat1, LTexture &gThreat2,
               LTexture &gPause, LTexture &gResume, LTexture &gScore, LTexture &game_over,LTexture &play_again,
               LTexture &exit_game, Mix_Music *&gMusic, Mix_Music *&gRun, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont, SDL_Renderer* &gRenderer, LTexture &gPlayer_ground,
               SDL_Rect &player_rect, int &frame_width, LTexture &gHiscore, LTexture &menu, LTexture &intro)
{
    bool success = true;

    // Load character animation
    if(!gPlayer_ground.load_media_from_file("img\\character_animation.png", gRenderer))
    {
        cout << "Could not load character animation" << endl;
        success = false;
    }
    else{
        frame_width = gPlayer_ground.getWidth()/10;
        player_rect.w = frame_width;
        player_rect.h = gPlayer_ground.getHeight();
        player_rect.x = 0;
        player_rect.y = 0;
    }

    // Load character when jump
    if(!gPlayer_jump.load_media_from_file("img\\character.png", gRenderer))
    {
        cout << "Could not load character when jump" << endl;
        success = false;
    }

    // Load background
    if(!gPlayer_background.load_media_from_file("img\\BG.png", gRenderer))
    {
        cout << "Could not load Dino background" << endl;
        success = false;
    }
    if (!intro.load_media_from_file("img\\Introduction.png", gRenderer))
    {
        cout << "Could not load Introduction" << endl;
        success = false;
    }

    // Load threat_1
    if(!gThreat1.load_media_from_file("img\\obstacle_1.png", gRenderer))
    {
        cout << "Could not load Threat 1" << endl;
        success = false;
    }

    // Load threat_2
    if(!gThreat2.load_media_from_file("img\\obstacle_2.png", gRenderer))
    {
        cout << "Could not load Threat 2" << endl;
        success = false;
    }

    // Load how to play png
    if(!menu.load_media_from_file("img\\Menu.png", gRenderer))
    {
        cout << "Could not load How to play png" << endl;
        success = false;
    }

    // Load pause image
    if(!gPause.load_media_from_file("img\\pause.png", gRenderer))
    {
        cout << "Could not load pause img" << endl;
        success = false;
    }

    // Load resume image
    if(!gResume.load_media_from_file("img\\resume.png", gRenderer))
    {
        cout << "Could not load resume img" << endl;
        success = false;
    }

    // Open the font
    gFont = TTF_OpenFont("font.ttf", 30);
    if(gFont == NULL)
    {
        cout << "Failed to load font! SDL_ttf Error: " << TTF_GetError() << endl;
        success = false;
    }
    else
    {
        SDL_Color textColor = {255, 255, 255, 255}; // white
        // Load current score
        if(!gScore.load_from_rendered_text("Score:", textColor, gRenderer, gFont))
        {
            cout << "Unable to render score texture!" << endl;
            success = false;
        }
        // Load high score
        if(!gHiscore.load_from_rendered_text("Hi: ", textColor, gRenderer, gFont))
        {
            cout << "Unable to render hi score texture!" << endl;
            success = false;
        }
        // Load texts on screen
        if(!game_over.load_from_rendered_text("GAME OVER!", textColor, gRenderer, gFont))
        {
            cout << "Unable to render game over texture!" << endl;
            success = false;
        }
        if(!play_again.load_from_rendered_text("Press R to play again", textColor, gRenderer, gFont))
        {
            cout << "Unable to render play again texture!" << endl;
            success = false;
        }
        if(!exit_game.load_from_rendered_text("Press Esc to quit", textColor, gRenderer, gFont))
        {
            cout << "Unable to render exit game texture!" << endl;
            success = false;
        }

    }
    // Load music
    gMusic = Mix_LoadMUS("music\\intro.mp3");
    if(gMusic == NULL)
    {
        cout << "Failed to load background music! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }
    gRun = Mix_LoadMUS("music\\in game.mp3");
    if(gRun == NULL)
    {
        cout << "Failed to load in game music! SDL_mixer Error: " << Mix_GetError() << endl;
    }

    // load sound when jump
    gjump = Mix_LoadWAV("music\\jump.wav");
    if(gjump == NULL)
    {
        cout << "Failed to load jumping sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    // Load sound when die
    gdeath = Mix_LoadWAV("music\\death.wav");
    if(gdeath == NULL)
    {
        cout << "Failed to load death sound effect! SDL_mixer Error: " << Mix_GetError() << endl;
        success = false;
    }

    return success;
}

void close(LTexture &gDino_jump, LTexture &gDino_background, LTexture &gThreat1, LTexture &gThreat2,
           LTexture &gPause, LTexture &gResume, LTexture &gScore, LTexture &game_over, LTexture &play_again,
           LTexture &exit_game, Mix_Music *&gMusic, Mix_Music *&gRun,Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont, LTexture &current_score, SDL_Window *&gWindow,
           SDL_Renderer* &gRenderer, LTexture &gDino_ground, LTexture &gHiscore, LTexture &menu, LTexture &intro)
{
    gDino_jump.free();
    gDino_ground.free();
    gDino_background.free();
    gScore.free();
    gHiscore.free();
    current_score.free();
    gPause.free();
    gResume.free();
    gThreat1.free();
    gThreat2.free();
    game_over.free();
    play_again.free();
    exit_game.free();
    menu.free();
    intro.free();

    TTF_CloseFont(gFont);
    gFont = NULL;
    Mix_FreeMusic(gMusic);
    gMusic = NULL;
    Mix_FreeMusic(gRun);
    gRun = NULL;
    Mix_FreeChunk(gjump);
    gjump = NULL;
    Mix_FreeChunk(gdeath);
    gdeath = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    TTF_Quit();
    SDL_Quit();
    IMG_Quit();
    Mix_Quit();
}
