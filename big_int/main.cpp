#include <iostream>
#include "BigInt.cpp"
using namespace std;

int main()
{
	try
	{
		string input = "";
		
		cout << "Multiply \n First BigInt: ";
		cin >> input;
		BigInt bi1(input);
		cout << "Second BigInt: ";
		cin >> input;
		BigInt bi2(input);
		cout << (bi1 * bi2).to_str();
		
		
	}
	catch(const char* e)
	{
		cout << e << endl;
	}
	 
	 return 0;
}
