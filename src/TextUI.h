#pragma once

#include <iostream>
#include "LogicSimulator.h"

using namespace std;

class TextUI
{
    public:

        static TextUI getInstance(){
            return TextUI();
        }

        void displayMenu(){
            cout<<"1. Load logic circuit file"<<endl;
            cout<<"2. Simulation"<<endl;
            cout<<"3. Display truth table"<<endl;
            cout<<"4. Exit"<<endl;
            cout<<"Command:";
        }

        void processCommand(){
            int command;

            cin>>command; //enter command

            switch(command){
                case 1:
                        loadingFile();
                        break;
                case 2:
                        Simulation();
                        break;
                case 3:
                        truthTable();
                        break;
                case 4:
                        Exit();
                        break;
                default:
                        break;
            }
            cout<<endl;
        }
        
        bool isExit(){
            return exit;
        }

    private:
        bool exit=false;
        bool fileLoad=false; 
        LogicSimulator LS=LogicSimulator::getInstance();

        TextUI(){}

        void loadingFile(){
            string filename;

            cout<<"Please key in a file path: ";
            cin>>filename;

            fileLoad=LS.load(filename);  //open file
            if(!fileLoad) cout<<"File not found or file format error!!"<<endl; //file error
            else cout<<"Circuit: "<< LS.iPinSize()<< " input pins, "<<LS.oPinSize() //print device numbers of LS
                    <<" output pins and "<<LS.circuitSize()<<" gates"<<endl;
        }

        void Simulation(){
            if(!fileLoad) cout<<"Please load an lcf file, before using this operation."<<endl;  // file not load
            else{
                vector<int> input;
                int num;

                for(int i=0;i<LS.iPinSize();i++){        //set input Pins' value of LS
                    num=-1;
                    while(num!=0&&num!=1){               //input 0/1 otherwise error
                        cout<<"Please key in the value of input pin "<<i+1<<": ";
                        cin>>num;

                        if(num>=0&&num<=1) break;
                        cout<<"The value of input pin must be 0/1"<<endl;
                    }
                    input.push_back(num);
                }
                cout<<LS.getSimulationResult(input);  //print simulation
            }
        }

        void truthTable(){
            if(!fileLoad) cout<<"Please load an lcf file, before using this operation."<<endl; // file not load
            else cout<<LS.getTruthTable(); //print truth table
        }

        void Exit(){
            exit=true;  //exit
            cout<<"Goodbye, thanks for using LS."<<endl;
        }
};