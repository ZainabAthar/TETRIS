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
