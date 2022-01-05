#include "../include/Client.h"
#include "../include/EncoderDecoder.h"
#include "../include/connectionHandler.h"
#include <boost/version.hpp>
#include <iostream>
#include <thread>
#include <string>

using namespace std;

//Client::Client(string host, short port ,EncoderDecoder _encdec):
//    handler(host , port) , encdec(_encdec) , shouldTerminate(false){
//}
    int main(int argc, char** argv) {
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
            return -1;
        }
        std::string host = argv[1];
        short port = atoi(argv[2]);

        EncoderDecoder encdec;
        ConnectionHandler handler(host, port);
        bool fal = false;
        bool *shouldTerminate = &fal;

        if (!handler.connect()) {                     //connection failed
            cerr << "Cannot connect to " << host << ":" << port << endl;
            return 1;
        }

        thread keyboardInput([shouldTerminate , &handler , &encdec]() -> void {
//        const short bufsize = 1024;
//        char buf[bufsize];
            while (!(*shouldTerminate()) {          //writing loop
//            cin.getline(buf, bufsize);            //echo client implemantation
//            string line(buf);
//            int len=line.length();

                string input;
                cin >> input;
                string encoded = encdec.encode(input);
                if (!handler.sendLine(encoded)) {
                    cout << "Message sending failed.\n" << endl;
                }
                // connectionHandler.sendLine(line) appends ';' to the message. Therefor we send len+1 bytes.
//            cout << "Sent " << len+1 << " bytes to server" << endl;
            }
        });

        while (!shouldTerminate) {          //reading loop
            string answer;
            // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
            // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
            if (!handler.getLine(answer)) {
                cout << "Message sending failed.\n" << endl;
                *shouldTerminate = encdec.decode(answer);
            }
        }
    keyboardInput.join();

}