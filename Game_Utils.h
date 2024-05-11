#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include"LTexture.h"
#include"BaseFunctions.h"

// Initialize SDL_Window, SDL_Renderer
bool init(SDL_Window* &gWindow, SDL_Renderer* &gRenderer, const char* WINDOW_TITLE);

// Load images, texts, music, sounds
bool loadMedia(LTexture &gPlayer_jump, LTexture &gPlayer_background, LTexture &gThreat1, LTexture &gThreat2, LTexture &gPause,
               LTexture &gResume, LTexture &gScore, LTexture &game_over,LTexture &play_again, LTexture &exit_game,
               Mix_Music *&gMusic, Mix_Music *&gRun, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont, SDL_Renderer* &gRenderer, LTexture &gPlayer_ground, SDL_Rect &player_rect,
               int &frame_width, LTexture &gHiscore, LTexture &how_to_play, LTexture &intro);

// Free all iamges, texts, music, sounds and SDL libraries
void close(LTexture &gPlayer_jump, LTexture &gPlayer_background, LTexture &gThreat1, LTexture &gThreat2,
           LTexture &gPause, LTexture &gResume, LTexture &gScore, LTexture &game_over, LTexture &play_again,
           LTexture &exit_game, Mix_Music *&gMusic, Mix_Music *&gRun, Mix_Chunk *&gjump, Mix_Chunk *&gdeath, TTF_Font *&gFont, LTexture &current_score, SDL_Window *&gWindow, SDL_Renderer* &gRenderer,
           LTexture &gPlayer_ground, LTexture &gHiscore, LTexture &how_to_play, LTexture &intro);

#endif // GAME_UTILS_H
