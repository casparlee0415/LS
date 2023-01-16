#pragma once

#include "./Device.h"

class oPin:public Device{
    public:

        oPin(){}

        void addInputPin(Device *val) override{
            if(iPins.size()==1) throw out_of_range("Out of Range");
            Device::addInputPin(val);
        }

        int getOutput() override{
            int o=iPins[0]->getOutput();
            return o;
        }
};

