#include "main.h"
class customer {
public:	
	string name;
	customer* prev;
	customer* next;
public:
	customer(){}
	customer(string na, int e, customer* p, customer *ne): name(na), prev(p), next(ne){}
	~customer(){}
};

class Restaurant {
	private:
		
	public:
	Restaurant() {

	};
	~Restaurant() {
		
	};
	void LAPSE(string name){ //chuan hoa ten khach hang
		
		//them vao nha hang
		//chon khu
	};
	void KOKUSEN(){

	};
	void KEITEIKEN(int num){

	};
	void HAND(){

	};
	void LIMITLESS(int num){

	};
	void CLEAVE(int num){

	};	
};

void simulate(string filename)
{
	ifstream ss(filename);
	int MAXSIZE;
	string str, maxsize, name, num;
	Restaurant* r = new Restaurant();
	while(ss >> str)
	{ 
		if(str == "MAXSIZE") // MAXSIZE <NUM>
		{
			ss >> maxsize;
			MAXSIZE = stoi(maxsize); 
    	}
        else if(str == "LAPSE") // LAPSE <NAME>
        {
            ss >> name;
            r->LAPSE(name);
    	}
    	else if(str == "KOKUSEN") // KOKUSEN
    	{
                ss >> num;
    			r->KOKUSEN();
		}
    	else if(str == "KEITEIKEN") // KEITEIKEN <NUM>
    	{
    			r->KEITEIKEN(stoi(num));
		}
		else if(str == "HAND") // HAND
		{
    			r->HAND();	
		}
    	else if(str == "LIMITLESS") // LIMITLESS <NUM>
     	{   	
    			r->LIMITLESS(stoi(num));
    	}
    	else // CLEAVE <NUM>
    	{
                ss >> num;
    			r->CLEAVE(stoi(num));
    	}
    }
}