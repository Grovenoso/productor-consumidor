#ifndef PRODUCERCONSUMER_H
#define PRODUCERCONSUMER_H

//CLEAR
#if _WIN64 || _WIN32
#define CLEAR system("cls")
#include <Windows.h>
#define SLEEP(x) Sleep(x);
#else
#define CLEAR system("clear");
#define SLEEP(x) std::this_thread::sleep_for(std::chrono::milliseconds(x));
#endif

//GOTOXY
#define GOTOXY(x, y) printf("%c[%d;%df", 0x1B, y, x);

//CURSOR
#define HIDECURSOR printf("\e[?25l");
#define SHOWCURSOR printf("\e[?25h");

//COLORS
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define BLUE "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define RESET "\x1b[0m"

#include <iostream>
#include <cstdio>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <ctime>
#include <string>
#include <conio.h>
#include <thread>

class producerConsumer
{
    private:
        //attributes
        bool state, kind, randomState;
        int index;

    public:
        //constructor
        producerConsumer(bool k) {
            //setting variables
            kind = k;
            state = false;
            index = 0;
            
            //setting the seed for random
            srand(time(NULL));
        };

        //getters
        bool getState() {return state;};
        bool getKind() {return kind;};
        int getIndex() {return index;};

        //setters
        void setState(bool data) { state = data;};
        void setKind(bool data) {kind = data;};
        void setIndex(int data) {index = data;};

        //methods
        void changeState() {            
            state = false;
        };
};

#endif