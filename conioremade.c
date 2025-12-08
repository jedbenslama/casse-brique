#include <stdlib.h>
#ifdef _WIN32
    #include <conio.h>
    #include <windows.h>
    void clearScreen(){
        int n;
        for (n = 0; n < 10; n++)
          printf( "\n\n\n\n\n\n\n\n\n\n" );
    }

#else
    #include <termios.h>
    #include <fcntl.h>
    #include <stdio.h>
    #include <unistd.h>
    
    void Sleep(int amount){
        usleep(amount*1000);
    }

    void clearScreen(){
        system("clear");
    }
    char _getch(void) {
        struct termios oldt, newt;
        char ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }

    int _kbhit(void) {
        struct termios oldt, newt;
        int ch;
        int oldf;

        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
        fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

        ch = getchar();

        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        fcntl(STDIN_FILENO, F_SETFL, oldf);

        if (ch != EOF) {
            ungetc(ch, stdin);
            return 1;
        }

        return 0;
    }
#endif