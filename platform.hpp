// platform_utils.h
#ifndef PLATFORM_UTILS_H
#define PLATFORM_UTILS_H

#include <cstdio>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

inline int getch() {
#ifdef _WIN32
    return _getch();
#else
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

inline void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

inline void pauseSystem() {
#ifdef _WIN32
    system("pause");
#else
    printf("Press any key to continue...");
    getch();
    printf("\n");
#endif
}

#endif // PLATFORM_UTILS_H
