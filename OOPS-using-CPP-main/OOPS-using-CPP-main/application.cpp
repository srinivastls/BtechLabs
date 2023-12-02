/* OOPS LAB ASSIGNMENT 1 
    26/07/2022
	T.LAKSHMI SRINIVAS
	CS21B2045  */

#include<iostream>
#include"stack"
using namespace std;

int main()
{
	Stack stack1,stack2;
	int choice,element,digit;
	while(1)
	{
		cout << " MENU DRIVE PROGRAMMING\n";
		cout << "1. Get Number\t2. Digit to Text\t3. Reverse\t4. Palindrom Check\t5. Exit\n";
		cin >> choice;
		switch(choice)
		{
			case 1 : cout << "Enter a number(max 5 digits) : ";
					 cin >> element;
					 while(1)
					 {
						if(stack1.isempty())
							break;
						else
							stack1.pop();
					 }
					 while(element>0 && element<100000)
					 {
					 	digit=element%10;
						stack1.push(digit);
						element=element/10;
					 }
					 if (element > 99999){
					 cout << "wrong number entered\n Try again\n ";
					 }
					 break;

			case 2 : stack1.digittotext();
					 cout << endl;
					 break;
			case 3 : stack1.reverse();
		 			 cout << endl;
					 break;
			case 4 : stack1.palindrome();
					 break;
			case 5 : exit(0);
			default : cout << "Invalid Choice\n"; 
					  break;
		}
	}
	return 0;
}
