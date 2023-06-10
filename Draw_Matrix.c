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
