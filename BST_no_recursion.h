// a3.h

/////////////////////////////////////////////////////////////////////////
//
// Student Info
// ------------
//
// Name : Avneet Toor
// St.# : 301222912
// Email: avneett@sfu.ca
//
//
// Statement of Originality
// ------------------------
//
// All the code and comments below are my own original work. For any non-
// original work, I have provided citations in the comments with enough
// detail so that someone can see the exact source and extent of the
// borrowed work.
//
// In addition, I have not shared this work with anyone else, and I have
// not seen solutions from other students, tutors, websites, books,
// etc.
//
/////////////////////////////////////////////////////////////////////////


#include "cmpt_error.h"
#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////////
//
// Your task for this assignment is to implement all of the methods of the BST
// class given below, subject to a few important constraints.
//
// Here are the things your implementation **cannot** do:
//
// - You **cannot** use recursion anywhere in any of the methods you write.
//   All the methods must be implemented iteratively, i.e. using loops.
//
// - You **cannot** add new variables to the BST class, public or private. You
//   cannot add any global variables.
//
// - You **cannot** #include any other files. If you borrow code or ideas from
//   any other source, be sure to cite the source (e.g. as a comment in your
//   code).
//
// - You **cannot** use arrays or vectors or any other pre-made data
//   structure. As mentioned below, you may only use data structures that you
//   implement yourself.
//
// Here are the things your implementation **can** do:
//
// - You **can** add helper methods, either public or private, to BST. You may
//   also add helper functions outside of BST. Of course, any extra
//   methods/functions you add must follow the "cannot" rules above.
//
// - You **can** add helper classes, either in BST or outside of BST. For
//   instance, you could implement your own stack class.
//
// Put all the code necessary to implement BST correct inside a3.h, and then
// submit just this file when you are done. Put your testing code in a3.cpp.
//
// In the specification of the methods for BST, these variables are used:
//
// - n is the number of nodes in the BST
// - h is the height of the BST
// - T refers to the tree immediately before a method is called
// - T' refers to the tree immediately after the method is finished
//
///////////////////////////////////////////////////////////////////////////////

class BST {
private:
    struct Node {
        string value;
        Node* left;
        Node* right;
    };

    Node* head;

    class stack { //stack implemented as a linked list
    private:    
        struct node {
            Node* n;
            node* next;
        };

        node* top; //basically the head

    public:
        stack()
            : top(nullptr) { }
        ~stack(){
            while (top!=nullptr){
                node* p=top;
                top = top->next;
                delete p;
            }
        }

        void push(Node* s){
            top = new node{s, top};
        }    

        Node* pop(){
            if(top==nullptr)
                cmpt::error("popping empty stack");
            node* p=top;
            Node* q = top->n;
            top = top->next;
            delete p;
            return q;
        }
        int size_of_stack(){
            node* p = top;
            int sz = 0;
            while (p!=nullptr){
                sz++;
                p = p->next; 
            }
            return sz;
        }
        bool empty(){
            if (top!=nullptr)
                return false;
            else{
                return true;
            }
        }
        Node* peek(){
            return (top->n);
        }
    }; 
     

public:
    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new empty BST
    // Constraints:
    //    O(1) performance
    BST()
            : head(nullptr) { }

    // Pre-condition:
    //    none
    // Post-condition:
    //    deletes all the nodes in this BST
    // Constraints:
    //    O(n) performance
    ~BST(){
        Node* q;
        for(Node* p = head; p!= nullptr; p=q){
            if (p->left==nullptr){
                q=p->right;
                delete p;
            }
            else {
                q=p->left;
                p->left = q->right;
                q->right = p;
            }
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the number of string in this tree (i.e. n)
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    int size() const{
        if (head==nullptr)
            return 0;
        if (head->left == nullptr && head->right == nullptr)
            return 1;
        stack st;
        Node* p;
        int n=0;
        st.push(head);
        while (st.empty() ==false){
            p = st.pop();
            n++;           
            if (p->right !=nullptr)
                st.push(p->right);
            if (p->left !=nullptr)
                st.push(p->left);
        }
        return n;

    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the height of this tree
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    // Note:
    //    The height of a BST is the number of links in the longest
    //    root-to-leaf path in the tree. An empty tree is height 0,
    //    and a tree with a single node is also height 0.
    int height() const{

        class queue { //queue implemented as a linked list, queue used height function only
        private:    
            struct no {
                Node* n;
                no* next;
            };

            no* rear;
            no* front;

        public:
            queue()
                : rear(nullptr), front(nullptr) { }

            void enqueue(Node* s){
                no* p= new no{s, nullptr};
                if (front == nullptr){
                    front = p;
                    rear=p;
                }
                else {
                    rear->next = p;
                    rear = p;
                    rear->next=nullptr;
                }

            }    

            Node* dequeue(){
                if(front==nullptr)
                    cmpt::error("popping empty stack");
                no* p=front;
                Node* q = front->n;
                front = front->next;
                delete p;
                return q;
            }
            bool empty(){
                if (rear!=nullptr && front != nullptr)
                    return false;
                else{
                    return true;
                }
            }
        }; 



        if (head==nullptr) return 0;
        if (head->left== nullptr && head->right==nullptr) return 0;
        int h=0;
        queue q;
        Node* p = head;
        q.enqueue(head);
        q.enqueue(nullptr);
        while (q.empty()==false){
            p=q.dequeue();
            if (p==nullptr){
                if (!q.empty()){
                    q.enqueue(nullptr);
                }
                h++;
            }
            else {
                if (p->left !=nullptr)
                    q.enqueue(p->left);
                if (p->right!= nullptr)
                    q.enqueue(p->right);

            }

        }
        return h-1;

    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns true if s is in this tree, and false otherwise
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    bool contains(const string& s) const{
        if (head==nullptr)
            return false;
        if (s.compare(head->value)==0)
            return true;

        Node* p = head;
        if (s.compare(head->value)<0)
            p = head->left;
        if (s.compare(head->value)>0)
            p = head->right;
        while (p != nullptr){
            if (s.compare(p->value)==0)
                return true;

            if (s.compare(p->value)!=0 && s.compare(p->value)<0 && p->left ==nullptr){
                return false;
            }  
            if (s.compare(p->value)!=0 && s.compare(p->value)>0 && p->right ==nullptr){
                return false;
            }   
            
            if (s.compare(p->value)!=0 && s.compare(p->value)<0 && p->left !=nullptr){
                p=p->left;
            }
            
            if (s.compare(p->value)!=0 && s.compare(p->value)>0 && p->right !=nullptr){
                p=p->right;
            }        
        }
        return false;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    T'.contains(s)
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    // Note:
    //    If s is already in T, then insert(s) does nothing.
    void insert(const string& s){
        if (head==nullptr){
            head = new Node{s, nullptr, nullptr};
            return;
        }
        
        if(contains(s)==true)
            return;

        Node* p = head;
        if (head->left == nullptr && s.compare(head->value)<0 && s.compare(head->value)!=0){
            Node* r = new Node{s, nullptr, nullptr};
            head->left = r;
            return;
        }
        if (head->right == nullptr && s.compare(head->value)>0 && s.compare(head->value)!=0){
            Node* r = new Node{s, nullptr, nullptr};
            head->right = r;
            return;
        }
        if (s.compare(head->value)<0)
            p = head->left;
        if (s.compare(head->value)>0)
            p = head->right;
        while (p != nullptr){
            if (s.compare(p->value)==0)
                    return;
            if (s.compare(p->value)!=0 && s.compare(p->value)<0 && p->left ==nullptr){
                Node* r = new Node{s, nullptr, nullptr};
                p->left = r;
                return;
            }
            if (s.compare(p->value)!=0 && s.compare(p->value)>0 && p->right==nullptr){
                Node* r = new Node{s, nullptr, nullptr};
                p->right = r;
                return;
            }
            if (s.compare(p->value)!=0 && s.compare(p->value)<0 && p->left !=nullptr){
                p=p->left;
            }
            
            if (s.compare(p->value)!=0 && s.compare(p->value)>0 && p->right !=nullptr){
                p=p->right;
            }        
        }
        return;

    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    !T'.contains(s)
    // Constraints:
    //    worst-case O(h) performance; does not use recursion!
    // Note:
    //    If s is not in T, then remove(s) does nothing.
    void remove(const string& s){
        if (head==nullptr)
            cmpt::error("can't remove from empty tree");
        if (contains(s)==false)
            return;
        Node* p=head;
        if (s.compare(p->value)==0 && p->left==nullptr && p->right==nullptr){
            head=nullptr;
            delete p;
            return;
        }
        if (s.compare(p->value)==0 && p->left!=nullptr && p->right==nullptr){
            head=p->left;
            delete p;
            return;
        }
        if (s.compare(p->value)==0 && p->left==nullptr && p->right!=nullptr){
            head=p->right;
            delete p;
            return;
        }
        if (s.compare(p->value)==0 && p->left!=nullptr && p->right!=nullptr){
                head = p->left;
                Node* r = p->right;
                Node* a = p->left;
                while(a->right!=nullptr){
                    a=a->right;
                }
                a->right=r;
                delete p;
                return;
        }

        while(p!=nullptr){
            if (p->left!=nullptr && s.compare(p->left->value)==0 && p->left->left==nullptr && p->left->right==nullptr){
                Node* q = p->left;
                p->left = nullptr;
                delete q;
                return;
            }
            if (p->left!=nullptr && s.compare(p->left->value)==0 && p->left->left!=nullptr && p->left->right==nullptr){
                Node* q = p->left;
                p->left = p->left->left;
                delete q;
                return;
            }
            if (p->left!=nullptr && s.compare(p->left->value)==0 && p->left->left==nullptr && p->left->right!=nullptr){
                Node* q = p->left;
                p->left = p->left->right;
                delete q;
                return;
            }
            if (p->left!=nullptr && s.compare(p->left->value)==0 && p->left->left!=nullptr && p->left->right!=nullptr){
                Node* q = p->left;
                Node* r = p->left->right;
                Node* a = p->left->left;
                while(a->right!=nullptr){
                    a=a->right;
                }
                p->left = p->left->left;
                a->right=r;
                delete q;
                return;
            }
            if (p->right!=nullptr && s.compare(p->right->value)==0 && p->right->left==nullptr && p->right->right==nullptr){
                Node* q = p->right;
                p->right = nullptr;
                delete q;
                return;
            }
            if (p->right!=nullptr && s.compare(p->right->value)==0 && p->right->left!=nullptr && p->right->right==nullptr){
                Node* q = p->right;
                p->right = p->right->left;
                delete q;
                return;
            }
            if (p->right!=nullptr && s.compare(p->right->value)==0 && p->right->left==nullptr && p->right->right!=nullptr){
                Node* q = p->right;
                p->right = p->right->right;
                delete q;
                return;
            }
            if (p->right!=nullptr && s.compare(p->right->value)==0 && p->right->left!=nullptr && p->right->right!=nullptr){
                Node* q = p->right;
                Node* r = p->right->left;
                Node* a = p->right->right;
                while(a->left!=nullptr){
                    a=a->left;
                }
                p->right = p->right->right;
                a->left=r;
                delete q;
                return;
            }    
            if(s.compare(p->value)<0){
                p=p->left;
            }
            else {
                p=p->right;
            }
        }
        return;
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in pre-order order
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    void print_preorder() const{

        if (head==nullptr) return;

        stack st;
        Node* p;
        st.push(head);
        while (st.empty() ==false){
            p = st.pop();
            cout<<p->value<<endl;            
            if (p->right !=nullptr)
                st.push(p->right);
            if (p->left !=nullptr)
                st.push(p->left);
        }
    }

    void print_leftmost(Node* m) const{ //prints the outer left-most side, from leaf to head (excluded)
        stack st;
        m=m->left;
        Node* q;
        while (m!=nullptr){
            st.push(m);
            m=m->left;
        }
        while (st.empty()==false){
            q=st.pop();
            cout<<q->value<<endl;
        }
    }
    void print_rightmost(Node* m) const{ //prints the outer right-most side, from head (excluded) to leaf
        while (m!=nullptr){
            cout<<m->value<<endl;
            m=m->right;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in in-order order
    //    (i.e. alphabetical order)
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    void print_inorder() const{
        if (head==nullptr) return;

        stack st;
        Node* p=head->left;
        Node* q;
        if (head->left != nullptr){
            while (p!=nullptr){
                st.push(p);
                p=p->left;
            }
            while (st.empty() ==false){            
                q=st.pop();
                cout<<q->value<<endl;
                if (q != head && q->right !=nullptr)
                    print_leftmost(q->right);
                    print_rightmost(q->right);
            }
            cout<<head->value<<endl;

        }
        if (head->left==nullptr)
            cout<<head->value<<endl;

        if (head->right!=nullptr){
            p=head->right;
            while (p!=nullptr){
                st.push(p);
                p=p->left;
            }
            while (st.empty() ==false){            
                q=st.pop();
                cout<<q->value<<endl;
                if (q != head && q->right !=nullptr)
                    print_leftmost(q->right);
                    print_rightmost(q->right);
            }
        }

    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    prints all the strings in T to cout in post-order order
    // Constraints:
    //    worst-case O(n) performance; does not use recursion!
    void print_postorder() const{
        if (head==nullptr) return;

        stack st;
        stack out;
        st.push(head);
        while (!st.empty()) {
            Node* p = st.peek();
            out.push(p);
            st.pop();
            if (p->left)
              st.push(p->left);
            if (p->right)
              st.push(p->right);
          }
        while (!out.empty()) {
            cout << out.peek()->value <<endl;
            out.pop();
        }
    }
}; // class BST

///////////////////////////////

// References:

//  How to implement a queue in C++ -> http://www.sanfoundry.com/cpp-program-implement-queue-linked-list/

//  Ideas on how to implement height -> http://www.geeksforgeeks.org/iterative-method-to-find-height-of-binary-tree/

///////////////////////////////