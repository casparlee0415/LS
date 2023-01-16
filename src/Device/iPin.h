#pragma once

#include "./Device.h"

class iPin:public Device{
    public:

        iPin(){
            input=-1;
        }

        iPin(int val){
            setInput(val);
        }

        void addInputPin(Device *val) override{
            throw logic_error("Unable to call iPin::addInputPin(device *val)");
        }

        void setInput(int val){
            if(val<0||val>1) throw invalid_argument("Input must be 0/1");
            else input=val;
        }

        int getOutput() override{
            return input;
        }

    private:

        int input;
};

