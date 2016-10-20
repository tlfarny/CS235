#pragma once
#include <fstream>
#include "LinkedList.h"
#include <sstream>

using namespace std;

template <typename ItemType>

class AVLTreeSet {
public:
    
    AVLTreeSet(){
        root = NULL;
        size = 0;
    }
    
    ~AVLTreeSet(){
        clear(root);
    }
    
    struct Node {
        ItemType item;
        Node* left;
        Node* right;
        int height;
        
        Node(const ItemType& itemin) {
            item = itemin;
            left = NULL;
            right = NULL;
            height = 1;
        }
    };
    
    Node* root = NULL;
    int size = 0;
    
    int getHeight(Node *node){
        int left, right;
        
        if(node==NULL){
            return 0;
        }
        left = getHeight(node->left);
        right = getHeight(node->right);
        if(left > right){
            return left+1;
        }
        else{
            return right+1;
        }
    }  //4
    
    void rotateLeftSideOnce(Node*& n){
        Node *otherNode;
        
        otherNode = n->left;
        n->left = otherNode->right;
        otherNode->right = n;
        otherNode->height = getHeight(otherNode);
        n = otherNode;
        n->height = getHeight(n);
        if (n->right!=NULL) {
            n->right->height = getHeight(n->right);
        }
        if (n->left!=NULL) {
            n->left->height = getHeight(n->left);
        }
    }  //1
    
    void rotateLeftTwice(Node*& n){
        rotateRightSideOnce(n->left);
        rotateLeftSideOnce(n);
    }  //1
    
    void rotateRightSideOnce(Node*& n){
        Node *otherNode;
        otherNode = n->right;
        n->right = otherNode->left;
        otherNode->left = n;
        otherNode->height = getHeight(otherNode);
        n = otherNode;
        n->height = getHeight(n);
        if (n->right!=NULL) {
            n->right->height = getHeight(n->right);
        }
        if (n->left!=NULL) {
            n->left->height = getHeight(n->left);
        }
    }  //1
    
    void rotateRightTwice(Node*& n){
        rotateLeftSideOnce(n->right);
        rotateRightSideOnce(n);
    }  //1
    
    void Balance(Node*& n, const ItemType& item){
        if(getHeight(n->left) - getHeight(n->right) == 2){  //Left Heavy
            if(getHeight(n->left->left) >= getHeight(n->left->right) ){
                rotateLeftSideOnce(n);
            }
            else{
                rotateLeftTwice(n);
            }
        }
        else if(getHeight(n->right) - getHeight(n->left) == 2){  //Right Heavy
            if(getHeight(n->right->right) >= getHeight(n->right->left)){
                rotateRightSideOnce(n);
            }
            else{
                rotateRightTwice(n);
            }
        }
    }  //7
    
    Node* insert(Node*& n, const ItemType& item){
        if(n == NULL){  // (1) If we are at the end of the tree place the value
            n = new Node(item);
        }
        else if(item < n->item){  //(2) otherwise go left if smaller
            insert(n->left, item);
            Balance(n, item);
            n->left->height = getHeight(n->left);
        }
        else if(item > n->item){ // (3) otherwise go right if bigger
            insert(n->right, item);
            Balance(n, item);
            n->right->height = getHeight(n->right);
        }
        n->height = getHeight(n);
        return n;
    }  //4
    
    void add(const ItemType& item) {
        root = insert(root, item);
    }  //1
    
    void clear(Node*& n){
        if (n==NULL) {
            return;
        }
        Node* Right = n->right;
        Node* Left = n->left;
        delete n;
        n=NULL;
        clear(Right);
        clear(Left);
    }  //2
    
    ItemType CTRMin(Node*& n){
        Node* Current = n;
        while (Current->left!=NULL) {
            Current = Current->left;
        }
        return Current->item;
    }  //2
    
    void removeFound(Node*& t, const ItemType& item ){
        Node* n = t;
        if (t->left==NULL) {
            t = t->right;
            delete n;
            n=NULL;
        }
        else if (t->right==NULL){
            t = t->left;
            delete n;
            n=NULL;
        }
        else{
            t->item = CTRMin(t->right);
            removeRecursion(t->right, t->item);
        }
    }  //4
    
    Node* removeRecursion(Node*& n, const ItemType& item){
        if (n==NULL) { //find
            return n;
        }
        else if (item > n->item){
            removeRecursion(n->right, item);
        }
        else if (item < n->item){
            removeRecursion(n->left, item);
        }
        else{  //Found.  Now Remove
            removeFound(n, item);
        }
        if (n!=NULL) {
            Balance(n, item);
            n->height = getHeight(n);
        }
        return n;
    }//6
    
    void remove(ItemType& item) {
        root = removeRecursion(root, item);
    }
    
    bool findRecursion(const ItemType& item, Node*& n, bool& Found){
        if (n==NULL || Found==true){
            
        }
        else if (n->item == item) {
            Found = true;
        }
        else {
            Found = findRecursion(item, n->left, Found);
            Found = findRecursion(item, n->right, Found);
        }
        return Found;
    }  //4
    
    bool find(const ItemType& item) {
        bool Found = false;
        Found = findRecursion(item, root, Found);
        return Found;
    }  //2
    
    void printRecursion(Node* n, ofstream& out){
        int row = 0;
        LinkedList<Node*> q = LinkedList<Node*>();
        if (n!=NULL) {
            q.push(n);
        }
        while (q.count!=0) {
            int perLine = 0;
            int levelSize = q.count;
            for (int i = 0; i<levelSize; i++) {
                if (perLine==0) {
                    out<<"level "<<row<<":";
                }
                Node* Parent;
                Parent = q.pop(perLine, out);
                if (Parent->left!=NULL) {
                    q.push(Parent->left);
                }
                if (Parent->right!=NULL) {
                    q.push(Parent->right);
                }
            }
            out<<endl;
            row++;
        }
    }  //7
    
    void printing(ofstream& out){
        printRecursion(root, out);
    }
};