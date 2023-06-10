int getKey(){
    if(kbhit()) return getch();
    else return -1;
}
