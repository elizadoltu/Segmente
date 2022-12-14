#include <iostream>
#include <stdlib.h>
#include <winbgim.h>
#include <graphics.h>
#include <time.h>
#include <cstring>
#include <algorithm>
#include "setUp.h"
#include "menu.h"
using namespace std;

int matriceSegmente[51][51];
char keyPressed;
bool valuePlay, valueRules;
bool gameRunning = true;
int counter = 1;
int dx, dy;

struct Player{

    int winnerRounds;

};

struct DrawPoint{

    int xCoordonate, yCoordonate;
    int pointNumber;
    bool taken;

} point[200];

void playerInput(){



}
char index[201][5]= {{"0"}, {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"},
{"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"},
{"20"}, {"21"}, {"22"}, {"23"}, {"24"}, {"25"}, {"26"}, {"27"}, {"28"}, {"29"},
{"30"}, {"31"}, {"32"}, {"33"}, {"34"}, {"35"}, {"36"}, {"37"}, {"38"}, {"39"},
{"40"}, {"41"}, {"42"}, {"43"}, {"44"}, {"45"}, {"46"}, {"47"}, {"48"}, {"49"},
{"50"}, {"51"}, {"52"}, {"53"}, {"54"}, {"55"}, {"56"}, {"57"}, {"58"}, {"59"},
{"60"}, {"61"}, {"62"}, {"63"}, {"64"}, {"65"}, {"66"}, {"67"}, {"68"}, {"69"},
{"70"}, {"71"}, {"72"}, {"73"}, {"74"}, {"75"}, {"76"}, {"77"}, {"78"}, {"79"},
{"80"}, {"81"}, {"82"}, {"83"}, {"84"}, {"85"}, {"86"}, {"87"}, {"88"}, {"89"},
{"90"}, {"91"}, {"92"}, {"93"}, {"94"}, {"95"}, {"96"}, {"97"}, {"98"}, {"99"},
{"100"}, {"101"}, {"102"}, {"103"}, {"104"}, {"105"}, {"106"}, {"107"}, {"108"}, {"109"},
{"110"}, {"111"}, {"112"}, {"113"}, {"114"}, {"115"}, {"116"}, {"117"}, {"118"}, {"119"},
{"120"}, {"121"}, {"122"}, {"123"}, {"124"}, {"125"}, {"126"}, {"127"}, {"128"}, {"129"},
{"130"}, {"131"}, {"132"}, {"133"}, {"134"}, {"135"}, {"136"}, {"137"}, {"138"}, {"139"},
{"140"}, {"141"}, {"142"}, {"143"}, {"144"}, {"145"}, {"146"}, {"147"}, {"148"}, {"149"},
{"150"}, {"151"}, {"152"}, {"153"}, {"154"}, {"155"}, {"156"}, {"157"}, {"158"}, {"159"},
{"160"}, {"161"}, {"162"}, {"163"}, {"164"}, {"165"}, {"166"}, {"167"}, {"168"}, {"169"},
{"170"}, {"171"}, {"172"}, {"173"}, {"174"}, {"175"}, {"176"}, {"177"}, {"178"}, {"179"},
{"180"}, {"181"}, {"182"}, {"183"}, {"184"}, {"185"}, {"186"}, {"187"}, {"188"}, {"189"},
{"190"}, {"191"}, {"192"}, {"193"}, {"194"}, {"195"}, {"196"}, {"197"}, {"198"}, {"199"}, {"200"}};

bool comp(DrawPoint a, DrawPoint b)
{
	if(a.xCoordonate != b.xCoordonate)
        return a.xCoordonate < b.xCoordonate;
	return a.yCoordonate <= b.yCoordonate;
}

bool CautareBin(int st, int dr, int x, int y)
{
	int m = (st + dr) / 2;
	if(x < point[m].xCoordonate - 10)
        return CautareBin(st, m - 1, x, y);
	else
        if(x > point[m].xCoordonate + 10)
            return CautareBin(m + 1, dr, x , y);
	else {
		if(y < point[m].yCoordonate - 10)
            return CautareBin(st, m - 1, x, y);
		else
            if(y > point[m].yCoordonate + 10)
                return CautareBin(m + 1, dr, x , y);
            else
                return 1;
	}
	return 0;
}

void trageLinia()
{
	POINT cursorPos;
	int x1, x2, y1, y2, verif, ok;
	int nr = 100;
	while(nr){
		cursorPos.x = cursorPos.x - 3;
		cursorPos.y = cursorPos.x - 26;
		if(ismouseclick(WM_LBUTTONDOWN)){
			getmouseclick(WM_LBUTTONDOWN, x1, y1);
			if(CautareBin(1, counter, x1, y1) == 1){
                cout << "da ";
			}
        }
	}
}


void generarePuncte(){

    int puncteGenerate;
    cout << ("Introduce un numar intre 10 si 50:");
    cin >> puncteGenerate;

    while (counter <= puncteGenerate){

        settextstyle(EUROPEAN_FONT, HORIZ_DIR, 1);
        point[counter].pointNumber = counter;
        point[counter].xCoordonate = rand()%800;
        point[counter].yCoordonate = rand()%800;


        if ((point[counter].xCoordonate >= 20 && point[counter].xCoordonate <= 800) &&
            (point[counter].yCoordonate >= 20 && point[counter].yCoordonate <= 800)){
            circle(point[counter].xCoordonate, point[counter].yCoordonate, 4);

            setfillstyle(SOLID_FILL, WHITE);
            floodfill(point[counter].xCoordonate, point[counter].yCoordonate, WHITE);

            outtextxy(point[counter].xCoordonate - 6, point[counter].yCoordonate - 30, index[counter]);
            ++counter;
        }
    }
    sort(point + 1, point + counter, comp);
    trageLinia();
}

int main()
{
    setUpMainWindow();
    showTitle();

    while (gameRunning == true) {

        drawButtons();
        getmouseclick(WM_LBUTTONDOWN, dx, dy);
        if (isPlayClicked(dx, dy) == true){
            cleardevice();
        }
        if (isRulesClicked(dx, dy) == true)
            gameRunning = false;

        keyPressed = (char) getch();

        if ((keyPressed == 'x') || keyPressed == 'X')
            gameRunning = false;

    }
    getch();
    closegraph();
    return 0;
}
