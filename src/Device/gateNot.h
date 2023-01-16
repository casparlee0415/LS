#pragma once

#include "./Device.h"

class gateNot:public Device{
    public:

        gateNot(){}

        void addInputPin(Device *val) override{
            if(iPins.size()==1) throw out_of_range("Out of Range");
            else if(val==NULL)  throw invalid_argument("Cannot add null pointer");
            else{
                iPins.push_back(val);
                val->connect=true;
            }
        }

        int getOutput() override{
            return (~iPins[0]->getOutput()) & 0x01;
        }
};


