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
#include <algorithm> 
#include <map>

using namespace std;

class LogicSimulator{
    private:
        string headerOne();
        string headerTwo();
        string headerThree();
        string getHeader();
        string inputPins(vector<int>);
        vector<vector<int>> inputTable();

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
            vector<vector<int>> inputMatrix=inputTable();

            output+="Truth table:\n";
            output+=getHeader();

            for(int i=0;i<inputMatrix.size();i++){
                output+=inputPins(inputMatrix[i]);
            }

            return output;
        }

        bool load(string filename){
            clear();
            string buffer=readbuf(filename);
            if(buffer=="") return false;
            vector<string> token=splitLine(buffer); 
            
            try{
                setDeviceNum(token);
                if(iPins.size()<=0) throw logic_error("No iPins");
                if(circuit.size()<=0) throw logic_error("No circuits");
                setCircuit(token);
                setOutput();
                if(oPins.size()<=0) throw logic_error("No oPins");
            }
            catch(const std::exception &e){
                clear();
                return false;
            }
            
            return true;
        }

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




