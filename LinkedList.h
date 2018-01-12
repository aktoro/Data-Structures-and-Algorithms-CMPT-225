// LinkedList.h

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



#include <iostream>
#include <string>
#include <sstream>
#include "cmpt_error.h"

using namespace std;

string remove_non_letters(string s){
	for(string::iterator i = s.begin(); i != s.end(); i++) { //iterates through length of string
		if(!isalpha(s.at(i - s.begin()))) { //if non-alphabetic character found
        		s.erase(i); //removes that non-alphabetic character
        		i--; // i needs to be reduced to take into account shifting of remaining characters in string to fill gap that erasing non-aplhabetic character left
		}
	}
	return s;
} 


class LinkedList {

private:
	struct Node {
		string str;
		Node* next;
	};
	Node* head;

public:

	LinkedList()
		: head(nullptr) { }
		
	~LinkedList(){
		while (head!=nullptr){
			Node* p=head;
			head = head->next;
			delete p;
		}

	}
	

	int size(){
		Node* p = head;
		int sz = 0;
		while (p!=nullptr){
			sz++;
			p = p->next; 
                }
		return sz;
	}
	

	void add(const string& s){
		Node* p = head;
		while (p!=nullptr){
			if (s == (p->str)){ // if s already exists in list, returns and exits function
				return;
			} 
			p=p->next;
		}

		head = new Node{s, head}; // if s doesn't already exist in list, added to front of list
	}


	void print(){
		Node* p = head;
		int order=1;
		while (p!=nullptr){
			cout << order << ". "<< p->str << endl;
			p = p->next;
			order++; 
			}
	}


};


///////////////////////////////

// References:

// 	CMPT 225 lecture notes on linked lists http://www.cs.sfu.ca/CourseCentral/225/tjd/singly_linked_oop_cpp.html

//	http://stackoverflow.com/questions/5422835/c-string-iterator -> how to iterate through the string to find non-alphabetic characters

///////////////////////////////
	
