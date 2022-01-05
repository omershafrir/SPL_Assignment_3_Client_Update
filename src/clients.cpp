
#include "../include/Client.h"
#include "../include/EncoderDecoder.h"
#include "../include/connectionHandler.h"
#include <boost/version.hpp>
#include <iostream>




using namespace std;

int main(int argc, char** argv) {
EncoderDecoder encdec;
string reg = encdec.encode("REGISTER OMER 123 3.11");
string login = encdec.encode("LOGIN OMER 123");
string logout = encdec.encode("LOGOUT");
string follow = encdec.encode("FOLLOW 1 OMER");
string post = encdec.encode("POST Heyall!");
string pm = encdec.encode("PM OMER YOMAN!");
string logstat = encdec.encode("LOGSTAT");
string block = encdec.encode("BLOCK OMERHAROCKER");
//string stat = encdec.encode("STAT OMER|EREZ|ROCKER12");
//encdec.decode("1104");
cout<<block<<endl;

char const *c = block.c_str();
for (int i=0 ; i<35 ; i++) {
    cout << c[i] << " , ";
}
//ConnectionHandler ch("omer" , 22);
//ch.sendLine(x);
}
