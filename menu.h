#include <iostream>
#include <graphics.h>
#include <stdlib.h>
#include <winbgim.h>
using namespace std;

int playWidth, playHeight;
int rulesWidth, rulesHeight;
int segmenteWidth, segmenteHeight;

void showText(){

    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 6);

    playWidth = textwidth("Play"), playHeight = textheight("Play");
    rulesWidth = textwidth("Rules"), rulesHeight = textheight("Rules");
    outtextxy(SIZE_WIDTH / 2 - playWidth / 2, SIZE_HEIGHT / 4 * 2 - playHeight / 2, "Play");
    outtextxy(SIZE_WIDTH / 2 - rulesWidth  / 2, SIZE_HEIGHT / 4 * 3 - rulesHeight / 2, "Rules");
}

void showTitle(){

    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 8);
    segmenteWidth = textwidth("Segmente"), segmenteHeight = textheight("Segmente");
    outtextxy(SIZE_WIDTH / 2 - segmenteWidth / 2, SIZE_HEIGHT / 4 - segmenteHeight / 2 - 50, "Segmente");
}

bool isPlayClicked(int x, int y){

    if((x >= 400 && x <= 800) &&
        (y >= 400 && y <= 500)){
            return true;
    }
    return false;
}

bool isRulesClicked(int x, int y){

    if((x >= 400 && x <= 800) &&
        (y >= 700 && y <= 800)){
            return true;
    }
    return false;
}

void drawButtons(){

    readimagefile("CGB03-green_L_btn.JPG", 400, 400, 800, 500);
    readimagefile("CGB03-green_L_btn.JPG", 400, 700, 800, 800);
}
