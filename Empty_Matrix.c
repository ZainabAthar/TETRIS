void emptymatrix(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH]){
    int i, j=0;
    for(i=0;i<MATRIX_HEIGHT;i++){
        for(j=0; j<MATRIX_WIDTH; j++){
            map[i][j] = EMPTY_SLOT;
        }
    }
}
