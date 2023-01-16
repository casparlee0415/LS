#pragma once

#include "./Device/Device.h"
#include "./Device/iPin.h"
#include "./Device/oPin.h"
#include "./Device/gateAnd.h"
#include "./Device/gateOR.h"
#include "./Device/gateNot.h"
#include <vector>
#include <fstream>
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <iterator>
#include <map>

using namespace std;

class LogicSimulator{
    private:
        string headerOne();
        string headerTwo();
        string headerThree();
        string inputPins();
        void clear();

        void setDeviceNum(vector<string> &);
        void setCircuit(vector<string> &);
        void setOutput();

        static Device* deviceType(int);
        static string readbuf(string);
        static vector<string> splitLine(string);
        
        vector<Device *> circuit;
        vector<Device *> iPins;
        vector<Device *> oPins;

    public:
        string getSimulationResult(vector<int> input){
            string output="";
            stringstream ss;

            output+="Simulation Result:\n"; 
            output+=getHeader();
            output+=inputPins(input);      //Input values into input Pins.

            return output;
        }

        string getTruthTable(){
            string output="";
            stringstream ss;
            vector<int> input;

            int N=(int)pow(2,iPins.size());  //There are 2^(iPin number) kinds of input.

            output+="Truth table:\n";
            output+=getHeader();

            for(int i=0;i<N;i++){
                for(int j=0;j<iPins.size();j++)  input.push_back((i>>(iPins.size()-j-1))&0x01);
                output+=inputPins(input);
                input.clear();
            }

            return output;
        }

        bool load(string filename);

        

        ~LogicSimulator(){
            clear();
        }

        int iPinSize(){
            return iPins.size();
        }

        int oPinSize(){
            return oPins.size();
        }

        int circuitSize(){
            return circuit.size();
        }
};


string LogicSimulator::headerOne(){
    string output="";
    stringstream ss;

    for(int i=0;i<iPins.size();i++){    // "i i i i ......| o"
        ss<<setw(to_string(i+1).length())<<setfill(' ')<<'i';
        output+=ss.str()+" ";
        ss.str("");
    }
    output+="|";

    for(int i=0;i<oPins.size();i++){
        ss<<setw(to_string(i+1).length())<<setfill(' ')<<'o';
        output+=" "+ss.str();
        ss.str("");
    }
    output+="\n";

    return output;
}

string LogicSimulator::headerTwo(){
    string output="";

    for(int i=0;i<iPins.size();i++) output+=to_string(i+1)+" "; //"1 2 3 ......| 1"
    output+="|";

    for(int i=0;i<oPins.size();i++) output+=" "+to_string(i+1);
    output+="\n";

    return output;
}

string LogicSimulator::headerThree(){
    string output="";
    stringstream ss;

    for(int i=0;i<iPins.size();i++){
        ss<<setfill('-')<<setw(to_string(i+1).length())<<'-';
        output+=ss.str()+"-";                                   //"------........+--"
        ss.str("");
    }
    output+="+";

    for(int i=0;i<oPins.size();i++){
        ss<<setfill('-')<<setw(to_string(i+1).length())<<'-';
        output+="-"+ss.str(); //"------........+--"
        ss.str("");
    }
    output+="\n";

    return output;
}

string LogicSimulator::getHeader(){
    string output="";

    output+=headerOne();
    output+=headerTwo();
    output+=headerThree();

    return output;
}

string LogicSimulator::inputPins(vector<int> input){
    stringstream ss;
    string output="";

    for(int i=0;i<iPins.size();i++) ((iPin *)iPins[i])->setInput(input[i]);

    for(int i=0;i<iPins.size();i++){  //"0 0 0 ......| 0"
        ss<<setfill(' ')<<setw(to_string(i+1).length())<<iPins[i]->getOutput();
        output+=ss.str()+" ";
        ss.str("");
    }
    output+="|";

    for(int i=0;i<oPins.size();i++){  //"0 0 0 ......| 0"
        ss<<setfill(' ')<<setw(to_string(i+1).length())<<oPins[i]->getOutput();
        output+=" "+ss.str();
        ss.str("");
    }
    output+="\n";

    return output;
}

void LogicSimulator::clear(){
    for(int i=0;i<iPins.size();i++) delete iPins[i];
    iPins.clear();

    for(int i=0;i<circuit.size();i++) delete circuit[i];
    circuit.clear();

    for(int i=0;i<oPins.size();i++) delete oPins[i];
    oPins.clear();
}

