#include "LogicSimulator.h"

using namespace std;

void LogicSimulator::setDeviceNum(vector<string> &token){
    int NI=0,NG=0;

    NI=stoi(token.at(0));
    NG=stoi(token.at(1));

    if(NI<=0||NG<=0) throw logic_error("error");

    token.erase(token.begin(),token.begin()+2);

    for(int i=0;i<NI;i++) iPins.push_back(new iPin());
    for(int i=0;i<NG;i++) circuit.push_back(NULL);
}

void LogicSimulator::setCircuit(vector<string> &token){

    map<Device *,vector<double>> deviceMap;

    for(int i=0;i<token.size();i++){

        stringstream ss(token.at(i));
        vector<double> subToken(istream_iterator<double>(ss),{});

        circuit[i]=deviceType((int)subToken.at(0));
        subToken.erase(subToken.begin());

        deviceMap[circuit[i]]=subToken;
    }

    for(int i=0;i<circuit.size();i++){

        vector<double> subToken=deviceMap[circuit[i]];
        for(int j=0;j<subToken.size();j++){
            double val=subToken[j];

            if(val==0) break;
            if(val<0) circuit[i]->addInputPin(iPins[abs(val)-1]);
            else if(val>0){
                circuit[i]->addInputPin(circuit[(int)val-1]);
            }
        }
    }
}

void LogicSimulator::setOutput(){

    for(int i=0;i<circuit.size();i++){
        if(!circuit[i]->isConnect()){
            oPin *o=new oPin();
            o->addInputPin(circuit[i]);
            oPins.push_back(o);
        } 
    }

}

Device* LogicSimulator::deviceType(int type){
    
    if(type==1) return new gateAND();
    else if(type==2) return new gateOR();
    else if(type==3) return new gateNot();
    
    throw logic_error("error");
}

string LogicSimulator::readbuf(string filename){
    fstream file;
    file.open(filename,ios::in);
    if(!file.is_open()) return "";
    stringstream ss;
    ss<<file.rdbuf();
    file.close();
    return string(ss.str());
}

vector<string> LogicSimulator::splitLine(string buffer){
    stringstream ss(buffer);

    string lineBuf;

    vector<string> token;

    while(getline(ss,lineBuf,'\n')){
        token.push_back(lineBuf);
    }
    return token;
}

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