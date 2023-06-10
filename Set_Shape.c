void setshape(int blockShape[4][4]){

    int shape[7][4][4] = {
            {{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},
            {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
            {{0,0,0,0},{0,1,0,0},{1,1,1,0},{0,0,0,0}},
            {{0,0,1,0},{0,1,1,0},{0,1,0,0},{0,0,0,0}},
            {{0,1,0,0},{0,1,1,0},{0,0,1,0},{0,0,0,0}},
            {{0,0,0,0},{0,1,0,0},{0,1,1,1},{0,0,0,0}},
            {{0,0,0,0},{0,1,1,1},{0,1,0,0},{0,0,0,0}}
    };
    srand((unsigned int)(time(NULL)));

    switch(rand()%7) {
        case 0:
            copyshape(blockShape, shape[0]);
            break;
        case 1:
            copyshape(blockShape, shape[1]);
            break;
        case 2:
            copyshape(blockShape, shape[2]);
            break;
        case 3:
            copyshape(blockShape, shape[3]);
            break;
        case 4:
            copyshape(blockShape, shape[4]);
            break;
        case 5:
            copyshape(blockShape, shape[5]);
            break;
        case 6:
            copyshape(blockShape, shape[6]);
            break;
        default :
            break;
    }
}

