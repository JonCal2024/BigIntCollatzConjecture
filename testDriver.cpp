#include <iostream>
#include <vector>
#include <string>
#include <algorithm>		//reverse()
#include <cmath>		//pow()
#include <cctype>		//isdigit()
#include <limits.h>		//INT_MAX
using namespace std;

/**********************************************
* NAME: 		Jonny Olswang
* DATE:			May 3, 2023
* CLASS:		CECS 325-01, MW 6:00p-7:15p
* PROGRAM 7: 	3n + 1 BigInt
*
* I certify that this program is my own original work. I did not copy any part of this program from
* any other source. I further certify that I typed each and every line of code in this program.
* ---------------------------------------------
* This program takes in positive integers from
* the command line to test the Collatz conjecture.
* The values generated from the conjecture are
* stored in a custom BigInt class to prevent
* overflow.
***********************************************/


const int EXP_NOTATION = 8;	//how many digits should be printed before exponential notation is used

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

	 	BigInt power(int n);				//power operator

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

/****************************************************
* STRUCT Statistics
*
* This struct keeps track of a given number's stats
* as we perform the Collatz conjecture. 
*****************************************************/
struct Statistics
{
	BigInt start = 0;	//starting number
	BigInt steps = 0;	//number of steps to base case
	BigInt max = 0;		//largest number in sequence
	BigInt odd = 0;		//number of odd values in sequence
	BigInt even = 0;	//number of even values in sequence
};

/**********************
* PROTOTYPES
***********************/
void findThreeNp1(BigInt num, Statistics& stats, bool printSteps);	//recursive function to run Collatz conjecture
void printStats(const Statistics& stats);							//prints given Statistics struct
ostream & operator<<(ostream & os, const BigInt & n);				//overloaded output stream operator

BigInt operator+(int iNum, BigInt biNum);							//overloaded addition operator for int + BigInt
BigInt operator-(int iNum, BigInt biNum);							//overloaded subtraction operator for int - BigInt
BigInt operator*(int iNum, BigInt biNum);							//overloaded multiplication operator for int * BigInt
BigInt operator/(int iNum, BigInt biNum);							//overloaded division operator for int / BigInt

int main()
{
	try
	{
		BigInt MAX(INT_MAX);
		cout <<	"The largest integer is " << MAX << endl;
		cout << "Twice the largest integer is " << MAX * 2 << endl;
		BigInt start(INT_MAX);
		//BigInt start(12);
		bool printSteps = false;
		Statistics stats = {};
		stats.start = start;
		stats.steps = 0;
		stats.max = 0;
		stats.odd = 0;
		stats.even = 0;
		findThreeNp1(start, stats, printSteps);
		cout << endl;
		printStats(stats);
	}
	catch(const char* e)
	{
		cout << e << endl;
	}
	 
	 return 0;
}

/****************************************************
* copy(BigInt, int start, int end)
* return: BigInt
*
* Copies the digits of the given BigInt from indeces
* [start, end] and returns value as a BigInt.
*****************************************************/
BigInt BigInt::copy(const BigInt& n, const int& start, const int& end)
{
	string store = "";
	for(int i = start; i <= end; i++)
	{
		store += to_string(n.v[i]);
	}
	return BigInt(store);
}

/****************************************************
* removeLeadingZeros(BigInt&)
* return: void
*
* Removes leading zeros in vector of passed BigInt
* reference.
*****************************************************/
void BigInt::removeLeadingZeros(BigInt& n)
{
	while(n.v.size() > 1 && n.v.back() == (char)0)
	{
		n.v.pop_back();
	}
}

/****************************************************
* BigInt()
* return: none
*
* Default constructor for BigInt class, sets value to 0.
*****************************************************/
BigInt::BigInt()
{
	v.push_back(0);
}

/****************************************************
* BigInt(int)
* return: none
*
* Overloaded constructor that sets value of BigInt
* to passed int.
*****************************************************/
BigInt::BigInt(int n)
{
	if(n == 0)
	{
		v.push_back(0);
	}
	else
	{
		char digit;
		while (n > 0)
		{
			digit = n % 10;
			n /= 10;
			v.push_back(digit);
		}	
	}
}

/****************************************************
* BigInt(string)
* return: none
*
* Overloaded constructor that sets value of BigInt
* to passed string. If string contains a non-numeric 
* character, exception is thrown and program ends.
*****************************************************/
BigInt::BigInt(string s)
{
	for(int i = 0; i < (int)s.length(); i++)
	{
		if(!isdigit(s[i]))
		{
			throw "\nTerminated: invalid std::string argument passed to BigInt::BigInt(string) overloaded constructor";
		}	
	}
	
	for(int i = s.length() - 1; i >= 0; i--)
	{
		v.push_back((int)s[i] - 48);
	}
}

/****************************************************
* operator+(BigInt)
* return: BigInt
*
* Overloaded addition operator that takes in a BigInt
* and adds it to *this BigInt, returning the sum as
* a BigInt.
*****************************************************/
BigInt BigInt::operator+(BigInt addend)
{	
	BigInt sum("");		//empty BigInt object
	int position = 0;	//index to calculate elements and store into sum 
	int carry = 0;		//carry to add to NEXT calculation, SHOULD ONLY BE A 1 OR 0
	int placesSum = 0;	//sum of individual elements at the position in each vector

	while(position < (int)v.size() && position < (int)addend.v.size())	//start at 1's position and move up, ends when position is greater than or equal to either vector size
	{
		placesSum = v[position] + addend.v[position] + carry;	//calculate sum of elements at index position in each vector
		sum.v.push_back(placesSum % 10);	//get digit in 1's places
		if(placesSum > 9)					//if placesSum is more than one digit, set carry to 1
		{
			carry = 1;
		}
		else								//else set carry to 0
		{
			carry = 0;
		}
		position++;							//increment position counter
	}

	while(position < (int)v.size())		//if native vector is the larger one, copy elements over to sum, including carry
	{
		placesSum = v[position] + carry;
		sum.v.push_back(placesSum % 10);
		if(placesSum > 9)
		{
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		position++;
	}

	while(position < (int)addend.v.size())	//if passed vector is the larger one, copy elemnts over to sum, including carry
	{
		placesSum = addend.v[position] + carry;
		sum.v.push_back(placesSum % 10);
		if(placesSum > 9)
		{
			carry = 1;
		}
		else
		{
			carry = 0;
		}
		position++;
	}

	if(carry > 0)	//if both vectors are the same size and a carry remains, push it to the back of the sum vector
	{
		sum.v.push_back(carry);
	}

	removeLeadingZeros(sum);

	return sum;
}

/****************************************************
* operator+(int)
* return: BigInt
*
* Overloaded addition operator that takes in an int
* and adds it to *this BigInt, returning the sum as
* a BigInt.
*****************************************************/
BigInt BigInt::operator+(int addend)
{
	return *this + BigInt(addend);
}

/****************************************************
* operator-(BigInt)
* return: BigInt
*
* Overloaded subtraction operator that takes in a BigInt
* and adds it to *this BigInt, returning the difference
* as a BigInt. If a negative number is generated by
* operation, exception is thrown.
*****************************************************/
BigInt BigInt::operator-(BigInt subtrahend)
{
	if(subtrahend > *this)	//if difference would be negative, throw exception (TODO: allow for negatives with negative bool var?)
	{
		throw "\nTerminated: negative value generated from BigInt::operator-(BigInt) operation";
	}
	
	BigInt difference("");	//empty BigInt object
	int position = 0;		//position index to traverse vectors
	int carry = 0;			//carry to subtract from NEXT operation, SHOULD ONLY BE 1 OR 0
	int placesDiff = 0;		//difference of individual elements at the position in each vector

	while(position < (int)v.size() && position < (int)subtrahend.v.size())
	{
		placesDiff = v[position] - subtrahend.v[position] - carry;	//difference of elements at index position in each vector, minus carry
		difference.v.push_back(placesDiff % 10);					//push back digit at 1's place
		if(placesDiff < 0)	//if placesDiff is negative, set carry to 1 and add 10 to latest element of difference vector to get correct value
		{
			carry = 1;
			difference.v[position] += 10;
		}
		else	//else set carry to 0
		{
			carry = 0;
		}
		position++;	//increment position
	}

	while(position < (int)v.size())	//only loop if native vector has more elements than given BigInt's vector
	{
		placesDiff = v[position] - carry;
		difference.v.push_back(placesDiff % 10);
		if(placesDiff < 0)
		{
			carry = 1;
			difference.v[position] += 10;
		}
		else
		{
			carry = 0;
		}
		position++;
	}
	
	removeLeadingZeros(difference);

	return difference;
}

/****************************************************
* operator-(int)
* return: BigInt
*
* Overloaded subtraction operator that takes in an int
* and adds it to *this BigInt, returning the difference
* as a BigInt. If a negative number is generated by
* operation, exception is thrown.
*****************************************************/
BigInt BigInt::operator-(int subtrahend)
{
	return *this - BigInt(subtrahend);
}

/****************************************************
* operator++()
* return: BigInt
*
* Overloaded pre-increment operator that increases
* value of *this BigInt by 1 and returns new value. 
*****************************************************/
BigInt BigInt::operator++()
{	
	*this = *this + BigInt(1);
	return *this;
}

/****************************************************
* operator++(int)
* return: BigInt
*
* Overloaded post-increment operator that increases
* value of *this BigInt by 1 and returns previous value. 
*****************************************************/
BigInt BigInt::operator++(int)
{	
	BigInt postReturn = *this;
	*this = *this + BigInt(1);
	return postReturn;
}

/****************************************************
* operator--()
* return: BigInt
*
* Overloaded pre-decrement operator that decreases
* value of *this BigInt by 1 and returns new value. 
*****************************************************/
BigInt BigInt::operator--()
{	
	*this = *this - BigInt(1);
	return *this;
}

/****************************************************
* operator--(int)
* return: BigInt
*
* Overloaded post-decrement operator that decreases
* value of *this BigInt by 1 and returns previous value. 
*****************************************************/
BigInt BigInt::operator--(int)
{	
	BigInt postReturn = *this;
	*this = *this - BigInt(1);
	return postReturn;
}

/****************************************************
* operator*(BigInt)
* return: BigInt
*
* Overloaded multiplication operator that takes in a 
* BigInt and multiplies it to *this BigInt, returning
* the product as a BigInt.
*****************************************************/
BigInt BigInt::operator*(BigInt multiplicand)
{
	BigInt product(0);			//ultimate return product
	BigInt placesProduct(0);	//product of a places digit times the other BigInt

	//Multiplication uses looped addition to find product, for efficiency we first
	//check if *this BigInt is smaller than the passed BigInt. If it is, we use the
	//value of *this as the loop control, and add the passed BigInt together to get
	//product. If *this is not smaller than passed BigInt, opposite logic applies. 
	if(*this < multiplicand)	
	{
		for(int i = 0; i < (int)v.size(); i++)
		{	
			for(int j = 0; j < (int)v[i]; j++)
			{
				placesProduct = placesProduct + multiplicand; 
			}

			for(int k = 0; k < i; k++)
			{
				placesProduct.v.insert(placesProduct.v.begin(), (char)0);
			}

			product = product + placesProduct;
			placesProduct = 0;
		}
	}
	else
	{
		for(int i = 0; i < (int)multiplicand.v.size(); i++)	
		{	
			for(int j = 0; j < (int)multiplicand.v[i]; j++)
			{
				placesProduct = placesProduct + *this; 
			}

			for(int k = 0; k < i; k++)
			{
				placesProduct.v.insert(placesProduct.v.begin(), (char)0);
			}

			product = product + placesProduct;
			placesProduct = 0;
		}
	}

	removeLeadingZeros(product);
	
	return product;
}

/****************************************************
* operator*(int)
* return: BigInt
*
* Overloaded multiplication operator that takes in an 
* int and multiplies it to *this BigInt, returning
* the product as a BigInt.
*****************************************************/
BigInt BigInt::operator*(int multiplicand)
{
	return *this * BigInt(multiplicand);
}

/****************************************************
* operator/(BigInt)
* return: BigInt
*
* Overloaded division operator that takes in a 
* BigInt and divides *this BigInt with it, returning
* the quotient as a BigInt. Throws an exception if
* the divisor is 0. (Developed by following the theory
* behind long division, my crowning jewel of this program).
*****************************************************/
BigInt BigInt::operator/(BigInt divisor)
{
	if(divisor == 0)	//throw exception if divisior is 0
	{
		throw "Terminated: division by zero\n";
	}
	if(divisor > *this)	//per int division, if divisor is greater than *this BigInt, return 0
	{
		return BigInt(0);
	}
	else if(divisor == *this)	//if BigInts are equal, return 1
	{
		return BigInt(1);
	}

	int placesQuotient = 0;	//will calculate quotient of individual elements, SHOULD NEVER BE MORE THAN 9
	BigInt quotient("");	//empty BigInt object
	string remainder = "";	//remainder string, will be used to come up with value for next calculation
	
	BigInt dividend = *this;	//sub-vector of *this vector, will be used to calculate all the sub-division operations

	//dividend needs start as the leading digits of *this BigInt THAT IS GREATER THAN DIVISOR.
	//Since implementation of vector has leading digits at END of vector, we need to reverse 
	//the vector to put leading digits at from, resize dividend vector to match the size of 
	//the divisor vector, and re-reverse the dividend to match up with BigInt implementation
	//again. 
	reverse(dividend.v.begin(), dividend.v.end());	
	dividend.v.resize(divisor.v.size());
	reverse(dividend.v.begin(), dividend.v.end());

	//Here we check if dividend is greater than divisor. At this point, the two BigInts will be 
	//the same size. If dividend is smaller, we insert the next leading digit from *this BigInt
	//to the start of the dividend vector to make dividend larger than the divisor.
	if(dividend < divisor)
	{
		dividend.v.insert(dividend.v.begin(), v[v.size() - dividend.v.size() - 1]);
	}

	//This for loop should run until the dividend has gone through each digit in *this vector.
	//Incrementation of loop control is handled inside loop.
	for(int i = v.size() - dividend.v.size(); i >= 0; placesQuotient = 0)
	{
		//This while loop is used to calculate how many divisors can fit inside the dividend.
		while(divisor * (placesQuotient + 1) <= dividend)
		{
			placesQuotient++;
		}
		//Insert value of placesQuotient at the start of quotient's vector, and calculate the 
		//remainder and store it into a string. Set the dividend to a BigInt of the remainder.
		quotient.v.insert(quotient.v.begin(), placesQuotient);
		remainder = (dividend - divisor * placesQuotient).to_str();
		dividend = BigInt(remainder);
		removeLeadingZeros(dividend);

		//This for loop adds digits to the dividend vector until the dividend object is greater
		//than or equal to the divisor, getting the dividend ready for the next calculation. If
		//the remainder from previous calculation was 0, remove the digit zero from the dividend
		//vector. If multiple digits are needed to make the dividend greater than or equal to
		//the divisor, then we push a 0 to the quoteint vector to account for offset in answer.
		for(int j = 1; dividend < divisor; j++)
		{
			if(dividend == 0)
			{
				dividend.v.pop_back();
			}
			if(j >= 2 && i >= 0)
			{
				quotient.v.insert(quotient.v.begin(), (char)0);
			}
		
			dividend.v.insert(dividend.v.begin(), v[--i]);
		}
	}

	removeLeadingZeros(quotient);
	
	return quotient;
}

/****************************************************
* operator/(int)
* return: BigInt
*
* Overloaded division operator that takes in an 
* int and divides *this BigInt with it, returning
* the quotient as a BigInt. Throws an exception if
* the divisor is 0.
*****************************************************/
BigInt BigInt::operator/(int denominator)
{
	return *this / BigInt(denominator);
}

/****************************************************
* operator%(BigInt)
* return: BigInt
*
* Overloaded modulo operator that takes in a BigInt 
* and modulos *this BigInt with it, returning
* the remainder as a BigInt.
*****************************************************/
BigInt BigInt::operator%(BigInt divisor)
{	
	if(divisor == 0)	//throw exception if divisior is 0
	{
		throw "Terminated: division by zero\n";
	}
	if(divisor > *this)	//per modulo operation, if divisor is greater than *this BigInt, return *this
	{
		return *this;
	}
	else if(divisor == *this)	//if BigInts are equal, return 0
	{
		return BigInt(0);
	}

	return BigInt(*this - (divisor * (*this / divisor)));	//return the divident minus the quotient of int division times the divisor
}

/****************************************************
* operator%(int)
* return: BigInt
*
* Overloaded modulo operator that takes in an int 
* and modulos *this BigInt with it, returning
* the remainder as a BigInt.
*****************************************************/
BigInt BigInt::operator%(int n)
{
	return *this % BigInt(n);
}

/****************************************************
* power(int)
* return: BigInt
*
* Power operator that takes in an int and
* raises *this to that power.
*****************************************************/
BigInt BigInt::power(int n)
{
	BigInt product = *this;
	for(int i = 1; i < n; i++)
	{
		product = product * *this;
	}
	return product;
}

/****************************************************
* operator[](int)
* return: int
*
* Overloaded index operator that takes in an index
* and returns the digit at that index.
*****************************************************/
int BigInt::operator[](int index) const
{
	return v[index];
}

/****************************************************
* operator<(BigInt)
* return: bool
*
* Overloaded less than operator that takes in a BigInt 
* and compares *this BigInt with it, returning true if
* *this < BigInt, false otherwise.
*****************************************************/
bool BigInt::operator<(BigInt n)
{
	if(v.size() < n.v.size())
	{
		return true;
	}
	else if(v.size() > n.v.size())
	{
		return false;
	}
	else
	{
		for(int i = v.size() - 1; i >= 0; i--)
		{
			if(v[i] < n.v[i])
			{
				return true;
			}
			else if(v[i] > n.v[i])
			{
				return false;
			}
		}
	}

	return false;
}

/****************************************************
* operator<(int)
* return: bool
*
* Overloaded less than operator that takes in an int 
* and compares *this BigInt with it, returning true if
* *this < int, false otherwise.
*****************************************************/
bool BigInt::operator<(int n)
{
	return *this < BigInt(n);
}

/****************************************************
* operator>(BigInt)
* return: bool
*
* Overloaded greater than operator that takes in a BigInt 
* and compares *this BigInt with it, returning true if
* *this > BigInt, false otherwise.
*****************************************************/
bool BigInt::operator>(BigInt n)
{
	if(v.size() > n.v.size())
	{
		return true;
	}
	else if(v.size() < n.v.size())
	{
		return false;
	}
	else
	{
		for(int i = v.size() - 1; i >= 0; i--)
		{
			if(v[i] > n.v[i])
			{
				return true;
			}
			else if(v[i] < n.v[i])
			{
				return false;
			}
		}
	}

	return false;
}

/****************************************************
* operator>(int)
* return: bool
*
* Overloaded less than operator that takes in an int 
* and compares *this BigInt with it, returning true if
* *this > int, false otherwise.
*****************************************************/
bool BigInt::operator>(int n)
{
	return *this > BigInt(n);
}

/****************************************************
* operator==(BigInt)
* return: bool
*
* Overloaded equal to operator that takes in a BigInt 
* and compares *this BigInt with it, returning true if
* *this == BigInt, false otherwise.
*****************************************************/
bool BigInt::operator==(BigInt n)
{
	if(v.size() != n.v.size())
	{
		return false;
	}

	for(int i = 0; i < (int)v.size(); i++)
	{
		if(v[i] != n.v[i])
		{
			return false;
		}
	}
	return true;
}

/****************************************************
* operator==(int)
* return: bool
*
* Overloaded equal to operator that takes in an int 
* and compares *this BigInt with it, returning true if
* *this == int, false otherwise.
*****************************************************/
bool BigInt::operator==(int n)
{
	return *this == BigInt(n);
}

/****************************************************
* operator!=(BigInt)
* return: bool
*
* Overloaded not equal to operator that takes in a BigInt 
* and compares *this BigInt with it, returning true if
* *this != BigInt, false otherwise.
*****************************************************/
bool BigInt::operator!=(BigInt n)
{
	return v != n.v;
}

/****************************************************
* operator!=(int)
* return: bool
*
* Overloaded not equal to operator that takes in an int 
* and compares *this BigInt with it, returning true if
* *this != int, false otherwise.
*****************************************************/
bool BigInt::operator!=(int n)
{
	return *this != BigInt(n);
}

/****************************************************
* operator<=(BigInt)
* return: bool
*
* Overloaded less than or equal to operator that takes
* in a BigInt and compares *this BigInt with it,
* returning true if *this <= BigInt, false otherwise.
*****************************************************/
bool BigInt::operator<=(BigInt n)
{
	if(v.size() < n.v.size())
	{
		return true;
	}
	else if(v.size() > n.v.size())
	{
		return false;
	}
	else
	{
		for(int i = v.size() - 1; i >= 0; i--)
		{
			if(v[i] > n.v[i])
			{
				return false;
			}
			else if(v[i] < n.v[i])
			{
				return true;
			}
		}
	}

	return true;
}

/****************************************************
* operator<=(int)
* return: bool
*
* Overloaded less than or equal to operator that takes
* in an int and compares *this BigInt with it,
* returning true if *this <= int, false otherwise.
*****************************************************/
bool BigInt::operator<=(int n)
{
	return *this <= BigInt(n);
}

/****************************************************
* operator>=(BigInt)
* return: bool
*
* Overloaded greater than or equal to operator that takes
* in a BigInt and compares *this BigInt with it,
* returning true if *this >= BigInt, false otherwise.
*****************************************************/
bool BigInt::operator>=(BigInt n)
{
	if(v.size() > n.v.size())
	{
		return true;
	}
	else if(v.size() < n.v.size())
	{
		return false;
	}
	else
	{
		for(int i = v.size() - 1; i >= 0; i--)
		{
			if(v[i] < n.v[i])
			{
				return false;
			}
			else if(v[i] > n.v[i])
			{
				return true;
			}
		}
	}

	return true;
}

/****************************************************
* operator>=(int)
* return: bool
*
* Overloaded greater than or equal to operator that takes
* in an int and compares *this BigInt with it,
* returning true if *this >= int, false otherwise.
*****************************************************/
bool BigInt::operator>=(int n)
{
	return *this >= BigInt(n);
}

/****************************************************
* to_str()
* return: string
*
* Converts value of BigInt into a string and returns it.
*****************************************************/
string BigInt::to_str()
{
	string num = "";
	for(int i = (int)v.size() - 1; i >= 0; i--)
	{
		num += to_string(v[i]);
	}
	
	return num;
}

/****************************************************
* operator<<(ostream, const BigInt&)
* return: ostream
*
* Overloaded output stream operator for BigInt class,
* allows for outputing exponential notation, returns
* ostream objects when finished. 
*****************************************************/
ostream & operator<<(ostream & os, const BigInt & n)
{
	int size = n.size() < EXP_NOTATION ? n.size() : EXP_NOTATION;
	for(int i = n.size() - 1; i >= n.size() - size; i--)
	{
		os << (int)n[i];
		if(i > (int)n.size() - 2 && size >= EXP_NOTATION)
		{
			os << ".";
		}
	}

	if(size >= EXP_NOTATION)
	{
		os << 'e' << (int)n.size() - 1;
	}
	return os;
}

/****************************************************
* findThreeNp1(BigInt, Statistics&, bool)
* return: void
*
* Recursive function used to calculate result of 
* Collatz conjecture. Takes in a BigInt to test, a
* reference to a Statistics struct to store data, and
* a bool value that tells function whether or not to
* print each calculation to screen. 
*****************************************************/
void findThreeNp1(BigInt num, Statistics& stats, bool printSteps)
{	
	if(printSteps)
	{
		cout << "->" << '(' << num << ')';
	}

	if(stats.max < num)
	{
		stats.max = num;
	}

	if(num == 1)
	{	
		cout << endl;
		stats.odd++;
		stats.steps++;
		return;
	}
	else if(num % 2 == 0)
	{	
		stats.even++;
		stats.steps++;
		findThreeNp1(num / 2, stats, printSteps);
	}
	else if(num % 2 == 1)
	{
		stats.odd++;
		stats.steps++;
		findThreeNp1(num * 3 + 1, stats, printSteps);
	}
	else
	{
		cout << "The one who programmed this is a dumdum\n";
	}
}

/****************************************************
* printStats(const Statistics&)
* return: void
*
* Recieves a const reference to a Statistics struct and
* formats and prints the data inside it.
*****************************************************/
void printStats(const Statistics& stats)
{
	cout << "Start: " << stats.start << endl
		 << "Steps: " << stats.steps << endl
		 << "Max:   " << stats.max   << endl
		 << "Odds:  " << stats.odd   << endl
		 << "Evens: " << stats.even  << endl;
}

/****************************************************
* operator+(int, BigInt)
* return: BigInt
*
* Overloaded addition operator that takes in an int and
* a BigInt, returning the sum as a BigInt.
*****************************************************/
BigInt operator+(int iNum, BigInt biNum)
{
	return iNum + biNum;
}

/****************************************************
* operator-(int, BigInt)
* return: BigInt
*
* Overloaded subtraction operator that takes in an int and
* a BigInt, returning the difference as a BigInt.
*****************************************************/
BigInt operator-(int iNum, BigInt biNum)
{
	return iNum - biNum;
}

/****************************************************
* operator*(int, BigInt)
* return: BigInt
*
* Overloaded multiplication operator that takes in an int and
* a BigInt, returning the product as a BigInt.
*****************************************************/
BigInt operator*(int iNum, BigInt biNum)
{
	return iNum * biNum;
}

/****************************************************
* operator/(int, BigInt)
* return: BigInt
*
* Overloaded division operator that takes in an int and
* a BigInt, returning the quotient as a BigInt.
*****************************************************/
BigInt operator/(int iNum, BigInt biNum)
{
	return iNum / biNum;
}
