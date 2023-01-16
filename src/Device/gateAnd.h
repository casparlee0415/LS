#pragma once

#include "./Device.h"

class gateAND:public Device{
    public:

        gateAND(){}

        int getOutput() override{
            int o=1;
            for(int i=0;i<iPins.size();i++) o=o&(iPins[i]->getOutput());

            return o;
        }
};

