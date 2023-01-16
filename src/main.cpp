#include <iostream>
#include <vector>
#include "LogicSimulator.h"
#include "TextUI.h"

using namespace std;

int main()
{
    TextUI textUI; 

    while(!textUI.isExit())
    {
        textUI.displayMenu();
        textUI.processCommand();
    }

}

