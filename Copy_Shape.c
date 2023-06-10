void copyshape(int blockShape[4][4], int copy[4][4]){
    int i, j;
    for(i=0;i<4;i++){
        for(j=0; j<4;j++){
            blockShape[i][j] = copy[i][j];
        }
    }
}
