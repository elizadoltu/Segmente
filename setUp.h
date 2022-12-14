#include <graphics.h>
#include <stdlib.h>
#include <time.h>
#include <winbgim.h>
#include <iostream>
#define SIZE_WIDTH 1200
#define SIZE_HEIGHT 1000

using namespace std;

void setUpMainWindow(){

    srand(time(0));
    initwindow(SIZE_WIDTH, SIZE_HEIGHT);
    setfillstyle(SOLID_FILL, CYAN);
    floodfill(0, 0, WHITE);
}
