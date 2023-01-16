#include "LogicSimulator.h"

using namespace std;


bool LogicSimulator::load(string filename){

    clear();
    
    string buffer=readbuf(filename);

    if(buffer=="") return false;

    vector<string> token=splitLine(buffer); 

    try{
        setDeviceNum(token);
        if(iPins.size()<=0) throw logic_error("No iPins");
        setCircuit(token);
        if(circuits.size()<=0) throw logic_error("No circuits");
        setOutput();
        if(oPins.size()<=0) throw logic_error("No oPins");
    }
    catch(const std::exception &e){
        clear();
        return false;
    }
    
    return true;
}

void LogicSimulator::setDeviceNum(vector<string> &token){
    int NI=0,NG=0;

    NI=stoi(token.at(0));
    NG=stoi(token.at(1));

    if(NI<=0||NG<=0) throw logic_error("error");

    token.erase(token.begin(),token.begin()+2);

    for(int i=0;i<NI;i++) iPins.push_back(new iPin());
    for(int i=0;i<NG;i++) circuits.push_back(NULL);
}

void LogicSimulator::setCircuit(vector<string> &token){

    map<Device *,vector<double>> deviceMap;

    for(int i=0;i<token.size();i++){

        stringstream ss(token.at(i));
        vector<double> subToken(istream_iterator<string>(ss),{});

        circuits[i]=deviceType((int)subToken.at(0));
        subToken.erase(subToken.begin());

        deviceMap[circuits[i]]=subToken;
    }

    for(int i=0;i<circuits.size();i++){

        vector<double> subToken=deviceMap[circuits[i]];
        for(int j=0;j<subToken.size();j++){
            double val=subToken[j];

            if(val==0) break;
            if(val<0) circuits[i]->addInputPin(iPins[abs(val)-1]);
            else if(val>0){
                circuits[i]->addInputPin(circuits[(int)val-1]);
            }
        }
    }
}

void LogicSimulator::setOutput(){

    for(int i=0;i<circuits.size();i++){
        if(!circuits[i]->isConnect()){
            oPin *o=new oPin();
            o->addInputPin(circuits[i]);
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