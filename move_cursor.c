void gotoxy(int x, int y){
    COORD Pos;
    Pos.X = 2*x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
