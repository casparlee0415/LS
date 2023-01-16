#pragma once

#include "./Device.h"

class gateNot:public Device{
    public:

        gateNot(){}

        void addInputPin(Device *val) override{
            if(iPins.size()==1) throw out_of_range("Out of Range");
            Device::addInputPin(val);
        }

        int getOutput() override{
            return (~iPins[0]->getOutput()) & 0x01;
        }
};


