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
