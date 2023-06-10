int main() {
    char password1[10],password2[10];
    strcpy(password1,"ad123");
    do{
    printf("Enter Password: ");
    scanf("%s",password2);
    if(strcmp(password2,password1)==0)
    printf("Password is Valid\n");
    else 
    printf("Incorrect Password\n");
    	}while(strcmp(password2,password1)!=0);
    char map[MATRIX_HEIGHT][MATRIX_WIDTH] ={0};   //map
    int keyinput;
    cursor_not_shown();

    system("color 7");                      //console color
    system("mode con: cols=57 lines=25");   //console size

    while(1){
        keyinput = before_starting_game();
        if(keyinput == 't' || keyinput == 'T') break;
        system("cls");
        startinggame(map);
        Sleep(1000/3);
        system("cls");
    }
    return 0;
}
