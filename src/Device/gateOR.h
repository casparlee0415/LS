#pragma once

#include "./Device.h"

class gateOR:public Device{
    public:

        gateOR(){}

        int getOutput() override{
            int o=0;
            for(int i=0;i<iPins.size();i++) o=o|(iPins[i]->getOutput());

            return o;
        }
};


