#ifndef SPL_ASSIGNEMNT_3_CLIENT_ENCODERDECODER_H
#define SPL_ASSIGNEMNT_3_CLIENT_ENCODERDECODER_H
#include <string>
#include <vector>
#include <iostream>


using namespace std;
class EncoderDecoder{
public:
    EncoderDecoder();
    string encode(string input);
    bool decode(string input);

private:
    string encodeRegister(string input);
    string encodeLogin(string input);
    string encodeLogout(string input);
    string encodeFollow(string input);
    string encodePost(string input);
    string encodePM(string input);
    string encodeLogstat(string input);
    string encodeStat(string input);
    string encodeBlock(string input);
    void processNotification(string input);
    bool processACK(string input);
    void processERROR(string input);

    vector<char> mergeVectors(vector<vector<char>> vec);
    vector<char> toVector(string input);
    vector<string> opcode;
    string getDateAndTime();
    string nullzero;
    string coma;



};


#endif //SPL_ASSIGNEMNT_3_CLIENT_ENCODERDECODER_H
