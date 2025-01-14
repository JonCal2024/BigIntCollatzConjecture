#include <iostream>
#include <vector>
#include <string>
#include <algorithm>	//reverse()
#include <cmath>		//pow()
#include <cctype>		//isdigit()
#include <limits.h>		//INT_MAX
using namespace std;

/****************************************************
* CLASS BigInt
*---------------------------------------------------
*
* Class developed to store integers larger than 
* INT_MAX and perform operations. 
* !-DOES NOT SUPPORT NEGATIVE INTEGERS-!
*****************************************************/
class BigInt
{
	 private:
		vector<char> v;		//vector representation of digits
							//v[0] = 1's place
							//v[1] = 10's place
							//v[2] = 100's place
	 						//etc.
	 	const int EXP_NOTATION = 8;	//how many digits should be printed before exponential notation is used
	 						
	 	//bool negative = false; TODO: Change string constructor to allow for negative symbol IF it is at front of string, and subtraction to not throw exception

	protected:
		/**********************
		* HELPER FUNCTIONS
		***********************/
	 	BigInt copy(const BigInt& n, const int& start, const int& end);	//copies digits of a given BigInt from given indeces (start and end inclusive)
	 	void removeLeadingZeros(BigInt& n);								//removes leading zeros in a BigInt vector

	public:
	 	/**********************
		* CONSTRUCTORS
		***********************/
	 	BigInt();			//default constructor
	 	BigInt(int n);		//int constructor
	 	BigInt(string s);	//string constructor
	 	
		/**********************
		* OPERATORS
		***********************/
		BigInt operator=(BigInt n);				//overloaded equals operator
		
	 	BigInt operator+(BigInt addend);		//overloaded addition operator	
	 	BigInt operator+(int addend);			//overloaded addition operator	
	 	
	 	BigInt operator-(BigInt subtrahend);	//overloaded subtraction operator	
	 	BigInt operator-(int subtrahend);		//overloaded subtraction operator
	 	
	 	BigInt operator++();					//pre-increment 
	 	BigInt operator++(int dummy);			//post-increment

	 	BigInt operator--();					//pre-decrement 
	 	BigInt operator--(int dummy);			//post-decrement
	 	
	 	BigInt operator*(BigInt multiplicand);	//overloaded multiplication operator
	 	BigInt operator*(int multiplicand);		//overloaded multiplication operator
	 	
	 	BigInt operator/(BigInt denominator);	//overloaded division operator
		BigInt operator/(int denominator);		//overloaded division operator
	 	
	 	BigInt operator%(BigInt n);				//overloaded modulo operator	
	 	BigInt operator%(int n);				//overloaded modulo operator

	 	BigInt operator^(int n);				//overloaded power operator

	 	int operator[](int index) const;		//overloaded index operator
	
		/**********************
		* RELATIONAL OPERATORS
		*---------------------
		* All relational operators
		* first check sizes of
		* BigInt vectors, then
		* checks elements for
		* comparisons.
		***********************/
		bool operator<(BigInt n);		//overloaded less than
		bool operator<(int n);			//overloaded less than
		bool operator>(BigInt n);		//overloaded greater than
		bool operator>(int n);			//overloaded greater than
		bool operator==(BigInt n);		//overloaded equal to 
		bool operator==(int n);			//overloaded equal to 
		bool operator!=(BigInt n);		//overloaded not equal to
		bool operator!=(int n);			//overloaded not equal to
		bool operator<=(BigInt n);		//overloaded less than or equal to
		bool operator<=(int n);			//overloaded less than or equal to
		bool operator>=(BigInt n);		//overloaded greater than or equal to
		bool operator>=(int n);			//overloaded greater than or equal to

		/**********************
		* HELPER FUNCTIONS
		***********************/
	 	string to_str();							//returns string interpretation of BigInt
	 	bool isEven() { return v[0] % 2 == 0; };	//checks if BigInt is even
	 	bool isOdd() { return v[0] % 2 == 1; };		//checks if BigInt is odd
	 	int size() const { return v.size(); };		//returns size of digit vector
};
