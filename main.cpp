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
unsigned int puncteGenerate = 0;
int culoareCerc;
int culoareLinie;
int culoareLiniep1;
int culoareLiniep2;


struct coordonate{

	int a, b, c, d;
	int pct1, pct2;

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
    //VERIFICAREA INTERSECTIEI
    //DACA SEGMENTELE SE INTERSECTEAZA ACEASTA FUNCTIE RETURNEAZA 1, ALTFEL 0
	for(int i = 1; i <= n; i++)
	{
		if(sarrus(segment[i].c, segment[i].d, segment[i].a, segment[i].b, x, y) * sarrus(segment[i].c, segment[i].d, segment[i].a, segment[i].b, xs, ys) <= 0 and sarrus(xs, ys, x, y, segment[i].a, segment[i].b) * sarrus(xs, ys, x, y, segment[i].c, segment[i].d) <= 0)return 1;
	}
	return 0;
}

void Cercuri()
{
    //AFISAREA CERCURILOR SI NUMARUL LOR
    for(int i = 1; i <= cnt; i++)
    {
        setfillstyle(SOLID_FILL,culoareCerc);
        circle(point[i].xCoordonate, point[i].yCoordonate, 10);
        floodfill(point[i].xCoordonate, point[i].yCoordonate, WHITE);
        settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
        outtextxy(point[i].xCoordonate - 6, point[i].yCoordonate - 30, index[i]);
        delay(100);
    }
}

void GenerareRandom()
{
    //GENERAREA DE COORDONATE RANDOM
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
                //VERIFICAREA SUPLIMENTARA A COORDONATELOR PENTRU A NU SE GENERA UN PUNCT PREA APROAPE DE ALTUL
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
        setfillstyle(SOLID_FILL,culoareCerc);
        circle(point[i].xCoordonate, point[i].yCoordonate, 10);
        floodfill(point[i].xCoordonate, point[i].yCoordonate, WHITE);
        settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
        outtextxy(point[i].xCoordonate - 6, point[i].yCoordonate - 30, index[i]);

        if(viz[i] == 1)
        {
            setlinestyle(SOLID_LINE, 0, 1);
            setcolor(culoareCerc);
            circle(point[i].xCoordonate, point[i].yCoordonate, 10);
            setcolor(WHITE);
            setfillstyle(SOLID_FILL,culoareCerc);
            circle(point[i].xCoordonate, point[i].yCoordonate, 15);
            floodfill(point[i].xCoordonate + 11, point[i].yCoordonate, WHITE);
            settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
            outtextxy(point[i].xCoordonate - 6, point[i].yCoordonate - 30, index[i]);
        }
    }

    for(int i = 1; i <= n; i++)
    {
        setlinestyle(SOLID_LINE, 0, 3);
        if(i % 2 == 1)setcolor(culoareLiniep1);
        else setcolor(culoareLiniep2);
        line(segment[i].a, segment[i].b, segment[i].c, segment[i].d);
    }
}

void VerificareNodBlocat()
{

    //PARCURGEREA VECTORULUI CU NODURILE FOLOSITE PENTRU A VEDEA DACA MAI SUNT PUNCTE RAMASE LIBERE
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

void reset()
{
	n = 0;
	for(int  i = 1; i <= cnt; i++)
		{
			viz[i] = 0;

		}
	cnt = 0;
}

void generarePuncte();

int trageLinia(bool run)
{
    //FUNCTIA PENTRU A TRAGE O LINIE INTRE DOUA PUNCTE
    POINT cursorPos;
    int x1, x2, y1, y2, verif1, verif2, ok = 0;
    int page = 0;
    int res = 0;
    while(run)
    {
         if (GetAsyncKeyState(VK_HOME) and res == 0){
            //SCOATE PLAYER-UL LA MENIUL PRINCIPAL
            cleardevice();
            run = false;
            res = 1;
            reset();
            return run;

         }

        if (GetAsyncKeyState(VK_F1)and res == 0){
			cleardevice();
            generarePuncte();
            res = 1;
            reset();
            break;
        }

        //VERIFICARE DACA UN PUNCT A FOST SELECTAT CU MOUSE UL
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
                    if(ismouseclick(WM_RBUTTONDOWN) and ok == 0)
                    {
                        setlinestyle(SOLID_LINE, 0, 3);
                    	setcolor(BLACK);
                    	line(point[c1].xCoordonate, point[c1].yCoordonate,cursorPos.x, cursorPos.y);
                    	setlinestyle(SOLID_LINE, 0, 1);
            			circle(point[c1].xCoordonate, point[c1].yCoordonate, 10);
           				setcolor(WHITE);
            			setfillstyle(SOLID_FILL,culoareCerc);
            			circle(point[c1].xCoordonate, point[c1].yCoordonate, 15);
            			floodfill(point[c1].xCoordonate + 11, point[c1].yCoordonate, WHITE);
            			settextstyle(COMPLEX_FONT, HORIZ_DIR, 1);
           				outtextxy(point[c1].xCoordonate - 6, point[c1].yCoordonate - 30, index[c1]);
                    	viz[c1] = 0;
                    	clearmouseclick(WM_RBUTTONDOWN);
                    	setcolor(WHITE);
                    	verif1 = 1;
					}
					//VERIFICARE DACA UN SEGMENT SE INTERSECTEAZA CU ALTUL SAU A FOST SELECTAT UN PUNCT DEJA FOLOSIT
                    if(intersectie(point[c1].xCoordonate, point[c1].yCoordonate,cursorPos.x, cursorPos.y) == 1)
                    {
                        setcolor(RED);
                        line(point[c1].xCoordonate, point[c1].yCoordonate, cursorPos.x, cursorPos.y);
                        setcolor(WHITE);
                        ok = 1;
                        delay(5);
                    }
                    else
                    {
                    	ok = 0;
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
                                circle(point[c2].xCoordonate, point[c2].yCoordonate, 10);
                                setcolor(WHITE);
                                setfillstyle(SOLID_FILL,culoareCerc);
                                circle(point[c2].xCoordonate, point[c2].yCoordonate, 15);
                                floodfill(point[c2].xCoordonate + 11, point[c2].yCoordonate, WHITE);
                                setlinestyle(SOLID_LINE, 0, 3);
                                if(n % 2 == 0)setcolor(culoareLiniep1);
                                else setcolor(culoareLiniep2);
                                line(point[c1].xCoordonate, point[c1].yCoordonate, point[c2].xCoordonate, point[c2].yCoordonate);
                                verif1 = 1;
                                viz[c2] = 1;
                                segment[++n].a = point[c1].xCoordonate;
                                segment[n].b = point[c1].yCoordonate;
                                segment[n].c = point[c2].xCoordonate;
                                segment[n].d = point[c2].yCoordonate;
                                segment[n].pct1 = c1;
                                segment[n].pct2 = c2;
                                //VERIFICARE DACA MAI SUNT PUNCTE LIBERE SAU SUNT TOATE BLOCATE
                                VerificareNodBlocat();
                                int p = 1;
                                for(int i = 1; i <= cnt; i++)
                                 	p = p * viz[i];
                                //STABILIREA PLAYER-ULUI CASTIGATOR
                                if(p == 1 )
                                {
                                	if(n % 2 == 0)
                                	{
                                		setcolor(WHITE);
                                		setlinestyle(SOLID_LINE, 0, 6);
                                		setfillstyle(SOLID_FILL,WHITE);
                                		rectangle(SIZE_WIDTH/3, SIZE_WIDTH/3, SIZE_HEIGHT / 3 * 2, SIZE_HEIGHT / 2);
                                		floodfill(SIZE_WIDTH/3 + 30, SIZE_WIDTH/3 + 30, WHITE);
                                		setfillstyle(SOLID_FILL,WHITE);
                                		rectangle(SIZE_WIDTH/3, SIZE_WIDTH/3, SIZE_HEIGHT / 3 * 2, SIZE_HEIGHT / 2);
            							setcolor(YELLOW);
                                		settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
            							outtextxy(SIZE_WIDTH/3 + 20, SIZE_WIDTH/3 + 50, "Player2 castiga!");
            							setcolor(WHITE);
									}
                                	else
                                	{
                                		setcolor(WHITE);
                                		setlinestyle(SOLID_LINE, 0, 6);
                                		setfillstyle(SOLID_FILL,WHITE);
                                		rectangle(SIZE_WIDTH/3, SIZE_WIDTH/3, SIZE_HEIGHT / 3 * 2, SIZE_HEIGHT / 2);
                                		floodfill(SIZE_WIDTH/3 + 30, SIZE_WIDTH/3 + 30, WHITE);
                                		setfillstyle(SOLID_FILL,WHITE);
                                		rectangle(SIZE_WIDTH/3, SIZE_WIDTH/3, SIZE_HEIGHT / 3 * 2, SIZE_HEIGHT / 2);
            							setcolor(YELLOW);
                                		settextstyle(COMPLEX_FONT, HORIZ_DIR, 3);
            							outtextxy(SIZE_WIDTH/3 + 20, SIZE_WIDTH/3 + 50, "Player1 castiga!");
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
        //UNDO
        if (ismouseclick(WM_MBUTTONDOWN) and n >= 0)
        {
			viz[segment[n].pct1] = 0;
            viz[segment[n].pct2] = 0;
            --n;
            clearmouseclick(WM_MBUTTONDOWN);
		}
        delay(2);


    }
}

void generarePuncte()
{
    cleardevice();

    //AFISAREA OPTIUNILOR DE ALEGERE A CULORII LINIEI
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
    outtextxy(10, 150, "Select colour line 1");
    setfillstyle(SOLID_FILL, MAGENTA);
    rectangle(400, 150, 440, 190);
    floodfill(420, 170, WHITE);

    setfillstyle(SOLID_FILL, RED);
    rectangle(450, 150, 490, 190);
    floodfill(470, 170, WHITE);

    setfillstyle(SOLID_FILL, CYAN);
    rectangle(500, 150, 540, 190);
    floodfill(520, 170, WHITE);

    setfillstyle(SOLID_FILL, GREEN);
    rectangle(550, 150, 590, 190);
    floodfill(560, 170, WHITE);

    setfillstyle(SOLID_FILL, BLUE);
    rectangle(600, 150, 640, 190);
    floodfill(620, 170, WHITE);

    setfillstyle(SOLID_FILL, YELLOW);
    rectangle(650, 150, 690, 190);
    floodfill(660, 170, WHITE);

    //AFISAREA OPTIUNILOR DE ALEGERE A CULORII CERCULUI
    outtextxy(10, 250, "Select colour cicle");

    setfillstyle(SOLID_FILL, MAGENTA);
    rectangle(400, 250, 440, 290);
    floodfill(420, 270, WHITE);

    setfillstyle(SOLID_FILL, RED);
    rectangle(450, 250, 490, 290);
    floodfill(470, 270, WHITE);

    setfillstyle(SOLID_FILL, CYAN);
    rectangle(500, 250, 540, 290);
    floodfill(520, 270, WHITE);

    setfillstyle(SOLID_FILL, GREEN);
    rectangle(550, 250, 590, 290);
    floodfill(560, 270, WHITE);

    setfillstyle(SOLID_FILL, BLUE);
    rectangle(600, 250, 640, 290);
    floodfill(620, 270, WHITE);

    setfillstyle(SOLID_FILL, YELLOW);
    rectangle(650, 250, 690, 290);
    floodfill(660, 270, WHITE);

     outtextxy(10, 350, "Select colour line 2");

    setfillstyle(SOLID_FILL, MAGENTA);
    rectangle(400, 350, 440, 390);
    floodfill(420, 370, WHITE);

    setfillstyle(SOLID_FILL, RED);
    rectangle(450, 350, 490, 390);
    floodfill(470, 370, WHITE);

    setfillstyle(SOLID_FILL, CYAN);
    rectangle(500, 350, 540, 390);
    floodfill(520, 370, WHITE);

    setfillstyle(SOLID_FILL, GREEN);
    rectangle(550, 350, 590, 390);
    floodfill(560, 370, WHITE);

    setfillstyle(SOLID_FILL, BLUE);
    rectangle(600, 350, 640, 390);
    floodfill(620, 370, WHITE);

    setfillstyle(SOLID_FILL, YELLOW);
    rectangle(650, 350, 690, 390);
    floodfill(660, 370, WHITE);

    //AFISAREA DE SELECTARE A PUNCTELOR GENERATE IN JOC
    outtextxy(10, 450, "Press a or d to generate how many points");
    rectangle(250, 550, 290, 590);
    rectangle(350, 550, 390, 590);
    rectangle(450, 550, 490, 590);
    outtextxy(260, 555, "-");
    outtextxy(460, 555, "+");
    outtextxy(160, 650, "Press SPACE to continue");
    bool spacePressed = false;
    char selectKey;

    //CONTROLUL DIN SAGETI SI SELECTAREA PUNCTELOR
    while(1){

        int x_click = 0, y_click = 0;
        int x2_click = 0, y2_click = 0;
        int x1save = 0, y1save = 0;
        int x2save = 0, y2save = 0;
        int choosedColourLine = 0;

        if (ismouseclick(WM_LBUTTONDOWN)){
        	setcolor(BLACK);
        	circle(x1save, 230, 4);
        	setcolor(WHITE);
            getmouseclick(WM_LBUTTONDOWN, x_click, y_click);
            choosedColourLine = getpixel(x_click, y_click);
            if ((x_click >= 400 and x_click <= 440) and (y_click >= 150 and y_click <= 190))
            {
                culoareLiniep1 = 5;
                setlinestyle(SOLID_LINE, 0, 6);
            	circle(420, 170 - 40, 4);
            	x1save = 420;
            }
            else if ((x_click >= 450 and x_click <= 490 and y_click >= 150 and y_click <= 190))
            {
				culoareLiniep1 = 4;
				setlinestyle(SOLID_LINE, 0, 6);
            	circle(470, 170 - 40, 4);
            	x1save = 470;
			}
            else if ((x_click >= 500 and x_click <= 540 and y_click >= 150 and y_click <= 190))
            {
				culoareLiniep1 = 3;
				setlinestyle(SOLID_LINE, 0, 6);
            	circle(520, 170 - 40, 4);
            	x1save = 520;
            }
            else if ((x_click >= 550 and x_click <= 590) and (y_click >= 150 and y_click <= 190))
            {
				culoareLiniep1 = 2;
				setlinestyle(SOLID_LINE, 0, 6);
            	circle(570, 170 - 40, 4);
            	x1save = 570;
            }
            else if ((x_click >= 600 and x_click <= 640) and (y_click >= 150 and y_click <= 190))
            {
				culoareLiniep1 = 1;
				setlinestyle(SOLID_LINE, 0, 6);
            	circle(620, 170 - 40, 4);
            	x1save = 620;
			}
            else if ((x_click >= 650 and x_click <= 690) and (y_click >= 150 and y_click <= 190))
            {
				culoareLiniep1 = 14;
				setlinestyle(SOLID_LINE, 0, 6);
            	circle(670, 170 - 40, 4);
            	x1save = 670;
			}

			if ((x_click >= 400 and x_click <= 440) and (y_click >= 350 and y_click <= 390))
                    {

 					culoareLiniep2 = 5;
					setlinestyle(SOLID_LINE, 0, 6);
            		circle(420, 370 - 40, 4);
            		x1save = 620;
					}
                    if ((x_click >= 450 and x_click <= 490 and y_click >= 350 and y_click <= 390))
                    {
						culoareLiniep2 = 4;
						setlinestyle(SOLID_LINE, 0, 6);
            			circle(470, 370 - 40, 4);
            			x1save = 470;
            		}
                    if ((x_click >= 500 and x_click <= 540 and y_click >= 350 and y_click <= 390))
                    {
						culoareLiniep2 = 3;
						setlinestyle(SOLID_LINE, 0, 6);
            			circle(520, 370 - 40, 4);
            			x2save = 520;
            		}
                    if ((x_click >= 550 and x_click <= 590) and (y_click >= 350 and y_click <= 390))
                    {
                    	culoareLiniep2 = 2;
                    	setlinestyle(SOLID_LINE, 0, 6);
            			circle(570, 370 - 40, 4);
            			x1save = 570;
            		}
                    if ((x_click >= 600 and x_click <= 640) and (y_click >= 350 and y_click <= 390))
                    {
						culoareLiniep2 = 1;
						setlinestyle(SOLID_LINE, 0, 6);
            			circle(620, 370 - 40, 4);
            			x1save = 620;
            		}
                    if ((x_click >= 650 and x_click <= 690) and (y_click >= 350 and y_click <= 390))
                    {
						culoareLiniep2 = 14;
						setlinestyle(SOLID_LINE, 0, 6);
            			circle(670, 370 - 40, 4);
            			x1save = 670;
            		}


        }

    	int choosedColourCircle;
        if (ismouseclick(WM_LBUTTONDBLCLK)){
        	setcolor(BLACK);
        	circle(x2save, 280 , 4);
        	setcolor(WHITE);
            getmouseclick(WM_LBUTTONDBLCLK, x2_click, y2_click);
            choosedColourCircle = getpixel(x2_click, y2_click);
                    if ((x2_click >= 400 and x2_click <= 440) and (y2_click >= 250 and y2_click <= 290))
                    {
						culoareCerc = 5;
						setlinestyle(SOLID_LINE, 0, 6);
            			circle(420, 270 - 40, 4);
            			x2save = 420;
					}
                    if ((x2_click >= 450 and x2_click <= 490 and y2_click >= 250 and y2_click <= 290))
                    {
						culoareCerc = 4;
						setlinestyle(SOLID_LINE, 0, 6);
            			circle(470, 270 - 40, 4);
            			x2save = 470;
            		}
                    if ((x2_click >= 500 and x2_click <= 540 and y2_click >= 250 and y2_click <= 290))
                    {
						culoareCerc = 3;
						setlinestyle(SOLID_LINE, 0, 6);
            			circle(520, 270 - 40, 4);
            			x2save = 520;
            		}
                    if ((x2_click >= 550 and x2_click <= 590) and (y2_click >= 250 and y2_click <= 290))
                    {
                    	culoareCerc = 2;
                    	setlinestyle(SOLID_LINE, 0, 6);
            			circle(570, 270 - 40, 4);
            			x2save = 570;
            		}
                    if ((x2_click >= 600 and x2_click <= 640) and (y2_click >= 250 and y2_click <= 290))
                    {
						culoareCerc = 1;
						setlinestyle(SOLID_LINE, 0, 6);
            			circle(620, 270 - 40, 4);
            			x2save = 620;
            		}
                    if ((x2_click >= 650 and x2_click <= 690) and (y2_click >= 250 and y2_click <= 290))
                    {
						culoareCerc = 14;
						setlinestyle(SOLID_LINE, 0, 6);
            			circle(670, 270 - 40, 4);
            			x2save = 670;
            		}
        }

        outtextxy(360, 555, index[puncteGenerate]);
        selectKey = (char) getch();
        selectKey = tolower(selectKey);

        if (selectKey == 'a')
            --puncteGenerate;

        if (selectKey == 'd')
            ++puncteGenerate;

        if (GetAsyncKeyState(VK_SPACE)){
            cleardevice();
            break;
        }
        delay(2);
    }
	setlinestyle(SOLID_LINE, 0, 1);
    //AFISAREA TABLEI DE JOC
    srand(time(0));
	GenerareRandom();
    line(0, 30, SIZE_WIDTH, 30);
    line(SIZE_WIDTH - 30, 0, SIZE_WIDTH - 30, SIZE_WIDTH);
    Cercuri();
}

void showTitle(){

    //AFISAREA TITLULUI JOCULUI
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 6);

    int titleWidth = textwidth("SEGMENTE");
    int titleHeight = textheight("SEGMENTE");

    text_x = SIZE_WIDTH / 2 - titleWidth / 2;
    text_y = SIZE_HEIGHT / 5 - titleHeight / 2;

    outtextxy(text_x, text_y, "SEGMENTE");

}

void showPlay(){

    //AFISAREA TEXTULUI PLAY
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);

    int playWidth = textwidth("PLAY");
    int playHeight = textheight("PLAY");

    play_x = SIZE_WIDTH / 2 - playWidth / 2;
    play_y = SIZE_WIDTH / 5 * 2 - playHeight / 2;

    outtextxy(play_x, play_y, "PLAY");

}

void showRules(){

    //AFISAREA TEXTULUI RULES
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);

    int rulesWidth = textwidth("RULES");
    int rulesHeight = textheight("RULES");

    rules_x = SIZE_WIDTH / 2 - rulesWidth / 2;
    rules_y = SIZE_WIDTH / 5 * 3 - rulesHeight / 2;

    outtextxy(rules_x, rules_y, "RULES");

}

void showControls(){

    //AFISAREA TEXTULUI CONTROLS
    settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);

    int controlsWidth = textwidth("CONTROLS");
    int controlsHeight = textheight("CONTROLS");

    controls_x = SIZE_WIDTH / 2 - controlsWidth / 2;
    controls_y = SIZE_HEIGHT / 5 * 4 - controlsHeight / 2;

    outtextxy(controls_x, controls_y, "CONTROLS");
}

void ImagineMeniu()
{
    //DESENARE CERCURI IN FEREASTRA MENIULUI PRINCIPAL
    setlinestyle(SOLID_LINE, 0, 1);
    setfillstyle(SOLID_FILL, BLUE);
    circle(171, 722, 23);
    floodfill(171, 722, WHITE);

    setlinestyle(SOLID_LINE, 0, 1);
    setfillstyle(SOLID_FILL,RED);
    circle(702, 256, 12);
    floodfill(702, 256, WHITE);

    setlinestyle(SOLID_LINE, 0, 1);
    setfillstyle(SOLID_FILL,BLACK);
    circle(690, 206, 30);
    floodfill(690, 206, WHITE);

    setlinestyle(SOLID_LINE, 0, 1);
    setfillstyle(SOLID_FILL,RED);
    circle(65, 303, 43);
    floodfill(65, 303, WHITE);

    setlinestyle(SOLID_LINE, 0, 1);
    setfillstyle(SOLID_FILL,CYAN);
    circle(620, 465, 53);
    floodfill(620, 465, WHITE);

    setlinestyle(SOLID_LINE, 0, 1);
    setfillstyle(SOLID_FILL,RED);
    circle(515, 387, 23);
    floodfill(515, 387, WHITE);

    setlinestyle(SOLID_LINE, 0, 1);
    setfillstyle(SOLID_FILL,MAGENTA);
    circle(221, 629, 34);
    floodfill(221, 629, WHITE);

    setlinestyle(SOLID_LINE, 0, 1);
    setfillstyle(SOLID_FILL,RED);
    circle(349, 378, 27);
    floodfill(349, 378, WHITE);

    setlinestyle(SOLID_LINE, 0, 1);
    setfillstyle(SOLID_FILL,WHITE);
    circle(243, 282, 27);
    floodfill(243, 282, WHITE);

    setlinestyle(SOLID_LINE, 0, 1);
    setfillstyle(SOLID_FILL,WHITE);
    circle(100, 50, 37);
    floodfill(100, 50, WHITE);

    setlinestyle(SOLID_LINE, 0, 1);
    setfillstyle(SOLID_FILL,WHITE);
    circle(743, 782, 27);
    floodfill(743, 782, WHITE);

}

int main()
{
    //INITIALIZAREA MENIULUI
    int mainWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "Segmente");
    int page = 0;
    ImagineMeniu();
    showTitle(); showPlay(); showRules(); showControls();
    circle_y = 320; circle_x = play_x - 90;
    circle(circle_x, circle_y, 10);
    setfillstyle(SOLID_FILL, BLACK);
    floodfill(circle_x, circle_y, WHITE);

    setfillstyle(SOLID_FILL, BLACK);
    floodfill(0, 0, WHITE);

    int dx, dy;
    bool isClicked = true;
    bool player1 = true, player2 = true;

    int rulesWindow, playWindow, controlsWindow;
    setcurrentwindow(mainWindow);

    //WHILE-UL PRINCIPAL
    while(gameRun){


        setactivepage(page);
        cleardevice();
        setfillstyle(SOLID_FILL, 0);
        floodfill(0, 0, WHITE);

        ImagineMeniu();
        showTitle(); showPlay(); showRules(); showControls();
        keyPressed = (char) getch();
        //COMENZILE IN FUNCTIE DE INPUTUL UTILIZATORULUI
        if (keyPressed == 'b' or keyPressed == 'B' or GetAsyncKeyState(VK_HOME)){
            //PENTRU A AJUNGE INAPOI LA MENIU
            closegraph(CURRENT_WINDOW);
            mainWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "Segmente");
            ImagineMeniu();
            showTitle(); showPlay(); showRules(); showControls();
            circle(circle_x, circle_y, 10);
            setfillstyle(SOLID_FILL, WHITE);
            floodfill(circle_x, circle_y, BLACK);
            setcurrentwindow(mainWindow);
        }
        if ((keyPressed == 'w' or keyPressed == 'W') and circle_y > 320){
            //PUNCTUL SE MISCA MAI SUS

            showTitle(); showPlay(); showRules(); showControls();
            circle_y -= 160;
            circle(circle_x, circle_y, 10);
            setfillstyle(SOLID_FILL, WHITE);
            floodfill(circle_x, circle_y, BLACK);
        }
        if ((keyPressed == 's' or keyPressed == 'S') and circle_y < 640){
            //PUNCTUL SE MISCA MAI JOS

            showTitle(); showPlay(); showRules(); showControls();
            circle_y += 160;
            circle(circle_x, circle_y, 10);
            setfillstyle(SOLID_FILL, WHITE);
            floodfill(circle_x, circle_y, BLACK);
        }

        if (GetAsyncKeyState(VK_SPACE)){
            //VERIFICARE COORDONATE PUNCT
            if (circle_y == 320){
                //MENIUL GAMEPLAY-ULUI
                closegraph(CURRENT_WINDOW);
                playWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "PLAY");
                setcurrentwindow(playWindow);
                while (1){
                    generarePuncte();
                    trageLinia(isClicked);
                    if (trageLinia(isClicked) == false){
                        keyPressed = 'b';
                        cleardevice();
                        break;
                    }
                }
            }
            if (circle_y == 480){
                //MENIUL CU REGULILE JOCULUI
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
                //MENIUL CU CONTROLUL DIN TASTATURA
                closegraph(CURRENT_WINDOW);
                controlsWindow = initwindow(SIZE_WIDTH, SIZE_HEIGHT, "CONTROLS");
                setcurrentwindow(controlsWindow);
                settextstyle(EUROPEAN_FONT, HORIZ_DIR, 4);
                outtextxy(290, 180, "w, W - up");
                outtextxy(290, 260, "s, S - down");
                outtextxy(290, 340, "SPACE - select");
                outtextxy(290, 420, "b, B - back");
                outtextxy(290, 500, "ESCAPE - close the game");
                outtextxy(290, 580, "HOME - to go back at the menu");
                outtextxy(290, 660, "DELETE - undo");
            }
        }
        if (GetAsyncKeyState(VK_ESCAPE))
            //PENTRU A IESI DIN JOC
            gameRun = false;
            setvisualpage(page);
                    page++;
                    if(page % 2 == 0)page = 0;

    }
    closegraph();
    getch();
	return 0;
}
