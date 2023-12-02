/*    OOPS LAB ASSIGNMENT 2
     01/08/2022
	 T.Lakshmi srinivas
	 CS21B2045
*/
#include<bits/stdc++.h>
using namespace std;

class TIME
{
	private :
		int hours,Minutes,Seconds;
	public :
		TIME()
		{
			hours=0;
			Minutes=0;
			Seconds=0;
		}
		TIME(int h,int m,int s)
		{
			hours=h;
			Minutes=m;
			Seconds=s;
		}
		~TIME()
		{
			
		}
		void setTIME(int hour,int mi,int se)
		{
			hours=hour;
			Minutes=mi;
			Seconds=se;
		}
		int gethour()
		{
			return hours;
		}
		int getMinutes()
		{
			return Minutes;
		}
		int getSeconds()
		{
			return Seconds;
		}
};

void stdTIME(TIME a)
{
	int hours=a.gethour();
	int Minutes=a.getMinutes();
	int Seconds=a.getSeconds();
	if(hours>=0 && hours<12)
	{
		cout << "Standard TIME is : " << endl;
		cout << "Hours : Minutes : Seconds = " << hours << " :: " << Minutes << " :: " << Seconds << " AM" <<endl;
	}
    else if(hours == 12)
    {
        cout << "Standard TIME is : " << endl;
		cout << "Hours : Minutes : Seconds = " << hours<< " :: " << Minutes << " :: " << Seconds << " PM" << endl;
    }
	else if(hours>12 && hours<=24)
	{
		cout << "Standard TIME is : " << endl;
		cout << "Hours : Minutes : Seconds = " << hours-12 << " :: " << Minutes << " :: " << Seconds << " PM" << endl;
	}
}

void uniTIME(TIME a)
{
	cout << "Universal TIME : " << endl;
	int hour=a.gethour();
	int Minutes=a.getMinutes();
	int Seconds=a.getSeconds();
	cout << "Hours :: Minutes :: Seconds : " << hour << " : " << Minutes << " : " << Seconds << endl;
}

void ist(TIME a)
{
	cout << "Indian Standard TIME is : " << endl;
	int hour=a.gethour();
	int Minutes=a.getMinutes();
	int Seconds=a.getSeconds();
	int k=hour+5;
	if(Minutes>29)
	{
	if(k+1<24)
	{
		cout << "Hours : Minutes : Seconds = " << k+1 << " :: " << Minutes-30 << " :: " << Seconds << endl;
	}
	else if(k+1>=24)
	{
		cout << "Hours : Minutes : Seconds = " << k-23 << " :: " << Minutes-30 << " :: " << Seconds << "\n \n";
		
	}
	}
	else
	{
	if(k<24)
	{
		cout << "Hours : Minutes: Seconds = " << k << " :: " << Minutes+30 << " :: " << Seconds << endl;
	}
	else if(k>=24)
	{
		cout << "Hours : Minutes : Seconds = " << k-24 << " :: " << Minutes+30 << " :: " << Seconds << endl;
	}
	}
}

void pst(TIME a)
{
	cout << "Pacific Standard TIME is : " << endl;
	int hours=a.gethour();
	int Minutes=a.getMinutes();
	int Seconds=a.getSeconds();
	if(hours+1>=0 && hours+1<8)
	{
		if(hours == 0)
            cout << "Hours : Minutes : Seconds = " << 4 << " :: " << Minutes << " :: " << Seconds << " PM" << endl;
        else
          cout << "Hours : Minutes : Seconds = " << 8-hours << " :: " << Minutes << " :: " << Seconds << " PM" << endl;
	}
	else if(hours+1>=8 && hours+1<20)
	{
		cout << "Hours : Minutes : Seconds = " << hours-8 << " :: " << Minutes << " :: " << Seconds << " AM" << endl;
		cout << endl;
	}
	else if(hours-7==12)
	{
		cout << "Hours : Minutes : Seconds = " << hours-8 << " :: " << Minutes << " :: " << Seconds << " PM" << endl;
		cout << endl;
	}
	else if(hours+1>20 && hours+1<=24)
	{
		cout << "Hours : Minutes : Seconds = " << hours-20 << " :: " << Minutes << " :: " << Seconds << " PM" << endl;
		cout << endl;
	}
	}


void DisplayMenu()
{
	cout << "Enter 1 to Set Time" << endl;
	cout << "Enter 2 to print Standard Time" << endl;
	cout << "Enter 3 to print Universal Time" << endl;
	cout << "Enter 4 to print Indian Standard Time" << endl;
	cout << "Enter 5 to print Pacific Standard Time" << endl;
	cout << "Enter 6 to exit" << endl;
    cout << "\n \n";
}

int main()
{
	int ch1,flag3=1,ch2,ch3,flag1=1,flag2=1;
	TIME b;
	TIME a;
	while(flag1)
	{
		cout << "1. Create Time \t 2. Create and Set Time" << endl;
		cout << "Enter your choice : ";
		cin >> ch1;
		switch(ch1)
		{
			case 1 : flag2=1;
					 while(flag2!=6)
					 {
					 	 DisplayMenu();
					 	 cout << "Enter your choice : ";
					 	 cin >> ch2;
					 	 switch(ch2)
						 {
							 case 1 : a.setTIME(0,0,0);
							          break;
							 case 2 : stdTIME(b);
					 				  break;
							 case 3 : uniTIME(b);
					 				  break;
							 case 4 : ist(b);
									  break;
							 case 5 : pst(b);
									  break;
							 case 6 : return 0;
						}
						cout << "Do you want to continue (6 for exit) : ";
						cin >> flag2;
					 }
					 break;
			case 2 : flag3=1;
					 while(flag3!=6)
					 {
					 	 DisplayMenu();
					 	 cout << "Enter your choice : ";
					 	 cin >> ch3;
					 	 switch(ch3)
						 {
							 case 1 : int hour,Seconds,Minutes;
					 				  cout << "Enter hours : " << endl;
					 				  cin >> hour;
					 				  cout << "Enter Minutes : " << endl;
					 				  cin >> Minutes;
					 				  cout << "Enter Seconds : " << endl;
									  cin >> Seconds;
									  if(hour<0 && hour>24 && Minutes<0 && Minutes>60 && Seconds<0 && Seconds>60)
					 				  {
						 				  cout << "Invalid Input" << endl;
						 				  return 0;
					 				  }
					 				  a.setTIME(hour,Minutes,Seconds);
					 				  break;
							 case 2 : stdTIME(a);
					 				  break;
							 case 3 : uniTIME(a);
					 				  break;
							 case 4 : ist(a);
									  break;
							 case 5 : pst(a);
									  break;
							 case 6 : return 0;
					 	 }
					 	 cout << "Do you want to continue (6 for exit) : ";
					 	 cin >> flag3;
					 }
					 break;
			case 3 : return 0;
		}
		cout << "Do you want to continue (0 or 1) : ";
		cin >> flag1;
	}
}