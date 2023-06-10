int before_starting_game()//before starting game page/;
{
    HANDLE control = GetStdHandle(STD_OUTPUT_HANDLE);
    int keyentered;
    gotoxy(1,2);
    SetConsoleTextAttribute(control, 4);
    printf("-----------------------------------\n");
    gotoxy(1,3);
    SetConsoleTextAttribute(control, 14);
    printf("-------------T E T R I S -----------\n");
    SetConsoleTextAttribute(control, 4);
    gotoxy(1,4);
    printf("------------------------------------\n");

    SetConsoleTextAttribute(control, 14);
    gotoxy(2,6);
    printf("Left : > \n");
    gotoxy(2,7);
    printf("Right : < \n");
   // gotoxy(2,8);
   /* printf("Rotation : ? \n");*/
    gotoxy(2,8);
    printf("Down: space \n");
    gotoxy(2,10);
    printf("Exit: 't' \n");

     //for starting game;
    while(1){
        keyentered = getKey();
        if(keyentered == 's' || keyentered == 'S') break;
        if(keyentered == 't' || keyentered == 'T') break;

        gotoxy(7, 15);
        SetConsoleTextAttribute(control, 11);
        printf(" === press 's' to start ===");
        SetConsoleTextAttribute(control, 7);
        Sleep(1000/2);
        gotoxy(7, 15);
        printf("                            ");
        Sleep(1000/2);
    }

    return keyentered;
}
