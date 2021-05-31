#ifndef MANAGER_H
#define MANAGER_H

#include "producerConsumer.h"

class manager
{
    private:
        //attributes
        producerConsumer p = producerConsumer(true);
        producerConsumer c = producerConsumer(false);
        bool elements[20], turn;
        int randomTurn;

    public:
        //initializing the element list
        //at the beginning the producer will be on 
        //and the consumer will be off
        manager(){
            for (int i(0); i<20; ++i)
                elements[i] = false;
            
            p.setIndex(0);
            c.setIndex(0);
            randomTurn = 0;
        };

        //methods
        void mainMethod();
        void draw();
        int execution();
        bool isFullOrEmpty(bool c);
};

//method that keeps the execution on loop
//until the esc key is pressed
void manager::mainMethod()
{
    int x;
    do
    {
        //if we return here and randomTurn variable isn't 0
        //it means the turn was interrupted
        if(randomTurn){
            GOTOXY(48, 3);
            std::cout << "--- Turno interrumpido ---";
        }

        //Decision on who can get into buffer
        GOTOXY(48, 4);
        std::cout << "Toma de turno: ----------";

        turn = rand()%2;
        
        //Dramatic pause
        SLEEP(2000);

        if(turn){
            p.setState(1);
            c.setState(0);
        }
        else{
            p.setState(0);
            c.setState(1);
        }

        //Cleaning up the "turn interrupted" warning
        GOTOXY(48, 3);
        std::cout << "                          ";
        
        //We go to execution
        x = execution();

        //If the escape key is pressed the program ends
        if (kbhit())
            x = getch();
    } while (x != 27);
}

//shows the data and its changes
void manager::draw()
{

    GOTOXY(48, 4);
    std::cout << "Toma de turno: " << (turn ? "Productor " : "Consumidor");
    
    GOTOXY(48, 5);
    for(auto x: elements){
        std::cout << (x ? YELLOW : CYAN);
        std::cout << (x ? " O " : " - ") << RESET;
    }

    GOTOXY(48, 6);
    for(int i(0); i<20; ++i){
        std::cout << (i < 10 ? " " : "") << i+1 << " ";
    }

    GOTOXY(50, 8);
    std::cout << "PRODUCTOR - "
              << (p.getState() ? GREEN : RED)
              << (p.getState() ? "Trabajando" : "Durmiendo ") 
              << RESET;
    
    GOTOXY(50, 9);
    if(p.getState())
        std::cout << "Turnos restantes: " << randomTurn;
    else
        std::cout << "                   ";

    GOTOXY(85, 8);
    std::cout << "CONSUMIDOR - "
              << (c.getState() ? GREEN : RED)
              << (c.getState() ? "Trabajando" : "Durmiendo ")
              << RESET;
    
    GOTOXY(85, 9);
    if(c.getState())
        std::cout << "Turnos restantes: " << randomTurn;
    else
        std::cout << "                   ";
}

//returns if the array of elements is full or empty by a bool
//true = checks on Full
//false = checks on Empty
bool manager::isFullOrEmpty(bool c)
{
    for(auto x: elements)
        if(!x == c)
            return false;
    return true;
}

//handles the execution of the states
//manages the production and cosumption
int manager::execution()
{   
    //if the element queue is full
    //forcefully the producer is shut off
    if(isFullOrEmpty(1)){
        p.setState(0);
        c.setState(1);
    }
    
    //if the element queue is empty
    //forcefully the consumer is shut off
    if(isFullOrEmpty(0)){
        c.setState(0);
        p.setState(1);
    }
        
    randomTurn = (rand()%4)+3;
    
    //if the consumer is off the producer can work
    if(!c.getState()){
        p.setState(1);
        for (; randomTurn > 0 && !isFullOrEmpty(1); randomTurn--){
            elements[p.getIndex()] = 1;
            p.setIndex((p.getIndex()+1)%20);
            draw();
            SLEEP(500);
            
            if(!(rand()%10))
                return 0;

            if(kbhit())
                return getch();
        }
    }
    
    //if the producer is off the consumer can work
    if(!p.getState()){
        c.setState(1);
        for (;randomTurn > 0 && !isFullOrEmpty(0); randomTurn--){
            elements[c.getIndex()] = 0;
            c.setIndex((c.getIndex() + 1) % 20);
            draw();
            SLEEP(500);

            if (!(rand() % 10))
                return 0;

            if(kbhit())
                return getch();
        }
    }
}

#endif