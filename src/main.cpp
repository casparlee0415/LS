#include <iostream>
#include <vector>
#include "LogicSimulator.h"
#include "TextUI.h"

using namespace std;

int main()
{
    TextUI textUI=TextUI::getInstance();

    while(!textUI.isExit()){
        textUI.displayMenu();
        textUI.processCommand();
    }

    return 0;
}

