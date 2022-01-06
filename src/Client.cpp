#include "../include/Client.h"
#include "../include/EncoderDecoder.h"
#include "../include/connectionHandler.h"
#include <boost/version.hpp>
#include <iostream>
#include <thread>
#include <string>
#include <mutex>
#include <chrono>

using namespace std;

    int main(int argc, char** argv) {


        //////////////////////////thread waiting example//////////////////////////////////
        /**
        mutex mu;
        unique_lock<mutex> lock(mu);
        condition_variable cond;
        thread th([&lock , &cond]()->void{
            cout<<"TH BLOCKED"<<endl;
            cond.wait(lock);
            cout<<"TH FREE!"<<endl;

        });
        this_thread::sleep_for(std::chrono::milliseconds (200));
        for (int i=0 ; i<=10 ;i++){
            cout<<i<<"..."<<endl;
        }
        cond.notify_all();


        th.join();
        **/
        ////////////////////////// ~thread waiting example//////////////////////////////////

        //////////////////////////////////////Main-COMPLETED////////////////////////////////
        //REGISTER OMER 123 33.10.1996
        if (argc < 3) {
            std::cerr << "Usage: " << argv[0] << " host port" << std::endl << std::endl;
            return -1;
        }
        std::string host = argv[1];
        short port = atoi(argv[2]);

        EncoderDecoder encdec;
        ConnectionHandler handler(host, port);
        mutex mu;
        unique_lock<mutex> lock(mu);
        condition_variable cond;
        bool fal = false;
        bool *shouldTerminate = &fal;

        if (!handler.connect()) {                     //connection failed
            cerr << "Cannot connect to " << host << ":" << port << endl;
            return 1;
        }

        thread keyboardInput([shouldTerminate , &handler , &encdec , &lock , &cond , fal]() -> void {

            while (!(*shouldTerminate)) {          //writing loop
                string input;
                input.clear();
                getline(cin , input);
                //cout<<"input is: "<<input<<endl;
                string encoded = encdec.encode(input);
                bool success = handler.sendLine(encoded);
                if (success) {
                    if(input.substr(0 , 6) == "LOGOUT")
                        cond.wait(lock);
                }
                else {
                    cout << "Message sending failed.\n" << endl;
                }


            }
        });

        while (!(*shouldTerminate)) {          //reading loop
            string answer;

            // Get back an answer: by using the expected number of bytes (len bytes + newline delimiter)
            // We could also use: connectionHandler.getline(answer) and then get the answer without the newline char at the end
            handler.getLine(answer);
            string output="";
            if(answer[0] == '\n')
                output = answer.substr(1 , answer.length() -1);
            else
                output = answer;
            fal = encdec.decode(output);
            cout<<"CLIENT READS: "<<output<<endl;
            answer.clear();
            //////////////////////////////////////////
//            char const *c = answer.c_str();
//            for (int i=0 ; i<35 ; i++) {
//                cout << c[i] << " , ";
//            }
            ////////////////////////////////////////////
            if(*shouldTerminate)
                cond.notify_all();
        }
    keyboardInput.join();

        ////////////////////////////////////// ~Main-COMPLETED////////////////////////////////

    }