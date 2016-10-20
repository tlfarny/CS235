#include <iostream>
#include <string>
#include <fstream>
#include "AVLTreeSet.h"
#include "LinkedList.h"

using namespace std;

int main(int argc, const char * argv[]){
    ifstream in;
    ofstream out;
    AVLTreeSet<string> AVLTree;
    string cmd;
    in.open(argv[1]);
    out.open(argv[2]);
    while (in>>cmd) {
        if (cmd=="add") {
            string Name;
            in>>Name;
            AVLTree.add(Name);
            out<<"add "<<Name<<endl;
        }
        else if (cmd=="clear") {
            AVLTree.clear(AVLTree.root);
            out<<"clear"<<endl;
        }
        else if (cmd=="print") {
            out<<"print"<<endl;
            AVLTree.printing(out);
        }
        else if (cmd=="find") {
            string item;
            in>>item;
            bool Found = AVLTree.find(item);
            if (Found==true) {
                out<<"find "<<item<<" "<<"true"<<endl;
            }
            else{
                out<<"find "<<item<<" "<<"false"<<endl;
            }
        }
        else if (cmd=="remove") {
            string name;
            in>>name;
            out<<"remove "<<name<<endl;
            AVLTree.remove(name);
        }
    }
    in.close();
    out.close();
}

