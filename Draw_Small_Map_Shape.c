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
