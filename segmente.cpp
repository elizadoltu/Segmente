#include <iostream>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <cstring>
#include <algorithm>
#define SIZE_WIDTH 800
#define SIZE_HEIGHT 800

using namespace std;

int cnt = 1, n = 1;
bool gameRun = true;
char keyPressed;
int text_x, text_y;
int titleWidth, titleHeight;

struct Player{

    int winnerRounds;

};

struct coordonate{
	int a, b, c, d;
}segment[200];

int viz[200];

struct DrawPoint{

    int xCoordonate, yCoordonate;
    int pointNumber;
    bool taken;
} point[200];

	char index[201][5]= {{"0"}, {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"}, {"16"}, {"17"}, {"18"}, {"19"}, {"20"}, {"21"}, {"22"}, {"23"}, {"24"}, {"25"}, {"26"}, {"27"}, {"28"}, {"29"}, {"30"}, {"31"}, {"32"}, {"33"}, {"34"}, {"35"}, {"36"}, {"37"}, {"38"}, {"39"}, {"40"}, {"41"}, {"42"}, {"43"}, {"44"}, {"45"}, {"46"}, {"47"}, {"48"}, {"49"}, {"50"}, {"51"}, {"52"}, {"53"}, {"54"}, {"55"}, {"56"}, {"57"}, {"58"}, {"59"}, {"60"}, {"61"}, {"62"}, {"63"}, {"64"}, {"65"}, {"66"}, {"67"}, {"68"}, {"69"}, {"70"}, {"71"}, {"72"}, {"73"}, {"74"}, {"75"}, {"76"}, {"77"}, {"78"}, {"79"}, {"80"}, {"81"}, {"82"}, {"83"}, {"84"}, {"85"}, {"86"}, {"87"}, {"88"}, {"89"}, {"90"}, {"91"}, {"92"}, {"93"}, {"94"}, {"95"}, {"96"}, {"97"}, {"98"}, {"99"}, {"100"}, {"101"}, {"102"}, {"103"}, {"104"}, {"105"}, {"106"}, {"107"}, {"108"}, {"109"}, {"110"}, {"111"}, {"112"}, {"113"}, {"114"}, {"115"}, {"116"}, {"117"}, {"118"}, {"119"}, {"120"}, {"121"}, {"122"}, {"123"}, {"124"}, {"125"}, {"126"}, {"127"}, {"128"}, {"129"}, {"130"}, {"131"}, {"132"}, {"133"}, {"134"}, {"135"}, {"136"}, {"137"}, {"138"}, {"139"}, {"140"}, {"141"}, {"142"}, {"143"}, {"144"}, {"145"}, {"146"}, {"147"}, {"148"}, {"149"}, {"150"}, {"151"}, {"152"}, {"153"}, {"154"}, {"155"}, {"156"}, {"157"}, {"158"}, {"159"}, {"160"}, {"161"}, {"162"}, {"163"}, {"164"}, {"165"}, {"166"}, {"167"}, {"168"}, {"169"}, {"170"}, {"171"}, {"172"}, {"173"}, {"174"}, {"175"}, {"176"}, {"177"}, {"178"}, {"179"}, {"180"}, {"181"}, {"182"}, {"183"}, {"184"}, {"185"}, {"186"}, {"187"}, {"188"}, {"189"}, {"190"}, {"191"}, {"192"}, {"193"}, {"194"}, {"195"}, {"196"}, {"197"}, {"198"}, {"199"}, {"200"}};
bool comp(DrawPoint a, DrawPoint b)
{
	if(a.xCoordonate != b.xCoordonate)
	return a.xCoordonate < b.xCoordonate;
	return a.yCoordonate <= b.yCoordonate;
}


int CautareBin(int st, int dr, int x, int y)
{
	int m = (st + dr) / 2;
	if(st > dr)
        return 0;
	else
	{
		if(x < point[m].xCoordonate - 10)
		return CautareBin(st, m - 1, x, y);
		else if(x > point[m].xCoordonate + 10)
		return CautareBin(m + 1, dr, x , y);
		else
		{
			if(y < point[m].yCoordonate - 10)
			return CautareBin(st, m - 1, x, y);
			else if(y > point[m].yCoordonate + 10)
			return CautareBin(m + 1, dr, x , y);
	    	else if(y >= point[m].yCoordonate - 10 or y <= point[m].yCoordonate + 10)return m;
		}
	}

}


void trageLinia()
{
	POINT cursorPos;
	int x1, x2, y1, y2, verif1, verif2, ok;
	int nr = 100;
	while(1)
	{
 		//verific daca click stanga e apsat si unde a fost apasat
		if(ismouseclick(WM_LBUTTONDOWN))
		{
			getmouseclick(WM_LBUTTONDOWN, x1, y1);
			//caut cercul pentru a trage linia din mijlocul cercului
			int c1 = CautareBin(0, cnt + 1, x1, y1);
			if(c1)
			{
				//maresc cercul apasat
				setlinestyle(SOLID_LINE, 0, 1);
				setcolor(RED);
        		circle(point[c1].xCoordonate, point[c1].yCoordonate, 10);
        		setcolor(WHITE);
				setfillstyle(SOLID_FILL,RED);
        		circle(point[c1].xCoordonate, point[c1].yCoordonate, 15);
        		floodfill(point[c1].xCoordonate + 11, point[c1].yCoordonate, WHITE);
				verif1 = 0;
				//caut urmatorul cerc pentru a face un segment si repet aceasi pasi ca mai inainte
				while(verif1 == 0)
				{
					setlinestyle(SOLID_LINE, 0, 3);
					setcolor(BLACK);
					line(point[c1].xCoordonate, point[c1].yCoordonate, cursorPos.x - 3, cursorPos.y - 26);
					setcolor(WHITE);
					GetCursorPos(&cursorPos);
					line(point[c1].xCoordonate, point[c1].yCoordonate, cursorPos.x - 3, cursorPos.y - 26);
					if(ismouseclick(WM_LBUTTONDOWN))
					{
						getmouseclick(WM_LBUTTONDOWN, x2, y2);
						int c2 = CautareBin(0, cnt + 1, x2, y2);

						if(c2)
						{
							setlinestyle(SOLID_LINE, 0, 1);
							setcolor(RED);
        					circle(point[c2].xCoordonate, point[c2].yCoordonate, 10);
        					setcolor(WHITE);
							setfillstyle(SOLID_FILL,RED);
        					circle(point[c2].xCoordonate, point[c2].yCoordonate, 15);
        					floodfill(point[c2].xCoordonate + 11, point[c2].yCoordonate, WHITE);
        					setlinestyle(SOLID_LINE, 0, 3);
							setcolor(BLACK);
							line(point[c1].xCoordonate, point[c1].yCoordonate, cursorPos.x - 3, cursorPos.y - 26);
							setcolor(GREEN);
						 	line(point[c1].xCoordonate, point[c1].yCoordonate, point[c2].xCoordonate, point[c2].yCoordonate);
						 	verif1 = 1;
						 	segment[n].a = point[c1].xCoordonate;
						 	segment[n].b = point[c1].yCoordonate;
						 	segment[n].c = point[c2].xCoordonate;
						 	segment[n].d = point[c2].yCoordonate;
						 	n++;
						}
					}
				}
			}
		}
		delay(5);
	}
}
//redesenz totul
void generarePuncte()
{
    int puncteGenerate;
    cout << "Introduce un numar intre 10 si 50: ";
    cin >> puncteGenerate;

    srand(time(0));


    while (cnt <= puncteGenerate){
    	while(1)
    	{
        	point[cnt].pointNumber = cnt;
        	point[cnt].xCoordonate = (rand() % (SIZE_WIDTH - 100) + 50);
        	point[cnt].yCoordonate = (rand() % (SIZE_HEIGHT - 100) + 50);
        	int i = 1, ok = 1;
        	for(i = 1; i < cnt; i++)
        	{
        		if((point[i].xCoordonate >= point[cnt].xCoordonate - 40 and point[i].xCoordonate <= point[cnt].xCoordonate + 40) and (point[i].yCoordonate >= point[cnt].yCoordonate - 40 and point[i].yCoordonate <= point[cnt].yCoordonate + 40))
				ok = 0;
			}
 			if(ok == 1)break;
		}
		sort(point + 1, point + cnt, comp);
		setfillstyle(SOLID_FILL,RED);
        circle(point[cnt].xCoordonate, point[cnt].yCoordonate, 10);
        floodfill(point[cnt].xCoordonate, point[cnt].yCoordonate, WHITE);
        settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
        outtextxy(point[cnt].xCoordonate - 6, point[cnt].yCoordonate - 30, index[cnt]);
        cnt++;
    }
    cnt--;
    trageLinia();
}

void showTitle(){

    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 6);

    int titleWidth = textwidth("SEGMENTE");
    int titleHeight = textheight("SEGMENTE");

    text_x = SIZE_WIDTH / 2 - titleWidth / 2;
    text_y = SIZE_HEIGHT / 4 - titleHeight / 2;

    outtextxy(text_x, text_y, "SEGMENTE");

}

void showPlay(){

    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);

    int playWidth = textwidth("PLAY");
    int playHeight = textheight("PLAY");

    int play_x = SIZE_WIDTH / 2 - playWidth / 2;
    int play_y = SIZE_WIDTH / 4 * 2 - playHeight / 2;

    outtextxy(play_x, play_y, "PLAY");

}

void showRules(){

    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);

    int rulesWidth = textwidth("RULES");
    int rulesHeight = textheight("RULES");

    int rules_x = SIZE_WIDTH / 2 - rulesWidth / 2;
    int rules_y = SIZE_WIDTH / 4 * 3 - rulesHeight / 2;

    outtextxy(rules_x, rules_y, "RULES");

}

bool verifyText(int x, int y){

    if ((x >= text_x - titleWidth / 2 - 50 and y >= text_y - titleHeight / 2 - 50) and (x <= text_x + titleWidth / 2 + 50 and y <= text_y + titleHeight / 2 + 50))
        return true;
    else return false;
}

int main()
{
    int mainWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "Segmente");

    showTitle(); showPlay(); showRules();
    int dx, dy;
    bool isClicked = false;
    int rulesWindow, playWindow;

    setcurrentwindow(mainWindow);

    while(1){


        keyPressed = (char) getch();
        if (keyPressed == 'p' or keyPressed == 'P'){
            closegraph(CURRENT_WINDOW);
            playWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "PLAY");
            setcurrentwindow(playWindow);
            generarePuncte();
        }
        if (keyPressed == 'r' or keyPressed == 'R'){
            closegraph(CURRENT_WINDOW);
            rulesWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "RULES");
            setcurrentwindow(rulesWindow);
            isClicked = true;
        }
        if (keyPressed == 'b' or keyPressed == 'B'){
            closegraph(CURRENT_WINDOW);
            mainWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "Segmente");
            showTitle(); showPlay(); showRules();
            setcurrentwindow(mainWindow);
        }
        if (keyPressed == 'x' or keyPressed == 'X')
            closegraph(ALL_WINDOWS);

    }
    if (isClicked)
        outtext("Your 'flag' boolean needs to be checked as the condition for both while loops, not just the first one.");

    getch();
    closegraph();
	return 0;
}
