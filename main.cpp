#include <iostream>
#include <stdlib.h>
#include <graphics.h>
#include <time.h>
#include <cstring>
#include <algorithm>
#include <windows.h>
#include <winuser.h>
#define SIZE_WIDTH 800
#define SIZE_HEIGHT 800

using namespace std;

int cnt = 1, n = 0;
bool gameRun = true;
char keyPressed;
int text_x, text_y;
int titleWidth, titleHeight;
int rules_x, rules_y;
int play_x, play_y;
int controls_x, controls_y;
int circle_x, circle_y;
int puncteGenerate;

struct Player{

    int winnerRounds;

};

struct coordonate{

	int a, b, c, d;

}segment[200];

int viz[200];
int blocat[200];

struct DrawPoint{

    int xCoordonate, yCoordonate;
    int pointNumber;
    bool taken;

} point[200];

char index[201][5]= {{"0"}, {"1"}, {"2"}, {"3"}, {"4"}, {"5"}, {"6"}, {"7"}, {"8"}, {"9"}, {"10"}, {"11"}, {"12"}, {"13"}, {"14"}, {"15"},
{"16"}, {"17"}, {"18"}, {"19"}, {"20"}, {"21"}, {"22"}, {"23"}, {"24"}, {"25"}, {"26"}, {"27"}, {"28"}, {"29"}, {"30"}, {"31"}, {"32"},
{"33"}, {"34"}, {"35"}, {"36"}, {"37"}, {"38"}, {"39"}, {"40"}, {"41"}, {"42"}, {"43"}, {"44"}, {"45"}, {"46"}, {"47"}, {"48"}, {"49"},
{"50"}, {"51"}, {"52"}, {"53"}, {"54"}, {"55"}, {"56"}, {"57"}, {"58"}, {"59"}, {"60"}, {"61"}, {"62"}, {"63"}, {"64"}, {"65"}, {"66"},
{"67"}, {"68"}, {"69"}, {"70"}, {"71"}, {"72"}, {"73"}, {"74"}, {"75"}, {"76"}, {"77"}, {"78"}, {"79"}, {"80"}, {"81"}, {"82"}, {"83"},
{"84"}, {"85"}, {"86"}, {"87"}, {"88"}, {"89"}, {"90"}, {"91"}, {"92"}, {"93"}, {"94"}, {"95"}, {"96"}, {"97"}, {"98"}, {"99"}, {"100"},
{"101"}, {"102"}, {"103"}, {"104"}, {"105"}, {"106"}, {"107"}, {"108"}, {"109"}, {"110"}, {"111"}, {"112"}, {"113"}, {"114"}, {"115"},
{"116"}, {"117"}, {"118"}, {"119"}, {"120"}, {"121"}, {"122"}, {"123"}, {"124"}, {"125"}, {"126"}, {"127"}, {"128"}, {"129"}, {"130"},
{"131"}, {"132"}, {"133"}, {"134"}, {"135"}, {"136"}, {"137"}, {"138"}, {"139"}, {"140"}, {"141"}, {"142"}, {"143"}, {"144"}, {"145"},
{"146"}, {"147"}, {"148"}, {"149"}, {"150"}, {"151"}, {"152"}, {"153"}, {"154"}, {"155"}, {"156"}, {"157"}, {"158"}, {"159"}, {"160"},
{"161"}, {"162"}, {"163"}, {"164"}, {"165"}, {"166"}, {"167"}, {"168"}, {"169"}, {"170"}, {"171"}, {"172"}, {"173"}, {"174"}, {"175"},
{"176"}, {"177"}, {"178"}, {"179"}, {"180"}, {"181"}, {"182"}, {"183"}, {"184"}, {"185"}, {"186"}, {"187"}, {"188"}, {"189"}, {"190"},
{"191"}, {"192"}, {"193"}, {"194"}, {"195"}, {"196"}, {"197"}, {"198"}, {"199"}, {"200"}};

bool comp(DrawPoint a, DrawPoint b)
{
	if(a.xCoordonate != b.xCoordonate)
	return a.xCoordonate < b.xCoordonate;
	return a.yCoordonate <= b.yCoordonate;
}

int CautareBin(int x, int y)
{

		int i;
		for(i = 1; i <= cnt; i++)
		{
			if((point[i].xCoordonate >= x - 10 and point[i].xCoordonate <= x + 10) and (point[i].yCoordonate >= y - 10 and point[i].yCoordonate <= y + 10))return i;
		}
		return 0;


}

int sarrus(int p1x, int p1y, int p2x, int p2y, int p3x, int p3y)
{
	return p1x * p2y + p2x * p3y + p1y * p3x - p3x * p2y - p3y * p1x - p1y * p2x;
}

int intersectie(int x, int y, int xs, int ys)
{
	for(int i = 1; i <= n; i++)
	{
		if(sarrus(segment[i].c, segment[i].d, segment[i].a, segment[i].b, x, y) * sarrus(segment[i].c, segment[i].d, segment[i].a, segment[i].b, xs, ys) <= 0 and sarrus(xs, ys, x, y, segment[i].a, segment[i].b) * sarrus(xs, ys, x, y, segment[i].c, segment[i].d) <= 0)return 1;
	}
	return 0;
}

void Cercuri()
{
    for(int i = 1; i <= cnt; i++)
    {
        setfillstyle(SOLID_FILL,RED);
        circle(point[i].xCoordonate, point[i].yCoordonate, 10);
        floodfill(point[i].xCoordonate, point[i].yCoordonate, WHITE);
        settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
        outtextxy(point[i].xCoordonate - 6, point[i].yCoordonate - 30, index[i]);
        delay(100);
    }
}

void GenerareRandom()
{
	while (cnt <= puncteGenerate)
    {
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
		cnt++;
    }
    cnt--;
}

void Randare()
{

    line(0, 30, SIZE_WIDTH, 30);
    line(SIZE_WIDTH - 30, 0, SIZE_WIDTH - 30, SIZE_WIDTH);
    for(int i = 1; i <= cnt; i++)
    {

        setlinestyle(SOLID_LINE, 0, 1);
        setfillstyle(SOLID_FILL,RED);
        circle(point[i].xCoordonate, point[i].yCoordonate, 10);
        floodfill(point[i].xCoordonate, point[i].yCoordonate, WHITE);
        settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
        outtextxy(point[i].xCoordonate - 6, point[i].yCoordonate - 30, index[i]);
        setcolor(WHITE);
        if(viz[i] == 1)
        {
            setlinestyle(SOLID_LINE, 0, 1);
            setcolor(RED);
            circle(point[i].xCoordonate, point[i].yCoordonate, 10);
            setcolor(WHITE);
            setfillstyle(SOLID_FILL,RED);
            circle(point[i].xCoordonate, point[i].yCoordonate, 15);
            floodfill(point[i].xCoordonate + 11, point[i].yCoordonate, WHITE);
            settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
            outtextxy(point[i].xCoordonate - 6, point[i].yCoordonate - 30, index[i]);
            setcolor(WHITE);
        }
    }

    for(int i = 1; i <= n; i++)
    {
        setlinestyle(SOLID_LINE, 0, 3);
        setcolor(GREEN);
        line(segment[i].a, segment[i].b, segment[i].c, segment[i].d);
    }
}

void VerificareNodBlocat()
{

	for(int i = 1; i <= cnt; i++)
	{
		int p = 1;
		if(viz[i] == 0)
		for(int j = 1; j <= cnt; j++)
		if(viz[j] == 0 and i != j)
		{
			p = p * intersectie(point[i].xCoordonate, point[i].yCoordonate, point[j].xCoordonate, point[j].yCoordonate);
		}
		if(p == 1)viz[i] = 1;
	}

}

int trageLinia(bool run)
{
    POINT cursorPos;
    int x1, x2, y1, y2, verif1, verif2, ok;
    int page = 0;
    while(run)
    {
         if (GetAsyncKeyState(VK_HOME)){
            run = false;
            return run;
         }

         if (GetAsyncKeyState(VK_DELETE))
            --n;

        if(ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, x1, y1);
            int c1 = CautareBin(x1, y1);
            if(c1 and viz[c1] == 0)
            {
                verif1 = 0;
                viz[c1] = 1;
                while(verif1 == 0)
                {
                    setactivepage(page);
                    cleardevice();
                    Randare();
                    GetCursorPos(&cursorPos);
                    ScreenToClient(GetForegroundWindow(), &cursorPos);
                    if(ismouseclick(WM_RBUTTONDOWN))
                    {
                    	setcolor(BLACK);
                    	line(point[c1].xCoordonate, point[c1].yCoordonate,cursorPos.x, cursorPos.y);
                    	setlinestyle(SOLID_LINE, 0, 1);
            			setcolor(RED);
            			circle(point[c1].xCoordonate, point[c1].yCoordonate, 10);
           				setcolor(WHITE);
            			setfillstyle(SOLID_FILL,RED);
            			circle(point[c1].xCoordonate, point[c1].yCoordonate, 15);
            			floodfill(point[c1].xCoordonate + 11, point[c1].yCoordonate, WHITE);
            			settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
           				outtextxy(point[c1].xCoordonate - 6, point[c1].yCoordonate - 30, index[c1]);
            			setcolor(WHITE);
                    	viz[c1] = 0;
                    	clearmouseclick(WM_RBUTTONDOWN);
                    	setcolor(WHITE);
                    	verif1 = 1;
					}
                    else if(getpixel(cursorPos.x, cursorPos.y) == 4 and intersectie(point[c1].xCoordonate, point[c1].yCoordonate,cursorPos.x, cursorPos.y) == 1)
                    {
                        setcolor(RED);
                        line(point[c1].xCoordonate, point[c1].yCoordonate, cursorPos.x, cursorPos.y);
                        setcolor(WHITE);
                        clearmouseclick(WM_LBUTTONDBLCLK);
                    }
                    else
                    {
                        setcolor(WHITE);
                        line(point[c1].xCoordonate, point[c1].yCoordonate, cursorPos.x, cursorPos.y);
                        setcolor(WHITE);
                        if(ismouseclick(WM_LBUTTONDBLCLK))
                        {
                            setcolor(BLACK);
                            line(point[c1].xCoordonate, point[c1].yCoordonate, cursorPos.x, cursorPos.y);
                            getmouseclick(WM_LBUTTONDBLCLK, x2, y2);
                            int c2 = CautareBin(x2, y2);
                            if(c2 and viz[c2] == 0)
                            {
                                setlinestyle(SOLID_LINE, 0, 1);
                                setcolor(RED);
                                circle(point[c2].xCoordonate, point[c2].yCoordonate, 10);
                                setcolor(WHITE);
                                setfillstyle(SOLID_FILL,RED);
                                circle(point[c2].xCoordonate, point[c2].yCoordonate, 15);
                                floodfill(point[c2].xCoordonate + 11, point[c2].yCoordonate, WHITE);
                                setlinestyle(SOLID_LINE, 0, 3);
                                setcolor(GREEN);
                                line(point[c1].xCoordonate, point[c1].yCoordonate, point[c2].xCoordonate, point[c2].yCoordonate);
                                verif1 = 1;
                                viz[c2] = 1;
                                segment[++n].a = point[c1].xCoordonate;
                                segment[n].b = point[c1].yCoordonate;
                                segment[n].c = point[c2].xCoordonate;
                                segment[n].d = point[c2].yCoordonate;
                                VerificareNodBlocat();
                                int p = 1;
                                for(int i = 1; i <= cnt; i++)
                                 	p = p * viz[i];
                                if(p == 1 )
                                {
                                	if(n % 2 == 0)
                                	{
                                		setcolor(YELLOW);
                                		settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
            							outtextxy(10, 20, "Player2 castiga!");
            							setcolor(WHITE);
									}
                                	else
                                	{
                                		setcolor(YELLOW);
                                		settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
            							outtextxy(10, 20, "Player1 castiga!");
            							setcolor(WHITE);
									}

								}

                            }
                        }
                    }
                    setvisualpage(page);
                    page++;
                    if(page % 2 == 0)page = 0;
                    delay(2);
                }
                verif1 = 0;
            }
        }
        delay(2);
        if(n * 2 == cnt - 1)
        {
            cout << "END GAME";
            return run;
        }
    }
}

void generarePuncte()
{
    cout << "Introduce un numar intre 10 si 50: ";
    cin >> puncteGenerate;
    srand(time(0));
	GenerareRandom();
    line(0, 30, SIZE_WIDTH, 30);
    line(SIZE_WIDTH - 30, 0, SIZE_WIDTH - 30, SIZE_WIDTH);
    Cercuri();
}

void showTitle(){

    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 6);

    int titleWidth = textwidth("SEGMENTE");
    int titleHeight = textheight("SEGMENTE");

    text_x = SIZE_WIDTH / 2 - titleWidth / 2;
    text_y = SIZE_HEIGHT / 5 - titleHeight / 2;

    outtextxy(text_x, text_y, "SEGMENTE");

}

void showPlay(){

    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);

    int playWidth = textwidth("PLAY");
    int playHeight = textheight("PLAY");

    play_x = SIZE_WIDTH / 2 - playWidth / 2;
    play_y = SIZE_WIDTH / 5 * 2 - playHeight / 2;

    outtextxy(play_x, play_y, "PLAY");

}

void showRules(){

    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);

    int rulesWidth = textwidth("RULES");
    int rulesHeight = textheight("RULES");

    rules_x = SIZE_WIDTH / 2 - rulesWidth / 2;
    rules_y = SIZE_WIDTH / 5 * 3 - rulesHeight / 2;

    outtextxy(rules_x, rules_y, "RULES");

}

void showControls(){

    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);

    int controlsWidth = textwidth("CONTROLS");
    int controlsHeight = textheight("CONTROLS");

    controls_x = SIZE_WIDTH / 2 - controlsWidth / 2;
    controls_y = SIZE_HEIGHT / 5 * 4 - controlsHeight / 2;

    outtextxy(controls_x, controls_y, "CONTROLS");
}

int main()
{
    int mainWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "Segmente");

    showTitle(); showPlay(); showRules(); showControls();
    circle_y = 320; circle_x = play_x - 100;
    circle(circle_x, circle_y, 10);
    setfillstyle(SOLID_FILL, WHITE);
    floodfill(circle_x, circle_y, WHITE);

    int dx, dy;
    bool isClicked = true;
    bool player1 = true, player2 = true;
    int verificareCastigator;

    int rulesWindow, playWindow, controlsWindow;
    setcurrentwindow(mainWindow);

    while(gameRun){

        keyPressed = (char) getch();
        if (keyPressed == 'b' or keyPressed == 'B'){
            closegraph(CURRENT_WINDOW);
            mainWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "Segmente");
            showTitle(); showPlay(); showRules(); showControls();
            circle(circle_x, circle_y, 10);
            setfillstyle(SOLID_FILL, WHITE);
            floodfill(circle_x, circle_y, WHITE);
            setcurrentwindow(mainWindow);
        }
        if ((keyPressed == 'w' or keyPressed == 'W') and circle_y > 320){
            cleardevice();
            showTitle(); showPlay(); showRules(); showControls();
            circle_y -= 160;
            circle(circle_x, circle_y, 10);
            setfillstyle(SOLID_FILL, WHITE);
            floodfill(circle_x, circle_y, WHITE);
        }
        if ((keyPressed == 's' or keyPressed == 'S') and circle_y < 640){
            cleardevice();
            showTitle(); showPlay(); showRules(); showControls();
            circle_y += 160;
            circle(circle_x, circle_y, 10);
            setfillstyle(SOLID_FILL, WHITE);
            floodfill(circle_x, circle_y, WHITE);
        }

        if (GetAsyncKeyState(VK_SPACE)){

            if (circle_y == 320){
                closegraph(CURRENT_WINDOW);
                playWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "PLAY");
                setcurrentwindow(playWindow);
                while (1){
                    generarePuncte();
                    trageLinia(isClicked);
                    if (trageLinia(isClicked) == false){
                        keyPressed = 'b';
                        break;
                    }
                }
            }
            if (circle_y == 480){
                closegraph(CURRENT_WINDOW);
                rulesWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "RULES");
                setcurrentwindow(rulesWindow);
                settextstyle(EUROPEAN_FONT, HORIZ_DIR, 2);
                outtextxy(10, 60,"Pe o foaie de hartie marcati la intamplare cateva zeci de puncte.");
                outtextxy(10, 80,"Fiecare dintre cei doi jucatori are pregatit cate un creion colorat,");
                outtextxy(10, 100, "in cazul acesta, punctele vor aparea pe ecran. Punctele se ");
                outtextxy(10, 120, "unesc, doua cate doua, prin segmente de dreapta, indiferent de");
                outtextxy(10, 140, "marimea si orientarea segmentelor. Acelasi punct nu poate fi ");
                outtextxy(10, 160, "capatul a doua sau mai multe segmente, iar segmentele nu se");
                outtextxy(10, 180, "vor intretaia.");
            }
            if (circle_y == 640){
                closegraph(CURRENT_WINDOW);
                controlsWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "CONTROLS");
                setcurrentwindow(controlsWindow);
                settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
                outtextxy(290, 180, "w, W - up");
                outtextxy(290, 260, "s, S - down");
                outtextxy(290, 340, "SPACE - select");
                outtextxy(290, 420, "b, B - back");
                outtextxy(290, 500, "ESCAPE - close the game");
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE))
            gameRun = false;

    }
    closegraph();
    getch();
	return 0;
}
