// Bigram.h

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

#include "Bigram_base.h"
#include <vector>
#include <string>
#include <iostream>
#include <math.h>
#include "cmpt_error.h"

//
// Put any other standard includes or helper functions/classes you need ...
//
int siz = 0; //global variable for size

int minv = 0; //global variable for integer value min
int maxv = 0; //global variable for integer value max
Bigram_key mink; //global variable for Bigram_key value min
Bigram_key maxk; //global variable for Bigram_key value max

vector <int> vmid; //these two vectors will store keys and integer values so when
vector <Bigram_key> kmid; //a min/max gets deleted we can look into these to find the new min/max

class Bigram : public Bigram_base {
private:
	struct triplet{
		Bigram_key key;
		int value;
		int tomb; // 1 means it is a tombstone, that it has been removed.
	};
	vector <triplet*> v;


public:

	Bigram()
		: v(500000) { }

	~Bigram() { 
		for (int i=0; i<v.size(); i++){
			if (v[i]!=NULL)
				delete v[i];
		}
		v.clear();
	}	

	int size() const{
		return siz;
	} 

	int capacity() const{
		return v.capacity();
	}

	bool contains(const Bigram_key& key) const {
		string com = key.first + key.second;
		int sum = 0;
		int p=1;
		for (unsigned int i = 0; i < com.size(); i++) {
			sum = sum + (com[i]*33); //a=33, prime constant
		}
		int mod = sum%capacity();
		int orig = sum%capacity();
		while (1){
			if (mod>=capacity()){
				return false;
			}	

			if (v[mod]!=NULL && v[mod]->key.first==key.first && v[mod]->key.second==key.second && v[mod]->tomb ==0){
				return true;
			}
			mod = orig+pow(p, 2);
			if (mod>=capacity()){
				mod = mod - capacity();
			}

			if (mod==orig)
				return false;
			p++;
		}
	}

	int value_of(const Bigram_key& key) const{
		if (contains(key)==false)
			cmpt::error("key does not exist, value cannot be obtained");
		string com = key.first + key.second;
		int sum = 0;
		int p=1;
		for (unsigned int i = 0; i < com.size(); i++) {
			sum = sum + (com[i]*33);
		}
		int mod = sum%capacity();
		int orig = sum%capacity();
		while (1){
			if (v[mod]->key.first==key.first && v[mod]->key.second==key.second && v[mod]->tomb ==0){
				return v[mod]->value;
			}
			mod = orig+pow(p, 2);
			if (mod>=capacity())
				mod = mod - capacity();
			p++;
		}
	}

	void put(const Bigram_key& key, int val){
		if (load_factor()>=0.5) //if load factor >= 0.5 goes to rehash function and rehashes every element
			rehash();
		string com = key.first + key.second;
		int sum = 0;
		int p=1;
		for (unsigned int i = 0; i < com.size(); i++) {
			sum = sum + (com[i]*33); 
		}
		int mod = sum%capacity();
		int orig = sum%capacity();

		minmax(key, val); //checks and sets any new min/max values
		if (vmid.size()!=0 && minv==vmid[0] && mink.first==kmid[0].first && mink.second==kmid[0].second){
			vmid.erase(vmid.begin());
			kmid.erase(kmid.begin());
		}
		if (vmid.size()!=0 && maxv==vmid[vmid.size()-1] && maxk.first==kmid[kmid.size()-1].first && maxk.second==kmid[kmid.size()-1].second){
			vmid.pop_back();
			kmid.pop_back();
		}

		while (1){

			if (v[mod]!=NULL && v[mod]->key.first==key.first && v[mod]->key.second==key.second && v[mod]->tomb ==0){
				v[mod]->value=val;
				return;
			}
			if (v[mod]==NULL){
				v[mod] = new triplet{key, val, 0};
				siz++;
				return;
			}
			if (v[mod]!=NULL && v[mod]->tomb==1){
				v[mod] = new triplet{key, val, 0};
				siz++;
				return;
			}
			mod = orig+pow(p, 2);
			if (mod>=capacity())
				mod = mod - capacity();
			p++;
		}

	}

	void remove(const Bigram_key& key){
		if (contains(key)==false)
			return;
		string com = key.first + key.second;
		int sum = 0;
		int p=1;
		for (unsigned int i = 0; i < com.size(); i++) {
			sum = sum + (com[i]*33); 
		}
		int mod = sum%capacity();
		int orig = sum%capacity();
		while (1){
			if (v[mod]!=NULL && v[mod]->key.first==key.first && v[mod]->key.second==key.second && v[mod]->tomb ==0){
				v[mod]->tomb=1;
				minmax_remove(mod); //checks if the removed value was a max/min, and proceeds accordingly
				siz--;
				return;
			}
			mod = orig+pow(p, 2);
			if (mod>=capacity())
				mod = mod - capacity();
			p++;
		}
	
	}

	Bigram_key max() const{
		return maxk;
	}

	Bigram_key min() const{
		return mink;
	}

	void minmax(const Bigram_key& key, int val){ //this function sets any new min/max values 
		if (minv==0 && maxv==0){
			minv = val;
			maxv = val;
			mink = key;
			maxk = key;
		}	

		if (minv==val && maxv==val){
			if (operator<=(key, mink)==1){ //when 1 means key is smaller than mink
				vmid.push_back(val);
				kmid.push_back(mink);
				mink = key;
				maxk = key;
			}
			return;	
		}	

		if (minv==val){ //performs tiebreaker for min value
			if (operator<=(key, mink)==1){
				for (int i=0; i<vmid.size(); i++){
					if (val<vmid[i]){
						vmid.insert(vmid.begin()+i, val);
						kmid.insert(kmid.begin()+i, mink);
						break;
					}
				}	
			}
			mink = key;		
			return;
		}	
		if (maxv==val){ //performs tiebreaker for max value
			if (operator<=(key, mink)==1){
				for (int i=0; i<vmid.size(); i++){
					if (val<vmid[i]){
						vmid.insert(vmid.begin()+i, val);
						kmid.insert(kmid.begin()+i, maxk);
						break;
					}
				}	
			}	
			maxk = key;	

			return;
		}	

		if (val <minv){
			if (vmid.size()==0){
				vmid.push_back(minv);
				kmid.push_back(mink);
				minv = val;
				mink = key;
				return;

			}
			if (minv>vmid[vmid.size()-1]){
				vmid.push_back(minv);
				kmid.push_back(mink);
				minv = val;
				mink = key;
				return;
			}
			if (minv<vmid[0]){
				vmid.insert(vmid.begin(), minv);
				kmid.insert(kmid.begin(), mink);
				maxv = val;
				maxk = key;
				return;
			}
			for (int i=0; i<vmid.size(); i++){
					if (minv<vmid[i]){
						vmid.insert(vmid.begin()+i, minv);
						kmid.insert(kmid.begin()+i, mink);
						break;
					}
			}		
			minv = val;
			mink = key;
			return;
		}

		if (val >maxv){
			if (vmid.size()==0){
				vmid.push_back(maxv);
				kmid.push_back(maxk);
				maxv = val;
				maxk = key;
				return;

			}
			if (maxv<vmid[0]){
				vmid.insert(vmid.begin(), maxv);
				kmid.insert(kmid.begin(), maxk);
				maxv = val;
				maxk = key;
				return;
			}

			if (maxv>vmid[vmid.size()-1]){
				vmid.push_back(maxv);
				kmid.push_back(maxk);
				maxv = val;
				maxk = key;
				return;
			}
			for (int i=0; i<vmid.size(); i++){
					if (maxv<vmid[i]){
						vmid.insert(vmid.begin()+i, maxv);
						kmid.insert(kmid.begin()+i, maxk);
						break;
					}
			}		
			maxv = val;
			maxk = key;
			return;
		}

		if (val >minv && val<maxv){ //once the new value is deemed not to be a max/min,
			if (vmid.size()==0){ //it gets stored into these vectors in case a max/min
				vmid.insert(vmid.begin(), val); //gets deleted, then we can look in here for new max/min
				kmid.insert(kmid.begin(), key);
				return;
			}
			if (val>vmid[vmid.size()-1]){
				vmid.push_back(val);
				kmid.push_back(key);
				for (int j=0; j<vmid.size(); j++)
				return;		
			}
			for (int i=0; i<vmid.size(); i++){
					if (val<vmid[i]){
						vmid.insert(vmid.begin()+i, val);
						kmid.insert(kmid.begin()+i, key);
						for (int j=0; j<vmid.size(); j++)
						return;
					}
			}
		}
		
	}

	void minmax_remove(int pos){ //executes when the item to be removed has a max or min value
		if (v[pos]->value==maxv && v[pos]->value==minv && vmid.size()==1){
			maxv = vmid[0];
			maxk = kmid[0];
			minv = vmid[0];
			mink = kmid[0];
			vmid.pop_back();
			kmid.pop_back();
			return;
		}
		if (v[pos]->value==maxv && vmid.size()==0){
			maxv = minv;
			maxk = mink;
			return;
		}
		if (v[pos]->value==minv && vmid.size()==0){
			minv = maxv;
			mink = maxk;
			return;
		}
		if (v[pos]->value==maxv && vmid.size()==1){
			maxv = vmid[0];
			maxk = kmid[0];
			vmid.pop_back();
			kmid.pop_back();
			return;
		}
		if (v[pos]->value==minv && vmid.size()==1){
			minv = vmid[0];
			mink = kmid[0];
			vmid.pop_back();
			kmid.pop_back();
			return;
		}
		if (v[pos]->value==maxv){
			maxv = vmid[vmid.size()-1];
			maxk = kmid[kmid.size()-1];
			vmid.pop_back();
			kmid.pop_back();
			return;
		}
		if (v[pos]->value==minv){
			minv = vmid[0];
			mink = kmid[0];
			kmid.erase(kmid.begin());
			vmid.erase(vmid.begin());
			return;
		}

		for (int j=0; j<vmid.size(); j++){
			if (vmid[j] == v[pos]->value){
				kmid.erase(kmid.begin()+j);
				vmid.erase(vmid.begin()+j);
				return;
			}
		}	
	}


	void rehash(){
		vector<triplet*> u(capacity()*2);

		for (int i=0; i<v.capacity(); i++){
			if (v[i]!=NULL && v[i]->tomb==0){
				triplet* addin = v[i];
				string com = v[i]->key.first + v[i]->key.second;
				int sum = 0;
				int p=1;
				for (unsigned int i = 0; i < com.size(); i++) {
					sum = sum + (com[i]*33);
				}
				int mod = sum% u.capacity();
				int orig = sum% u.capacity();

				while (1){

					if (u[mod]==NULL){
						u[mod] = addin;
						break;
					}
	
					mod = orig+pow(p, 2);
					if (mod>=u.capacity())
						mod = mod - u.capacity();
					p++;
				}
			}
		}
		
		v=u;

	}


    // Implement all the non-implemented methods from Bigram_base here. Be
    // sure to include a default constructor that creates a new empty Bigram.

}; // class Bigram