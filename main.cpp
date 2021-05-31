#include "manager.h"

void getCurrentState(producerConsumer &p);

int main()
{    
    manager m;
    
    HIDECURSOR;
    CLEAR;
    m.mainMethod();
    CLEAR;
    SHOWCURSOR;
    
    return 0;
}