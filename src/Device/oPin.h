#pragma once

#include "./Device.h"

class oPin:public Device{
    public:

        oPin(){}

        void addInputPin(Device *val) override{
            if(iPins.size()==1) throw out_of_range("Out of Range");
            else if(val==NULL)  throw invalid_argument("Cannot add null pointer");
            else{
                iPins.push_back(val);
                val->connect=true;
            }
        }

        int getOutput() override{
            int o=iPins[0]->getOutput();
            return o;
        }
};

