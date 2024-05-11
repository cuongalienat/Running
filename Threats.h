#ifndef THREATS_H
#define THREATS_H

#include"BaseFunctions.h"
#include"LTexture.h"

#define THREAT_1_WIDTH 80
#define THREAT_1_HEIGHT 76

#define THREAT_2_WIDTH 72
#define THREAT_2_HEIGHT 76

#define RUN_DISTANCE 3;

class Threat
{
public:
    Threat();

    void render_threat_1(LTexture &gThreat1, SDL_Renderer* &gRenderer);
    void render_threat_2(LTexture &gThreat2, SDL_Renderer* &gRenderer);

    void threat_move();
    void pause(SDL_Event e);

    SDL_Rect get_obstacle_1_dimension(); // Get threat's dimension
    SDL_Rect get_obstacle_2_dimension();

    void reset();
    void gameOver();

private:
    bool is_pause;
    //Threat 1
    int mPosX_1, mPosY_1;
    int mWidth_1, mHeight_1;
    //Threat 2
    int mPosX_2, mPosY_2;
    int mWidth_2, mHeight_2;
};

#endif // THREATS_H
