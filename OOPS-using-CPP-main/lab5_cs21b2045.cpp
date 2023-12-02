#include<bits/stdc++.h>
using namespace std;

class coordinates{
private:
float xnum;
float ynum;
public:
coordinates(){
    xnum =0.0;
    ynum=0.0;
}
coordinates(float xnum, float ynum){
	this->xnum = xnum;
	this->ynum = ynum;
}
coordinates operator ~(){
        xnum = float(abs(xnum));
        ynum = float(abs(ynum));
    }
float  operator- (coordinates c2){
	coordinates c3;
	c3.xnum = (this->xnum-c2.xnum)*(this->xnum-c2.xnum);
	c3.ynum =( this->ynum - c2.ynum)*( this->ynum - c2.ynum);
	return c3.xnum + c3.ynum;
}
friend ostream & operator << (ostream &out, const coordinates &c);
friend istream & operator >> (istream &in, coordinates &c);
bool Right_angled (coordinates c1,coordinates c2,coordinates c3);
};

ostream & operator << (ostream &out, const coordinates &c)
{
	out <<"("<< c.xnum;
	out << "  " << c.ynum<< ")\n";
	return out;
}

istream & operator >> (istream &in, coordinates &c)
{
	cout << "Enter X  coordinate ";
	in >> c.xnum;
	cout << "Enter Y coordinate ";
	in >> c.ynum;
	return in;
}
bool coordinates :: Right_angled(coordinates c1,coordinates c2,coordinates c3) 
{
    if (((c1-c2)+(c2-c3)) ==(c3-c1) && c1-c2 != 0 )
    return true;
    else
    return false;
}
int main() {
    coordinates c1,c2,c3; 
    int choice ,k,l;
    while(1)
   {
      cout<<endl<<"1 to Set Point\n2 to Display point\n3 to Display Length\n4 to Check Right Triangle\n5 to EXIT:\n ";
      cin>>choice;
      switch(choice)
      {
        case 1:
           cout << "\n 1.to set first  point 2.to set second point 3.to set third point\n";
           cin >> k;
           if(k==1){
          cin >> c1;
           ~c1;
           }
           if(k==2){
           cin >> c2;
           ~c2;
           }
           if(k==3){
           cin >> c3;
            ~c3;
           }
           if (k>3 || k<1)
            cout << "Enter the correct input\n";

           break;
        case 2:
           cout<<"Enter which point to display:";
           cin>>l;
           if(l==1)
           cout << c1;
           if(l==2)
            cout << c2;
           if(l==3)
            cout << c3;
            if (l>3 || l<1)
            cout << "Enter the correct input\n";
           break;
        case 3:
        cout<<"Enter distance between which  points to display:1)1 and 2     2)2 and 3 3) 3 and 1:";
           cin>>l;
           if(l==1)
           cout<<"Length between points 1 and 2: " << sqrt( c1-c2)<<endl;
           if (l==2)
           cout <<"Length between points 2 and 3: " <<sqrt( c2-c3)<< endl;
           if (l==3)
           cout <<"Length between points 3 and 1: " <<sqrt( c3-c1)<< endl;
           if (l>3 || l<1)
            cout << "Enter the correct input\n";
           break;
        case 4:
           if (c1.Right_angled(c1,c2,c3) || c1.Right_angled(c2,c3,c1) || c1.Right_angled(c3,c1,c2))
            cout << " Given points form a right angled Triangle \n";
            else
            cout << " Given points not  form a right angled Triangle \n";
           break;
        case 5:
           exit(0);      
      }
   }
	return 0;
}