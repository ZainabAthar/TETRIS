void drawSmallMap(int best, int score){
    HANDLE control = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(control, 14);
    gotoxy(HALF_WIDTH + 4, HALF_HEIGHT+1);
    printf("%4d", best);
    gotoxy(HALF_WIDTH + 4, HALF_HEIGHT+2);
    printf("%4d", score);
    SetConsoleTextAttribute(control, 7);
}

