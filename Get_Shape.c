int getShapeLeftLoc(int blockShape[4][4]){
    int i, j, leftW=4;
    for(j=0; j<4;j++){
        for(i=0; i<4;i++){
            if(blockShape[i][j] == FULL_SLOT){
                if(leftW > j)
                    leftW = j;
            }
        }
    }
    return leftW;
}
int getShapeRightLoc(int blockShape[4][4]){
    int i, j, rightW=0;
    for(j=3; j>=0;j--){
        for(i=3; i>=0;i--){
            if(blockShape[i][j] == FULL_SLOT){
                if(rightW < j)
                    rightW = j;
            }
        }
    }
    return rightW+1;
}
int getShapeBottomLoc(int blockShape[4][4]){
    int i, j, bottomH=0;
    for(j=3; j>=0;j--){
        for(i=3; i>=0;i--){
            if(blockShape[i][j] == FULL_SLOT){
                if(bottomH < i)
                    bottomH =i;
            }
        }
    }
    return bottomH+1;
}
int getEachBottomLoc(int blockShape[4][4], int w){
    int h, bottomH=-1;
    for(h=3; h>=0;h--){
        if(blockShape[h][w] == FULL_SLOT){
            if(bottomH < h)
                bottomH =h;
        }
    }
    return bottomH;
}
int getEachLeftLoc(int blockShape[4][4], int h){
    int w, leftW= 5;
    for(w=0; w<4;w++){
        if(blockShape[h][w] == FULL_SLOT){
            if(leftW > w)
                leftW = w;
        }
    }
    return leftW;
}
int getEachRightLoc(int blockShape[4][4], int h){
    int w, rightW= -1;
    for(w=0; w<4;w++){
        if(blockShape[h][w] == FULL_SLOT){
            if(rightW < w)
                rightW = w;
        }
    }
    return rightW;
}
