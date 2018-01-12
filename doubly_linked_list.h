// Exam_database.h

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
#include "cmpt_error.h"

using namespace std; //empty case, case with one thing, ...... test!

class Exam_database {
private:
	struct Node {
		string name;
		int score;
		Node* next_name;
		Node* next_score;
		Node* prev_name;
		Node* prev_score;
	};
	Node* head_name;
	Node* head_score;
	Node* tail_name;
	Node* tail_score;

public:
    // Default constructor: create a new empty Exam_database.
    Exam_database()
	: head_name(nullptr), head_score(nullptr), tail_name(nullptr), tail_score(nullptr) { }

	/*head_name = new Node;
	head_score = new Node;
	tail_name = new Node;
	tail_score = new Node;*/
	
	/*head_name->next_name = tail_name;
	tail_name->prev_name = head_name;
	head_score->next_score = tail_score;
	tail_score->prev_score = head_score;

	//head_name->prev_name = nullptr;
	//head_score->prev_score = nullptr; //these 2 needed?
	tail_name->next_name = nullptr;
	tail_score->next_score = nullptr; 
}*/


    // Destructor: make sure all nodes are properly deleted
    ~Exam_database() {
		while (head_name!=nullptr) {
			Node* p=head_name;
			head_name = head_name->next_name;
			delete p;
		}
		/*while (head_score!=nullptr) {
			Node* n=head_score;
			head_score = head_score->next_score;
			delete n;
		}*/
		//delete head_score;
		//delete tail_score;

	}

    // Adds (n, s) to this Exam_database. If a pair in the database already
    // has the name n, then its corresponding score is set to s (thus names
    // occur at most in one pair).
    //
    // Also, it is assumed that name is not empty, and does not contain any
    // spaces. If it is empty or contained any spaces, then use cmpt::error to
    // throw an exception.


    void add_exam(const string& n, int s) {
	if (n.size() == 0) {
		cmpt::error("name is empty");
	}
	for (int i=0; i < n.size(); i++) {
		if (n[i] == ' ')
			cmpt::error("name contains space");
	}


	if (head_name == nullptr){ //ADDS FIRST NODE IN EMPTY LIST
		//cout<<"first one added"<<endl;
		Node* m = new Node{n, s, nullptr, nullptr, nullptr, nullptr};
		head_score = m;
		tail_score = m;
		head_name = m;
		tail_name = m;
		return;
	}

	
	Node* p = head_score; 
	while (p!=nullptr) {
		if (n==(p->name) && p==head_name && p==head_score && p==tail_score && p==tail_name) {
			p->score = s;
			return;
		}
		if (n == (p->name)) {
			p->score = s;

			if (p==head_score){ 
				p->next_score->prev_score = nullptr;
				head_score = p->next_score;
				p->next_score = nullptr;
				p->prev_score = nullptr;
				Node* t = head_score;
				while (t!=nullptr) {
			    		if(p->score <= t->score && t==head_score) {
			    			p->next_score = t;
			    			t->prev_score = p;
			    			p->prev_score = nullptr;
			    			head_score = p;
			    			//tail_score = t;
			    			return;
			    		}


			    		if(p->score <= t->score && t != head_score){
			    			p->next_score = t;
			    			p->prev_score = t->prev_score;
			    			t->prev_score->next_score = p;
			    			t->prev_score = p;
			    			return;
			    		}

			    t= t->next_score; 

			    }	
			Node* w = tail_score;
			w->next_score = p;
			p->next_score = nullptr;
			p->prev_score = w;
			tail_score = p;	 
			return;  

		    }

		    if(p==tail_score){
		    	p->prev_score->next_score = nullptr;
		    	tail_score = p->prev_score;
		    	p->prev_score = nullptr;
		    	p->next_score = nullptr;
		    	Node* t = head_score;
		    	while (t!=nullptr) {
			    		if(p->score <= t->score && t==head_score) {
			    			p->next_score = t;
			    			t->prev_score = p;
			    			p->prev_score = nullptr;
			    			head_score = p;
			    			//tail_score = t;
			    			return;
			    		}


			    		if(p->score <= t->score && t != head_score){
			    			p->next_score = t;
			    			p->prev_score = t->prev_score;
			    			t->prev_score->next_score = p;
			    			t->prev_score = p;
			    			return;
			    		}
			    t=t->next_score;		
		    	} 
		    Node* w = tail_score;
			w->next_score = p;
			p->next_score = nullptr;
			p->prev_score = w;
			tail_score = p;	 
			return;

		    }		
			p->next_score->prev_score = p->prev_score;
			p->prev_score->next_score = p->next_score;
			p->next_score = nullptr;
			p->prev_score = nullptr;
			Node* t = head_score;
	    		while (t!=nullptr) {
		    		if(p->score <= t->score && t==head_score) {
		    			p->next_score = t;
		    			t->prev_score = p;
		    			p->prev_score = nullptr;
		    			head_score = p;
		    			return;
		    		}


		    		if(p->score <= t->score && t != head_score){
		    			p->next_score = t;
		    			p->prev_score = t->prev_score;
		    			t->prev_score->next_score = p;
		    			t->prev_score = p;
		    			return;
		    		}
		    		t= t->next_score; 
		    	}
		    	Node* w = tail_score;
			w->next_score = p;
			p->next_score = nullptr;
			p->prev_score = w;
			tail_score = p;	 
			return;  
			 		
		}
		p = p->next_score;
		//q = q->next_name;
	}


	linker(n, s);
	//score_linker(n, s, r);
				


}

    // Deletes the (n, score) pair from this Exam_database. If there is no
    // pair with the name string, then this does nothing.
    void remove_exam(const string& n) {

    	Node* p = head_name;
    	if (p==nullptr) cmpt::error("can't pop empty list");

    	while (p!=nullptr) {
    		if(n==(p->name) && p==head_name && p==head_score && p==tail_score && tail_name){
    			head_name=nullptr;
    			head_score=nullptr;
    			tail_name=nullptr;
    			tail_score=nullptr;
    			delete p;
    			return; }

    		if(n==(p->name) && p==head_name && p!=head_score && p!=tail_score){
    			p->next_name->prev_name = nullptr;
    			p->next_score->prev_score = p->prev_score;
    			p->prev_score->next_score = p->next_score;
    			head_name = p->next_name;
    			delete p;
    			return;
    		}

    		if(n==(p->name) && p!=head_name && p==head_score && p!=tail_name){
    			p->next_score->prev_score = nullptr;
    			p->next_name->prev_name = p->prev_name;
    			p->prev_name->next_name = p->next_name;
    			head_score = p->next_score;
    			delete p;
    			return;
    		}

    		if(n==(p->name) && p==tail_name && p!=head_score && p!=tail_score){
    			tail_name = p->prev_name;
    			p->prev_name->next_name = nullptr;
    			p->next_score->prev_score = p->prev_score;
    			p->prev_score->next_score = p->next_score;
    			delete p;
    			return;
    		}

    		if(n==(p->name) && p==tail_score && p!=head_name && p!=tail_name){
    			tail_score = p->prev_score;
    			p->prev_score->next_score = nullptr;
    			p->next_name->prev_name = p->prev_name;
    			p->prev_name->next_name = p->next_name;
    			delete p;
    			return;
    		}

    		if(n==(p->name) && p==head_name && p==head_score){
    			p->next_name->prev_name = nullptr;
    			p->next_score->prev_score = nullptr;
    			head_name = p->next_name;
    			head_score = p->next_score;
    			delete p;
    			return;
    		}

    		if(n==(p->name) && p==head_name && p==tail_score){
    			head_name = p->next_name;
    			p->next_name->prev_name = nullptr;
    			tail_score = p->prev_score;
    			p->prev_score->next_score = nullptr;
    			delete p;
    			return;
    		}

    		if(n==(p->name) && p==tail_name && p==head_score){
    			p->prev_name->next_name = nullptr;
    			p->next_score->prev_score = nullptr;
    			tail_name = p->prev_name;
    			head_score = p->next_score;
    			delete p;
    			return;
    		}

    		if(n==(p->name) && p==tail_name && p==tail_score){
    			p->prev_name->next_name = nullptr;    			
    			p->prev_score->next_score = nullptr;
    			tail_name = p->prev_name;
    			tail_score = p->prev_score;
    			delete p;
    			return;
    		}


    		if (n==(p->name)){
    			p->next_name->prev_name = p->prev_name;
    			p->prev_name->next_name = p->next_name;
    			p->next_score->prev_score = p->prev_score;
    			p->prev_score->next_score = p->next_score;
    			delete p;
    			return;
    		}
    		p=p->next_name;
    	}
    }

    // Prints all (name, score) pairs in alphabetical order by name.
    void print_by_name() const {
	Node* p = head_name;
	while (p!=nullptr) {
		cout << "(" << p->name << ", " << p->score << ")" << endl;
		p=p->next_name;
	}
}

    // Prints all (name, score) pairs in reverse alphabetical order by name.
    void print_by_name_rev() const {
	Node* p = tail_name;
	while (p!=nullptr) {
		cout << "(" << p->name << ", " << p->score << ")" << endl;
		p=p->prev_name;
	}
}

    // Prints all (name, score) pairs from smallest to biggest by score.
    void print_by_score_ascending() const {
	Node* p = head_score;
	while (p!=nullptr) {
		cout << "(" << p->name << ", " << p->score << ")" << endl;
		p=p->next_score;
	}
}

    // Prints all (name, score) pairs from biggest to smallest by score.
    void print_by_score_descending() const {
	Node* p = tail_score;
	while (p!=nullptr) {
		cout << "(" << p->name << ", " << p->score << ")" << endl;
		p=p->prev_score;
	}
}

    void linker(const string&n, int s){

	    Node* p = head_name;
		while (p!=nullptr) {
			if (n.compare(p->name)<0 && p==head_name) { //BEGINNING OF LIST
				Node* r = new Node{n, s, head_name, nullptr, nullptr, nullptr};

				p->prev_name = r;
				//p->prev_score = r;
				head_name = r;
				//head_score = r;

				Node* k = head_score;
				while (k!=nullptr){
					if(r->score <= k->score && k==head_score){
						k->prev_score = r;
						//p->next_score = nullptr;
						r->next_score = k;
						r->prev_score = nullptr;
						head_score = r;
						return;
					}
					if (r->score <= k->score && k!=head_score){
						r->next_score = k;
						k->prev_score->next_score = r;
						r->prev_score = k->prev_score;
						k->prev_score = r;
						return;

					}
				k = k->next_score;
					
				}
				Node* w = tail_score;
		    	w->next_score = r;
		    	r->next_score = nullptr;
		    	r->prev_score = w;
		    	tail_score = r;	


				return;
			} 

			if (n.compare(p->name)<0 && p!=head_name) { //MIDDLE OF LIST
				Node* r = new Node{n, s, nullptr, nullptr, nullptr, nullptr};
				r->next_name = p;
				r->prev_name = p->prev_name;
				p->prev_name->next_name = r;
				//p->prev_score->next_score = r;
				p->prev_name = r;
				//p->prev_score = r;
				Node* t = head_score;
	    		while (t!=nullptr) {
		    		if(r->score <= t->score && t==head_score) {
		    			r->next_score = t;
		    			t->prev_score = r;
		    			r->prev_score = nullptr;
		    			head_score = r;
		    			//tail_score = t;
		    			return;
		    		}


		    		if(r->score <= t->score && t != head_score){
		    			r->next_score = t;
		    			r->prev_score = t->prev_score;
		    			t->prev_score->next_score = r;
		    			t->prev_score = r;
		    			return;
		    		}
		    		t= t->next_score;

		    	}

		    	Node* w = tail_score;
		    	w->next_score = r;
		    	r->next_score = nullptr;
		    	r->prev_score = w;
		    	tail_score = r;	    	
		    	


				/*while (q!= nullptr){
					if(r->score < q->score){
						q->prev_score->next_score = r;
						r->prev_score = q->prev_score;
						q->prev_score = r;
						r->next_score = q;
					}
					if (r->score > q->score){
						q->prev_score = nullptr;
						q->next_score = r;
						head_score = q;
						r->prev_score = q;
						r->next_score = nullptr;

					}
				}*/

				return;

			}
			
			p=p->next_name; }

			Node* q = tail_name; //END OF LIST
			Node* r = new Node{n, s, nullptr, nullptr, nullptr, nullptr};
			r->prev_name = tail_name;
			q->next_name = r;
			//q->next_score = r; ///
			tail_name = r;
			//tail_score = r;
			Node* t = head_score;
		    	while (t!=nullptr) {
		    		if(s <= t->score && t==head_score) {
		    			r->next_score = t;
		    			t->prev_score = r;
		    			r->prev_score = nullptr;
		    			head_score = r;
		    			//tail_score = t;
		    			return;
		    		}

		    		if(s <= t->score && t != head_score){
		    			r->next_score = t;
		    			r->prev_score = t->prev_score;
		    			t->prev_score->next_score = r;
		    			t->prev_score = r;
		    			return;
		    		}
		    		t= t->next_score;

		    	}

		    	Node* w = tail_score;
		    	w->next_score = r;
		    	r->prev_score = w;
		    	r->next_score = nullptr;
		    	tail_score = r;
	    	
			return;
	    }





    void score_linker(Node* &r, int s){
    	//cout<<r->score<<"r score"<< endl;
    	Node* t = head_score;
    	while (t!=nullptr) {
    		if(s < t->score && t==head_score) {
    			r->next_score = t;
    			t->prev_score = r;
    			r->prev_score = nullptr;
    			head_score = r;
    			tail_score = t;
    			return;
    		}

    		/*if(s > p->score && p==head_score){
    			p->next_score = r;
    			r->prev_score = p;
    			head_score = p;
    			tail_score = r;
    			return;
    		}*/

    		if(s < t->score && t != head_score){
    			r->next_score = t;
    			t->prev_score->next_score = r;
    			t->prev_score = r;
    			return;
    		}
    		t= t->next_score;

    	}

    	Node* q = tail_score;
    	q->next_score = r;
    	r->next_score = nullptr;
    	tail_score = r;
    	//cout<<tail_score->score<<endl;
    	return;
    	
    }

    //
    // ... you can add other helper methods here if you need them ...
    //

}; // class Test_database
