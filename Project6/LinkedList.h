#pragma once
#include "AVLTreeSet.h"
using namespace std;

template <typename ItemType>

class LinkedList {
public:
    
    LinkedList(){
        head = NULL;
        tail = NULL;
        count = 0;
    }
    
    ~LinkedList(){
        clear();
    }
    
    struct Node {
        ItemType item;
        Node* next;
        Node* prev;
        int height = 1;
    };
    
    int count;
    Node* head;
    Node* tail;
    
    void clear(){
        while (head!=NULL) {
            Node* Current = head;
            head = head->next;
            delete Current;
            
        }
        tail = NULL;
    }  //2
    
    Node* NthFinder(int index, struct Node* head){
        Node* Current = head;
        int spot = 0;
        while (Current!=NULL) {
            if (spot==index) {
                return Current;
            }
            spot++;
            Current = Current->next;
        }
        return NULL;
    }  //3
    
    void insert(int index, const ItemType& item) {
        Node* n = new Node();
        Node* IndexAtInsert;
        n->item = item;
        IndexAtInsert = NthFinder(index, head);
        if (index==0) {
            if (head==NULL) {
                head=n;
                tail=n;
                n->next = NULL;
                n->prev = NULL;
            }
            else{
                n->next = head;
                n->prev = NULL;
                head->prev = n;
                head = n;
            }
        }
        else{
            if (IndexAtInsert==NULL) {
                n->next = NULL;
                n->prev = tail;
                tail = n;
            }
            else {
                std::cout<<IndexAtInsert->item<<std::endl;
                n->next = IndexAtInsert;
                n->prev = IndexAtInsert->prev;
                IndexAtInsert->prev = n;
            }
            n->prev->next = n;
        }
        
        IndexAtInsert = NULL;
        count++;
        delete IndexAtInsert;
    }  //6
    
    void remove(int index, std::ofstream& Out) {
        Node* IndexForRemove;
        IndexForRemove = NthFinder(index, head);
        if (IndexForRemove==head) {
            if (IndexForRemove==tail) {
                head=NULL;
                tail = NULL;
            }
            else{
                head->next->prev = NULL;
                head = head->next;
            }
        }
        else{
            if (IndexForRemove==tail) {
                tail->prev->next = NULL;
                tail = tail->prev;
            }
            else{
                IndexForRemove->next->prev = IndexForRemove->prev;
                IndexForRemove->prev->next = IndexForRemove->next;
            }
        }
        count--;
        Out<<"remove "<<index<<" "<<IndexForRemove->item<<std::endl;
        std::cout<<"remove "<<index<<" "<<IndexForRemove->item<<std::endl;
        delete IndexForRemove;
    }  //7
    
    void push(ItemType n){
        insert(count, n);
        
        /*Node* Current = head;
        while (Current->next!=NULL) {
            Current = Current->next;
        }
        Node* n = new Node();
        n->item = item;
        Current->next = n;
        count++;*/
    }
    
    ItemType pop(int& perLine, ofstream& out){
        Node* n = head;
        head = head->next;
        out<<" "<<n->item->item<<"("<<n->item->height<<")";
        perLine++;
        if (perLine==8) {
            out<<endl;
            perLine = 0;
        }
        ItemType item = n->item;
        delete n;
        n=NULL;
        count--;
        return item;
        
    }
    
    
    
    int find(const ItemType& item) {
        Node* Current = head;
        int spot = 0;
        while (Current!=NULL) {
            if (Current->item==item) {
                Current=NULL;
                delete Current;
                return spot;
            }
            Current = Current->next;
            spot++;
        }
        return -1;
        
    }  //3
    
    void print(std::ofstream& Out){
        Out<<"print"<<std::endl;
        std::cout<<"print"<<std::endl;
        Node* Current = head;
        int spot = 0;
        while (Current!=NULL) {
            Out<<"node "<<spot<<": "<<Current->item<<std::endl;
            std::cout<<"node "<<spot<<": "<<Current->item<<std::endl;
            Current = Current->next;
            spot++;
        }
        delete Current;
    }  //2
    
    
};

