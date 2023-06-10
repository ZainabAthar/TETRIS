int endgame(playing_field map[MATRIX_HEIGHT][MATRIX_WIDTH],int score, int bestScore){
    FILE * wfp;
    int w=0;
    for(w=0; w<MATRIX_WIDTH; w++){
        if(map[0][w] == FULL_SLOT){
            HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hand, 14);
            gotoxy(HALF_WIDTH -7, HALF_HEIGHT-2);
            printf("====== Game Over ======");
            gotoxy(HALF_WIDTH -6, HALF_HEIGHT-1);
            printf("Your Score : %4d\n", score);
            SetConsoleTextAttribute(hand, 7);
            gotoxy(1, MATRIX_HEIGHT+3);

            if(score >= bestScore){
                wfp = fopen("score.txt", "w");
                fprintf(wfp, "%d", score);
                fclose(wfp);
            }

            system("pause");
            return TRUE;
        }
    }

    return FALSE;
}
