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
