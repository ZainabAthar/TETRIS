void startTime(){
    int i;
    HANDLE control = GetStdHandle(STD_OUTPUT_HANDLE);

    for(i=0 ;i<3;i++){
        gotoxy(2,0);
        SetConsoleTextAttribute(control, 14);
        printf("Start : %d sec", 3-i);
        SetConsoleTextAttribute(control, 7);
        Sleep(1000);
    }
    gotoxy(2,0);
     printf("                       ");
}
