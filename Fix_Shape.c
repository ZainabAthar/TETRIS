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
