#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

#define MATRIX_WIDTH 10
#define MATRIX_HEIGHT 20
#define HALF_WIDTH 15
#define HALF_HEIGHT 10
#define EXIT 100

#define WALL 5
#define EMPTY_SLOT 0
#define FULL_SLOT 1

#define UP_DIRECTION 72
#define LEFT_DIRECTION 75
#define RIGHT_DIRECTION 77
#define SPACE 32
#define ESC 27
#define DOWN 80

typedef char playing_field ;

typedef struct _currentlocation{
    int X;
    int Y;
} position;

void cursor_not_shown();
void gotoxy(int x, int y);
int getKey();
void drawborder(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH]);
int before_starting_game();
void drawMatrix(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH]);
void drawSmallMap(int best, int score);
void drawSmallShape(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int shape[4][4]);
void createShape(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int shape[4][4], position curLoc);
void startTime();
void emptymatrix(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH]);
void copyshape(int blockShape[4][4], int copy[4][4]);
void setshape(int blockShape[4][4]);
void deleteShape(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH], int blockShape[4][4], position * curLoc);
int getShapeLeftLoc(int blockShape[4][4]);
int getShapeRightLoc(int blockShape[4][4]);
int getShapeBottomLoc(int blockShape[4][4]);
int getEachBottomLoc(int blockShape[4][4], int w);
int getEachLeftLoc(int blockShape[4][4], int h);
int getEachRightLoc(int blockShape[4][4], int h);
void goLeft(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int blockShape[4][4], position *curLoc);
void goRight(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int blockShape[4][4], position *curLoc);
int fixShape(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH], int blockShape[4][4], position *curLoc);
int goDown(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH], int blockShape[4][4], position *curLoc);
void rotate(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int blockShape[4][4], position * curLoc);
int goSpace(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int blockShape[4][4],position * curLoc);
void deletecompleteLine(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH], int h);
void organizeLine(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH], int h);
void checkifLineiscomplete(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH], position curLoc, int * score);
int endgame(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int score, int bestScore);
int startinggame(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH]);



int main() {
    char password1[10],password2[10];
    strcpy(password1,"ad123");
    do{
    printf("Enter Password: ");
    scanf("%s",password2);
    if(strcmp(password2,password1)==0)
    printf("Password is Valid\n");
    else 
    printf("Incorrect Password\n");
    	}while(strcmp(password2,password1)!=0);
    char map[MATRIX_HEIGHT][MATRIX_WIDTH] ={0};   //map
    int keyinput;
    cursor_not_shown();

    system("color 7");                      //console color
    system("mode con: cols=57 lines=25");   //console size

    while(1){
        keyinput = before_starting_game();
        if(keyinput == 't' || keyinput == 'T') break;
        system("cls");
        startinggame(map);
        Sleep(1000/3);
        system("cls");
    }
    return 0;
}

//hide cursor
void cursor_not_shown() {
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}


//move cursor.
void gotoxy(int x, int y){
    COORD Pos;
    Pos.X = 2*x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

//get keyboard input.
int getKey(){
    if(kbhit()) return getch();
    else return -1;
}

//DRAW
void drawborder(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH]){//border
    int i, j;
    HANDLE control = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(control, 13);

    for(i=0; i<=MATRIX_HEIGHT +1; i++){
        for(j=0; j<=MATRIX_WIDTH +1; j++){
            gotoxy(j+1,i+1);
            if(i==0 || j==0 || i==MATRIX_HEIGHT+1 || j==MATRIX_WIDTH+1)
                printf("¦");
        }
        printf("\n");
    }
    gotoxy(HALF_WIDTH, 1);
    SetConsoleTextAttribute(control, 14);
    printf("<Next>");
    //for creating scorebox
    SetConsoleTextAttribute(control, 11);

    for(i=2; i<=7 ;i++){
        for(j=HALF_WIDTH ; j<=HALF_WIDTH+5; j++){
            if(j==HALF_WIDTH || j==HALF_WIDTH+5 || i==2 || i==7){
                gotoxy(j, i);
                printf("¦");
            }
        }
    }
   gotoxy(HALF_WIDTH, HALF_HEIGHT+1);
    printf("Best  : ");
    gotoxy(HALF_WIDTH, HALF_HEIGHT+2);
    printf("Score : ");
    gotoxy(HALF_WIDTH, HALF_HEIGHT+12);
    printf("<Exit : 't' / Pause : 'p'>");
    SetConsoleTextAttribute(control, 7);
}

int before_starting_game()//before starting game page/;
{
    HANDLE control = GetStdHandle(STD_OUTPUT_HANDLE);
    int keyentered;
    gotoxy(1,2);
    SetConsoleTextAttribute(control, 4);
    printf("-----------------------------------\n");
    gotoxy(1,3);
    SetConsoleTextAttribute(control, 14);
    printf("-------------T E T R I S -----------\n");
    SetConsoleTextAttribute(control, 4);
    gotoxy(1,4);
    printf("------------------------------------\n");

    SetConsoleTextAttribute(control, 14);
    gotoxy(2,6);
    printf("Left : > \n");
    gotoxy(2,7);
    printf("Right : < \n");
   // gotoxy(2,8);
   /* printf("Rotation : ? \n");*/
    gotoxy(2,8);
    printf("Down: space \n");
    gotoxy(2,10);
    printf("Exit: 't' \n");

     //for starting game;
    while(1){
        keyentered = getKey();
        if(keyentered == 's' || keyentered == 'S') break;
        if(keyentered == 't' || keyentered == 'T') break;

        gotoxy(7, 15);
        SetConsoleTextAttribute(control, 11);
        printf(" === press 's' to start ===");
        SetConsoleTextAttribute(control, 7);
        Sleep(1000/2);
        gotoxy(7, 15);
        printf("                            ");
        Sleep(1000/2);
    }

    return keyentered;
}

void drawMatrix(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH]){
    int i, j;
    HANDLE control = GetStdHandle(STD_OUTPUT_HANDLE);

    for(i=0; i<MATRIX_HEIGHT; i++){
        for(j=0; j<MATRIX_WIDTH; j++){
            gotoxy(j+2,i+2);
            if(map[i][j] == EMPTY_SLOT){
                printf("·+");
            }else if(map[i][j] == FULL_SLOT){
                SetConsoleTextAttribute(control, 6);
                printf("¦");
                SetConsoleTextAttribute(control, 7);
            }
        }
        printf("\n");
    }

}

void drawSmallMap(int best, int score){
    HANDLE control = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(control, 14);
    gotoxy(HALF_WIDTH + 4, HALF_HEIGHT+1);
    printf("%4d", best);
    gotoxy(HALF_WIDTH + 4, HALF_HEIGHT+2);
    printf("%4d", score);
    SetConsoleTextAttribute(control, 7);
}

void drawSmallShape(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int shape[4][4]){
    int i, j;
    HANDLE control = GetStdHandle(STD_OUTPUT_HANDLE);

    for(i=3; i<=6 ;i++){
        for(j=HALF_WIDTH+1 ; j<=HALF_WIDTH+4; j++){
                gotoxy(j, i);
                printf(" ");

        }
    }
    for(i=3; i<=6 ;i++){
        for(j=HALF_WIDTH+1 ; j<=HALF_WIDTH+4; j++){
            if(shape[i-3][j - HALF_WIDTH-1] == FULL_SLOT){
                gotoxy(j, i);
                SetConsoleTextAttribute(control, 14);
                printf("¦");
                SetConsoleTextAttribute(control, 7);

            }
        }
    }
}

void createShape(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int shape[4][4], position curLoc){
    int i, j;

    for(i=0; i<4;i++){
        for(j=0; j<4;j++){
            if(shape[i][j] ==FULL_SLOT){
                map[curLoc.Y+ i][curLoc.X +j]=FULL_SLOT;
               \
            }
        }
    }

}


void startTime(){
    int i;
    HANDLE control = GetStdHandle(STD_OUTPUT_HANDLE);

    for(i=0 ;i<3;i++){
        gotoxy(2,0);
        SetConsoleTextAttribute(control, 14);
        printf("Start : %d sec", 3-i);
        SetConsoleTextAttribute(control, 7);
        Sleep(1000);
    }
    gotoxy(2,0);
     printf("                       ");
}
void emptymatrix(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH]){
    int i, j=0;
    for(i=0;i<MATRIX_HEIGHT;i++){
        for(j=0; j<MATRIX_WIDTH; j++){
            map[i][j] = EMPTY_SLOT;
        }
    }
}
void locationInmatrix(position * curLoc){
    curLoc->X =3;
    curLoc->Y =0;
}
void copyshape(int blockShape[4][4], int copy[4][4]){
    int i, j;
    for(i=0;i<4;i++){
        for(j=0; j<4;j++){
            blockShape[i][j] = copy[i][j];
        }
    }
}
void setshape(int blockShape[4][4]){

    int shape[7][4][4] = {
            {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},
            {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
            {{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}},
            {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
            {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
            {{0,0,0,0},{0,1,0,0},{0,1,1,1},{0,0,0,0}},
            {{0,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,0,0}}
    };
    srand((unsigned int)(time(NULL)));

    switch(rand()%7) {
        case 0:
            copyshape(blockShape, shape[0]);
            break;
        case 1:
            copyshape(blockShape, shape[1]);
            break;
        case 2:
            copyshape(blockShape, shape[2]);
            break;
        case 3:
            copyshape(blockShape, shape[3]);
            break;
        case 4:
            copyshape(blockShape, shape[4]);
            break;
        case 5:
            copyshape(blockShape, shape[5]);
            break;
        case 6:
            copyshape(blockShape, shape[6]);
            break;
        default :
            break;
    }
}


void deleteShape(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH], int blockShape[4][4], position * curLoc){
    int i, j;
    for(i=0; i<4;i++){
        for(j=0; j<4;j++){
            if(blockShape[i][j] == FULL_SLOT)
                map[curLoc->Y + i][curLoc->X + j]=EMPTY_SLOT;
        }
    }
}

int getShapeLeftLoc(int blockShape[4][4]){
    int i, j, leftW=4;
    for(j=0; j<4;j++){
        for(i=0; i<4;i++){
            if(blockShape[i][j] == FULL_SLOT){
                if(leftW > j)
                    leftW = j;
            }
        }
    }
    return leftW;
}
int getShapeRightLoc(int blockShape[4][4]){
    int i, j, rightW=0;
    for(j=3; j>=0;j--){
        for(i=3; i>=0;i--){
            if(blockShape[i][j] == FULL_SLOT){
                if(rightW < j)
                    rightW = j;
            }
        }
    }
    return rightW+1;
}
int getShapeBottomLoc(int blockShape[4][4]){
    int i, j, bottomH=0;
    for(j=3; j>=0;j--){
        for(i=3; i>=0;i--){
            if(blockShape[i][j] == FULL_SLOT){
                if(bottomH < i)
                    bottomH =i;
            }
        }
    }
    return bottomH+1;
}
int getEachBottomLoc(int blockShape[4][4], int w){
    int h, bottomH=-1;
    for(h=3; h>=0;h--){
        if(blockShape[h][w] == FULL_SLOT){
            if(bottomH < h)
                bottomH =h;
        }
    }
    return bottomH;
}
int getEachLeftLoc(int blockShape[4][4], int h){
    int w, leftW= 5;
    for(w=0; w<4;w++){
        if(blockShape[h][w] == FULL_SLOT){
            if(leftW > w)
                leftW = w;
        }
    }
    return leftW;
}
int getEachRightLoc(int blockShape[4][4], int h){
    int w, rightW= -1;
    for(w=0; w<4;w++){
        if(blockShape[h][w] == FULL_SLOT){
            if(rightW < w)
                rightW = w;
        }
    }
    return rightW;
}
void goLeft(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int blockShape[4][4], position *curLoc){
    int leftW = getShapeLeftLoc(blockShape);
    int boundaryArr[4] ={0};
    int i;
    for(i=0; i<4;i++){
        boundaryArr[i] = getEachLeftLoc(blockShape, i);

    }
    if((curLoc->X) + leftW > 0){
        if(!((boundaryArr[0] != 5 && map[curLoc->Y][curLoc->X + boundaryArr[0] -1] != EMPTY_SLOT)
           ||(boundaryArr[1] != 5 && map[curLoc->Y +1][curLoc->X + boundaryArr[1] -1] != EMPTY_SLOT)
          ||(boundaryArr[2] != 5 && map[curLoc->Y +2][curLoc->X + boundaryArr[2] -1] != EMPTY_SLOT)
           ||(boundaryArr[3] != 5 && map[curLoc->Y +3][curLoc->X + boundaryArr[3] -1] != EMPTY_SLOT))){

            deleteShape(map, blockShape,curLoc);
            (curLoc->X)--;
        }
    }
}
void goRight(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int blockShape[4][4], position *curLoc){
    int rightW = getShapeRightLoc(blockShape);
    int boundaryArr[4] ={0};
    int i;
    for(i=0; i<4;i++){
        boundaryArr[i] = getEachLeftLoc(blockShape, i);

    }

    if((curLoc->X) + rightW < MATRIX_WIDTH){
        if(!((boundaryArr[0] != 5 && map[curLoc->Y][curLoc->X + boundaryArr[0] +1] != EMPTY_SLOT)
             ||(boundaryArr[1] != 5 && map[curLoc->Y +1][curLoc->X + boundaryArr[1] +1] != EMPTY_SLOT)
             ||(boundaryArr[2] != 5 && map[curLoc->Y +2][curLoc->X + boundaryArr[2] +1] != EMPTY_SLOT)
             ||(boundaryArr[3] != 5 && map[curLoc->Y +3][curLoc->X + boundaryArr[3] +1] != EMPTY_SLOT))){

            deleteShape(map, blockShape,curLoc);
            (curLoc->X)++;
        }

    }
}

int fixShape(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH], int blockShape[4][4], position *curLoc){
    int i, j;
    for(i=0; i<4; i++){
        for(j=0; j<4 ; j++){
            if(blockShape[j][i] ==1){
                map[curLoc->Y+ j][curLoc->X +i]=FULL_SLOT;
            }
        }
    }
}

int goDown(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH], int blockShape[4][4], position *curLoc){
    int bottomH = getShapeBottomLoc(blockShape);
    int bottomArr[4] = {0};
    int i;
    for(i=0; i<4; i++){
        bottomArr[i] = getEachBottomLoc(blockShape, i);
    }
    if(curLoc->Y + bottomH  == MATRIX_HEIGHT
       ||(bottomArr[1] != -1 && map[curLoc->Y + bottomArr[1] +1][curLoc->X + 1] != EMPTY_SLOT)
       ||(bottomArr[0] != -1 && map[curLoc->Y + bottomArr[0] +1][curLoc->X + 0] != EMPTY_SLOT)
       ||(bottomArr[3] != -1 && map[curLoc->Y + bottomArr[3] +1][curLoc->X + 3] != EMPTY_SLOT)
       ||(bottomArr[2] != -1 && map[curLoc->Y + bottomArr[2] +1][curLoc->X + 2] != EMPTY_SLOT)
       ){

        fixShape(map, blockShape, curLoc);

        Sleep(1000/8);
        return TRUE;
    }


    if(curLoc->Y + bottomH < MATRIX_HEIGHT){
        deleteShape(map, blockShape, curLoc);
        Sleep(1000/8);
        (curLoc->Y)++;
    }
    return FALSE;
}

void rotate(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int blockShape[4][4], position * curLoc){
    int i, j;
    int tmp[4][4];
    int leftW, rightW, bottomH;

    for(i=0; i<4;i++){
        for(j=0; j<4;j++){
            if(blockShape[i][j] == FULL_SLOT){
                tmp[j][3-i] = blockShape[i][j];
                blockShape[i][j] = EMPTY_SLOT;
            }

        }
    }

    for(i=0; i<4;i++){
        for(j=0; j<4;j++){
            if(tmp[i][j] == 1){
                blockShape[i][j] = FULL_SLOT;
            }

        }
    }


    leftW= getShapeLeftLoc(blockShape);
    if(curLoc->X + leftW <0){
        goRight(map, blockShape, curLoc);
        if(leftW == 0) goRight(map, blockShape, curLoc); 
    }

    rightW = getShapeRightLoc(blockShape);
    if(curLoc->X + rightW >MATRIX_WIDTH){
        goLeft(map, blockShape, curLoc);
        if(rightW == 4)goLeft(map, blockShape, curLoc); 
    }


    bottomH = getShapeBottomLoc(blockShape);
    if(curLoc->Y + bottomH > MATRIX_HEIGHT){
        deleteShape(map, blockShape, curLoc);
        (curLoc->Y)--;
        if(bottomH ==4) (curLoc->Y)--; 
    }
}

int goSpace(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int blockShape[4][4],position * curLoc){
    int bottomH = getShapeBottomLoc(blockShape);
    int bottomArr[4] = {0};
    int i;
    for(i=0; i<4; i++){
        bottomArr[i] = getEachBottomLoc(blockShape, i);
    }
    while(1){
        if(curLoc->Y + bottomH  == MATRIX_HEIGHT
           ||(bottomArr[1] != -1 && map[curLoc->Y + bottomArr[1] +1][curLoc->X + 1] != EMPTY_SLOT)
           ||(bottomArr[0] != -1 && map[curLoc->Y + bottomArr[0] +1][curLoc->X + 0] != EMPTY_SLOT)
           ||(bottomArr[3] != -1 && map[curLoc->Y + bottomArr[3] +1][curLoc->X + 3] != EMPTY_SLOT)
           ||(bottomArr[2] != -1 && map[curLoc->Y + bottomArr[2] +1][curLoc->X + 2] != EMPTY_SLOT)
                ){

            fixShape(map, blockShape, curLoc);

            Sleep(1000/8);
            return TRUE;
        }
        if(curLoc->Y + bottomH < MATRIX_HEIGHT){
            deleteShape(map, blockShape, curLoc);
            (curLoc->Y)++;
        }
    }

    return FALSE;
}


void deletecompleteLine(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH], int h){
    int w;
    for(w=0 ; w < MATRIX_WIDTH ; w++){
        map[h][w] = EMPTY_SLOT;
    }
}
void organizeLine(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH], int h){
    int w;
    while(h > 1){
        for(w=0; w<MATRIX_WIDTH;w++){
            map[h][w] = map[h-1][w];
        }
        h--;
    }

}
void checkifLineiscomplete(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH], position curLoc, int * score){
    int i, j, full, count =0;

    for(i=MATRIX_HEIGHT ; i >= (curLoc.Y -1); i--){
        full =0;
        for(j=0; j<MATRIX_WIDTH  ;j++){
            if(map[i][j] == EMPTY_SLOT){
                break;
            }else{
                full++;
            }
        }

        if(full == MATRIX_WIDTH){
            (*score) += 5;
            deletecompleteLine(map, i);
            organizeLine(map, i);
        }
    }

}

///////////////////////////////////////////////////////////END/////////////////////////////////////////////////////
int endgame(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int score, int bestScore){
    FILE * wfp;
    int w=0;
    for(w=0; w<MATRIX_WIDTH; w++){
        if(map[0][w] == FULL_SLOT){
            HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hand, 14);
            gotoxy(HALF_WIDTH -7, HALF_HEIGHT-2);
            printf("====== Game Over ======");
            gotoxy(HALF_WIDTH -6, HALF_HEIGHT-1);
            printf("Your Score : %4d\n", score);
            SetConsoleTextAttribute(hand, 7);
            gotoxy(1, MATRIX_HEIGHT+3);

            if(score >= bestScore){
                wfp = fopen("score.txt", "w");
                fprintf(wfp, "%d", score);
                fclose(wfp);
            }

            system("pause");
            return TRUE;
        }
    }

    return FALSE;
}

///////////////////////////////////////////////////////////START//////////////////////////////////////////////////////
int startinggame(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH]){
    int key;
    int reachBottom = FALSE;
    int one = TRUE;
    int score =0, bestScore =0;
    int blockShape[4][4] ={0};
    int blockShapeSub[4][4] = {0};
    position curLoc = {2,2};
    FILE * rfp;
    if((rfp = fopen("score.txt", "r")) == NULL){
        FILE * wfp;
        wfp = fopen("score.txt", "w");
        fprintf(wfp, "%d", 0);
        fclose(wfp);
    }
    fscanf(rfp, "%d", &bestScore);

    emptymatrix(map);
    drawborder(map);
    drawMatrix(map);

    locationInmatrix(&curLoc);
    setshape(blockShape);
    startTime();
    setshape(blockShapeSub);
    drawSmallShape(map, blockShapeSub);
    while(1){

        if(reachBottom == TRUE){
            if(endgame(map,score, bestScore)) return EXIT;

            checkifLineiscomplete(map, curLoc, &score);
            checkifLineiscomplete(map, curLoc, &score);
            locationInmatrix(&curLoc);
            copyshape(blockShape, blockShapeSub);
            setshape(blockShapeSub);
            drawSmallShape(map, blockShapeSub);
            reachBottom = FALSE;
        }

        drawSmallMap(bestScore,score);
        createShape(map,blockShape, curLoc);
        drawMatrix(map);
        reachBottom = goDown(map, blockShape, &curLoc);
        if(reachBottom == TRUE) continue;

        key = getKey();
        if(key == 't' || key =='T') break;
        if(key == 'p' || key == 'P'){
            system("pause"); system("cls");
            drawMatrix(map); drawborder(map);
        }
        if(key == SPACE){
            goSpace(map, blockShape, &curLoc);
        }
        if(key==224 || key ==0){
            key = getch();
            if(key == UP_DIRECTION){
                rotate(map, blockShape, &curLoc);
            }else if(key == LEFT_DIRECTION){
                goLeft(map, blockShape, &curLoc);
            }else if(key == RIGHT_DIRECTION){
                goRight(map, blockShape, &curLoc);
            }
        }
    }
    return EXIT;
}
