#include <iomanip>

using namespace std;

#include "MailHouse.h"


int failed(){
    cout << "Failed. Exitting..." << endl << endl;
    return 0;
}

int main(int argv, char* argc[]){
    if(argv != 2){
        cout << "Invalid number of parameters..." << endl;
        return -1;
    }
    cout << "ARG" << argc[1] << endl;
    MailHouse m;
    cout << "Loading file: " << argc[1] << endl << endl;
    if(!m.loadMail(argc[1])){
        m.cleanUp();
        return failed();
    }
    cout << "SUCCESS" << endl << endl;

    cout << "Filling carriers...." << endl << endl;
    if(!m.fillCarriers()){
        m.cleanUp();
        return failed();
    }
    cout << "SUCCESS" << endl << endl;

    cout << "Delivering...." << endl << endl;
    if(!m.deliverMail()){
        m.cleanUp();
        return failed();
    }
    cout << "SUCCESS" << endl << endl;

    cout << "Cleaning up the carriers....." << endl << endl;
    m.cleanUp();

    cout << "Simulation success. Have a nice day!" << endl;
    return 0;
}
