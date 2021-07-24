#include <iostream>

using namespace std;

class EagerString{
	public:
		char* str;
		signed length = -1;
	
	EagerString(char* str_) : str(str_){
		char c = str[0];
		int i = 0;
		while(c){	
			length++;
			c = str[i++];
		}
	}
	
	EagerString& operator=(EagerString& other){
		//first must check if strings are the same by iterating through both
		if(length == other.length){
			int i = 0;
			char c = str[0]; 
			char rhsc = other.str[0];
			bool same = true;
			while(c && rhsc){
				if(c != rhsc){
					same = false;
					break;
				}

				i++;
				c = str[i];
				rhsc = other.str[i];
			}
			if(same){
				return *this;
			}
		}

		//copy lhs -> rhs
		str = other.str;		
		length = other.length;

		return *this;
	}

	bool operator<(EagerString& other){
		char c = str[0]; 
		char rhsc = other.str[0];
		int i = 0;
		while(c && rhsc){
			if(c < rhsc){
				return true;
			}
			if(rhsc < c){
				return false;
			}

			i++;
			c = str[i];
			rhsc = other.str[i];
		}

		if(!c && rhsc){
			return true;
		}
		else if(c && !rhsc){
			return false;
		}

		return false;
	}

	int getLength(){
		cout<<"EagerString Length: "<< length << " ... Returning: " << length <<endl;
		return length;
	}
};	

class LazyString{
	public:
		char* str;
		signed length;

	LazyString(char* str_) : str(str_){
		length = -1;
	}
	
	LazyString& operator=(LazyString& other){
		//first must check if strings are the same by iterating through both
		if(length == other.length){
			int i = 0;
			char c = str[0]; 
			char rhsc = other.str[0];
			bool same = true;
			while(c && rhsc){
				if(c != rhsc){
					same = false;
					break;
				}

				i++;
				c = str[i];
				rhsc = other.str[i];
			}
			if(same){
				return *this;
			}
		}

		//copy lhs -> rhs
		str = other.str;		
		length = other.length;

		return *this;
	}
	
	bool operator<(LazyString& other){
		char c = str[0]; 
		char rhsc = other.str[0];
		int i = 0;
		while(c && rhsc){
			if(c < rhsc){
				return true;
			}
			if(rhsc < c){
				return false;
			}

			i++;
			c = str[i];
			rhsc = other.str[i];
		}

		if(!c && rhsc){
			return true;
		}
		else if(c && !rhsc){
			return false;
		}

		return false;
	}

	int getLength(){
		if(length < 0){
			cout<<"EagerString Length: "<< length << " ... Calculating Now" <<endl;
			char c = str[0];
			int i = 0;
			while(c){	
				length++;
				c = str[i++];
			}
			cout<<"EagerString Length: "<< length << " ... Returning: " << length <<endl;
		}

		return length;
	}
};
	

int main(int argc, char** argv){
	char test[] = "Hello";

	cout<<"<------- GET LENGTH CHECK ------->"<<endl;
	cout<<"First test string (char*) : "<< test << endl;
	EagerString e (test);
	int eagerlength = e.getLength();

	cout<<"Returned Eager Length: " << eagerlength << endl;

	LazyString l (test);
	int lazylength = l.getLength();
	cout<<"Returned Lazy Length: " << lazylength << endl;

	char test2[] = "Goodbye";

	cout<<"Last test string (char*) : "<< test2 << endl;
	EagerString e2 (test2);
	LazyString l2 (test2);

	cout<<"<------- '<' COMPARISON CHECK ------->"<<endl;
	cout<<"Comparing EagerString1 (Hello) to New EagerString (Goodbye)"<< endl;
	cout<<"G<H Expecting False, recieved: " << (e < e2) << endl;
	cout<<"Comparing new EagerString (Goodbye) to EagerString1 (Hello)"<< endl;
	cout<<"H<G Expecting True, recieved: " << (e2 < e) << endl;
	
	cout<<"Comparing LazyString1 (Hello) to New LazyString (Goodbye)"<< endl;
	cout<<"Goodbye<Hello Expecting False, recieved: " << (l < l2) << endl;
	cout<<"Comparing new LazyString (Goodbye) to LazyString1 (Hello)"<< endl;
	cout<<"Hello<Goodbye Expecting True, recieved: " << (l2 < l) << endl;

	cout<<"<------- '=' ASSIGNMENT CHECK ------->"<<endl;
	cout<<"Assigning EagerString1 (Hello) to New EagerString (Goodbye)"<< endl;
	e = e2;
	cout<<"EagerString1 (Hello) -> (Goodbye): "<< e.str << endl; 
	
	cout<<"Assigning LazyString1 (Hello) to New LazyString (Goodbye)"<< endl;
	l = l2;
	cout<<"LazyString1 (Hello) -> (Goodbye): "<< l.str << endl; 



	return 0;
}
