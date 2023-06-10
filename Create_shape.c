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
