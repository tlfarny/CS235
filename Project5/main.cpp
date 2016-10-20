#include <iostream>
#include <string>
#include <fstream>
#include "LinkedList.h"

using namespace std;

int main(int argc, const char * argv[]){
    ifstream in;
    ofstream out;
    LinkedList<string> List;
    string cmd;
    in.open(argv[1]);
    out.open(argv[2]);
    while (in>>cmd) {
        if (cmd=="insert") {
            int index;
            string name;
            in>>index;
            in>>name;
            List.insert(index, name, out);
        }
        else if (cmd=="clear") {
            List.clear();
            out<<"clear"<<std::endl;
            std::cout<<"clear"<<std::endl;
        }
        else if (cmd=="print") {
            List.print(out);
        }
        else if (cmd=="find") {
            string NameToFind;
            in>>NameToFind;
            int position = List.find(NameToFind);
            out<<"find "<<NameToFind<<" "<<position<<endl;
            cout<<"find "<<NameToFind<<" "<<position<<endl;
        }
        else if (cmd=="remove") {
            int index;
            in>>index;
            List.remove(index, out);
        }
    }
    in.close();
    out.close();
}

