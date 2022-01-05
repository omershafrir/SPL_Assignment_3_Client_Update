#include "../include/EncoderDecoder.h"
#include <string>
#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;
EncoderDecoder::EncoderDecoder(){
  opcode.push_back("\0");
  opcode.push_back("01");
  opcode.push_back("02");
  opcode.push_back("03");
  opcode.push_back("04");
  opcode.push_back("05");
  opcode.push_back("06");
  opcode.push_back("07");
  opcode.push_back("08");
  opcode.push_back("09");
  opcode.push_back("10");
  opcode.push_back("11");
  opcode.push_back("12");
  nullzero = string(1,'\0');
  coma = string(1,';');
}

string EncoderDecoder::encode(string input) {

    if (input.substr(0, 8) == "REGISTER") {
        return encodeRegister(input + ";");
    }
    if (input.substr(0, 5) == "LOGIN") {
        return encodeLogin(input + ";");
    }
    if (input.substr(0, 6) == "LOGOUT") {
        return encodeLogout(input + ";");
    }
    if (input.substr(0, 6) == "FOLLOW") {
        return encodeFollow(input + ";");
    }
    if (input.substr(0, 4) == "POST") {
        return encodePost(input + ";");
    }
    if (input.substr(0, 2) == "PM") {
        return encodePM(input + ";");
    }
    if (input.substr(0, 7) == "LOGSTAT") {
        return encodeLogstat(input + ";");
    }
    if (input.substr(0, 4) == "STAT") {
        return encodeStat(input + ";");
    }
    if (input.substr(0, 5) == "BLOCK") {
        return encodeBlock(input + ";");
    }
}

bool EncoderDecoder:: decode(string input){              //return value is boolean: true if ACK is for logout, false otherwise
    using namespace std;
    if (input.substr(0, 2) == "09"){    //NOTIFICATION
         processNotification(input);
         return false;
    }
    if (input.substr(0, 2) == "10"){    //ACK
        return processACK(input);
    }
    if (input.substr(0, 2) == "11"){    //ERROR
        processERROR(input);
        return false;
    }
}

string EncoderDecoder::encodeRegister(string input){
    int indexStart = 9;
    int curr = 9;
    while(input[curr] != ' '){
        curr++;
    }
    string username = input.substr(indexStart , curr - indexStart);
    indexStart = curr + 1;
    curr++;
    while(input[curr] != ' '){
        curr++;
    }
    string password = input.substr(indexStart , curr - indexStart);
    indexStart = curr + 1;
    curr++;
    while(input[curr] != ';'){
        curr++;
    }
    string birthday = input.substr(indexStart , curr - indexStart);
    string output = opcode[1]+username+nullzero+password+nullzero+birthday+nullzero+coma;
cout<<"ENCODED INPUT: "<<output<<endl;
return output;
}

string EncoderDecoder::encodeLogin(string input){
    int indexStart = 6;
    int curr = 6;
    while(input[curr] != ' '){
        curr++;
    }
    string username = input.substr(indexStart , curr - indexStart);
    indexStart = curr + 1;
    curr++;
    while(input[curr] != ' '){
        curr++;
    }
    string password = input.substr(indexStart , curr - indexStart);
    indexStart = curr + 1;
    curr++;

    string captcha(1 , input[curr]);
    string output = opcode[2]+username+nullzero+password+nullzero+captcha+coma;
    return output;
}

string EncoderDecoder::encodeLogout(string input){
    return opcode[3]+coma;
}

string EncoderDecoder::encodeFollow(string input){
    int curr = 9;
    int indexStart = 9;
    while(input[curr] != ';'){
        curr++;
    }
    string username = input.substr(indexStart , curr - indexStart);
    string output = opcode[4]+string(1,input[7])+username+nullzero+coma;
    return output;
}

string EncoderDecoder::encodePost(string input){
    int curr = 5;
    int indexStart = 5;
    while(input[curr] != ';'){
        curr++;
    }
    string content = input.substr(indexStart , curr - indexStart);
    string output = opcode[5]+content+nullzero+coma;
    return output;
}

string EncoderDecoder::encodePM(string input){
    int curr = 3;
    int indexStart = 3;
    while(input[curr] != ' '){
        curr++;
    }
    string username = input.substr(indexStart , curr - indexStart);
    indexStart = curr + 1;
    curr++;
    while(input[curr] != ';'){
        curr++;
    }
    string content = input.substr(indexStart , curr - indexStart);
    string DATEANDTIME = getDateAndTime();
    return opcode[6]+username+nullzero+content+nullzero+DATEANDTIME+coma;
}

string EncoderDecoder::encodeLogstat(string input){
    return opcode[7]+coma;
}

string EncoderDecoder::encodeStat(string input){
    int curr = 5;
    int indexStart = 5;
    while(input[curr] != ';'){
        curr++;
    }
    string users = input.substr(indexStart , curr - indexStart);
    return opcode[8]+users+nullzero+coma;
}

string EncoderDecoder::encodeBlock(string input){
    int curr = 6;
    int indexStart = 6;
    while(input[curr] != '\0'){
        curr++;
    }
    string username = input.substr(indexStart , curr - indexStart);
    cout<<input<<endl;
    cout<<username<<endl;
    return opcode[12]+username+nullzero;
}

void EncoderDecoder::processNotification(string input){
    int curr = 3;
    int indexStart = 3;
    while(input[curr] != ';'){
        curr++;
    }
    string user = input.substr(indexStart , curr - indexStart);
    indexStart = curr + 1;
    curr++;
    while(input[curr] != ';'){
        curr++;
    }
    string content = input.substr(indexStart , curr - indexStart);
    string type = "";
    if(input[2] == '0')
        type = "PM";
    else
        type = "Public";

    cout<<"NOTIFICATION "<<type<<" "<<user<<" "<<content<<endl;
}
bool EncoderDecoder::processACK(string input) {
    if (input[2] == '0' && input[3] == '3') {
    cout << "ACK " << input[2] << input[3] << " " << endl;
    return true;
    }
    else {
        int curr = 4;
        int indexStart = 4;
        while(input[curr] != ';'){
            curr++;
        }
        string content = input.substr(indexStart , curr - indexStart);
        cout << "ACK " << input[2] << input[3] << " " <<content<<endl;
        return false;
    }
}
void EncoderDecoder::processERROR(string input){
    cout<<"ERROR "<<input[2]<<input[3]<<endl;;
}

vector<char> EncoderDecoder::mergeVectors(vector<vector<char>> vec){
        int size = 0;
        for (vector<char> thisVector : vec){
            size += thisVector.size();
        }
        vector<char> output;
        int index = 0;
        for(vector<char> thisVector : vec){
            for (char byte : thisVector){
                output.push_back(byte);
            }
        }
        return output;
    }

vector<char> EncoderDecoder::toVector(string input){
        vector<char> output;
        for(int i=0 ; i<input.size() ; i++){
            output.push_back(input[i]);
        }
        return output;
    }

string EncoderDecoder::getDateAndTime(){
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    ostringstream oss;
    oss << put_time(&tm, "%d-%m-%Y %H:%M");
    auto str = oss.str();
    return str;
}

