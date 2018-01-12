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
#include <algorithm> 
#include <vector>

using namespace std;

long long s1=0; //counter for STL sort function
long long s2=0; //counter for selection sort
long long s3=0; //counter for insertion sort
long long s4=0; //counter for heapsort


class PQ_unordered { //selection sort
private:
	vector< int> u;
public:
	~PQ_unordered() {
		u.clear();
	}
	void make_empty(){
		vector< int> u;
	}
	bool is_empty(){
		if (u.empty()==true)
			return true;
		return false;
	}
	int pop_min(){
		int j=u[0];
		int pl=0;
		for (int i=0; i< u.size(); i++){
			s2++;
			if (j>u[i])
				pl=i;
		}
		j = u[pl];
		swap(u[pl], u[u.size()-1]);
		u.pop_back();
		return j;
	}	
	void insert(int x){
		u.push_back(x);
	}	
};
class PQ_ordered{ //insertion sort
private:
	vector<int> u;
public:
	~PQ_ordered() {
		u.clear();
	}
	void make_empty(){
		vector<int> u;
	}
	bool is_empty(){
		if (u.empty()==true)
			return true;
		return false;
	}
	int pop_min(){
		int j=u[0];
		u.erase(u.begin());
		return j;
	}	
	void insert(int x){
		if (is_empty()==true){
			u.insert(u.begin(), x);
			return;
		}
		int j=0;
		for (int i=0; i<u.size();i++){
			s3++;
			if (x>u[i])
				j++;
		}
		u.insert(u.begin()+j, x);
	}	
};

class PQ_heapsort{ //implementing the heap as a vector
private:
	vector<int> u;
public:
	~PQ_heapsort() {
		u.clear();
	}
	void make_empty(){
		vector<int> u;
	}
	bool is_empty(){
		if (u.empty()==true)
			return true;
		return false;
	}
	int pop_min(){
		if (u.size()==1){
			int o = u[0];
			u.pop_back();
			return o;
		}

		swap(u[0], u[u.size()-1]);
		int j = u[u.size()-1];
		u.pop_back();
		int ji = 0;

		while(1){
			if ((ji*2)+1>=u.size() && (ji*2)+2>=u.size()){
				return j;
			}

			if (u[ji]< u[(ji*2)+1] && (ji*2)+2>=u.size()){
				return j;
			}

			if(u[ji]< u[(ji*2)+1] && u[ji]< u[(ji*2)+2]){
				return j;
			}

			if (u[ji]> u[(ji*2)+1]&& (ji*2)+2>=u.size()){
				swap (u[ji], u[(ji*2)+1]);
				ji = (ji*2)+1;
				s4++;
			}
			else if ((ji*2)+1>=u.size() && u[ji] > u[(ji*2)+2]){
				swap (u[ji], u[(ji*2)+2]);
				ji = (ji*2)+2;
				s4++;
			}

			else if (u[ji]< u[(ji*2)+1] && u[ji]> u[(ji*2)+2]){
				swap (u[ji], u[(ji*2)+2]);
				ji= (ji*2)+2;
				s4++;
			}
			else if (u[ji]>u[(ji*2)+1] && u[ji]< u[(ji*2)+2]){
				swap (u[ji], u[(ji*2)+1]);
				ji= (ji*2)+1;
				s4++;
			}
			else if (u[ji]> u[(ji*2)+1] && u[ji]> u[(ji*2)+2] && u[(ji*2)+1]!=0 && u[(ji*2)+2]!=0){
				if (u[(ji*2)+2] < u[(ji*2)+1]){
					swap (u[ji], u[(ji*2)+2]);
					ji= (ji*2)+2;
					s4++;
				}
				else if (u[(ji*2)+2] > u[(ji*2)+1]){
					swap (u[ji], u[(ji*2)+1]);
					ji= (ji*2)+1;
					s4++;
				}

			}
		}
		return j;
	}	
	void insert(int x){
		u.push_back(x);
		int pos = u.size()-1;
		while (1){

			if (pos==0){
				return;
			}	
			if (pos%2==0 && u[(pos/2)-1] < u[pos]){
				return;
			}
			if (pos%2!=0 && u[(pos/2)] < u[pos]){
				return;
			}
			if (pos%2==0 && u[(pos/2)-1] > u[pos]){
				swap(u[(pos/2)-1], u[pos]);
				pos = (pos/2)-1;
				s4++;
			}
			if (pos%2!=0 && u[(pos/2)] > u[pos]){
				swap(u[(pos/2)], u[pos]);
				pos=pos/2;
				s4++;
			}
		}

	}	
};
bool less_than(int a, int b){
	s1++;
	return (a<b);
}

void stl_sort (vector<int>& v){
	sort(v.begin(), v.end(), less_than);
}

template<class PQ>
void pq_sort(vector<int>& v) {
    PQ pq;
    for(int x : v) {
        pq.insert(x);
    }
    v.clear();
    while (!pq.is_empty()) {
        v.push_back(pq.pop_min());
    }
}

int main(){

	cout<<endl;

	for (int j=5000; j<100001; j=j+5000){

		vector<int> v(j);
		for (int i=0; i<j; i++){
			v[i] = i;
		}
		random_shuffle(v.begin(), v.end());

		cout<<"##### n = "<<j<<" COMPARISONS #####"<<endl;

		stl_sort(v);
		cout<<"STL sort: "<<s1<<endl;
		random_shuffle(v.begin(), v.end());

		pq_sort<PQ_unordered>(v);
		cout<<"Selection sort: "<<s2<<endl;
		random_shuffle(v.begin(), v.end());

		pq_sort<PQ_ordered>(v);
		cout<<"Insertion sort: "<<s3<<endl;
		random_shuffle(v.begin(), v.end());
		
		pq_sort<PQ_heapsort>(v);
		cout<<"Heapsort: "<<s4<<endl;
		cout<<endl;

	}

	return 0;
}

///////////////////////////////

// References:

//  How to count comparisons for STL sort -> http://www.cplusplus.com/reference/algorithm/sort/

///////////////////////////////
