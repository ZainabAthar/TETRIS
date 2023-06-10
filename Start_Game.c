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
