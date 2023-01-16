#pragma once

#include <vector>
#include <iostream>

using namespace std;

class Device{

    public:
        virtual void addInputPin(Device *val){
            if(val==NULL)  throw invalid_argument("Cannot add null pointer");
            else{
                iPins.push_back(val);
                val->connect=true;
            }
        }

        virtual int getOutput()=0;

        virtual ~Device(){
            iPins.clear();
        }

        bool iPinEmpty(){
            return iPins.empty();
        }

        bool isConnect(){
            return connect;
        }

    protected:
        vector<Device *> iPins;
        bool connect=false;
};


















