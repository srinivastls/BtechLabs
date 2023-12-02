#include<bits/stdc++.h>
using namespace std;
string a_check(string s1,string s2,string s3,string s4){
    while(s4==s1 || s4==s2 || s4==s3){
        cout<<"\n Course Assigned cannot be same as the given course";
        cout<<"Try again with a new course\n ";
        cout<<"Enter:";
        cin>>s4;
    }
    if(s4!=s1 && s4!=s2 && s4!=s3)
        return s4;
}
string c3_check(string s1,string s2,string s4){
    while(s4==s1 || s4==s2 ){
        cout<<"\n Course already taken!!!\n";
        cout<<"Try again with a new course\n ";
        cout<<"Enter:";
        cin>>s4;
        
    }
    if(s4!=s1 && s4!=s2 )
    return s4;
}
string p_check(string s1,string s2){
    while(s1==s2){
        cout<<"Course already taken!!!\n";
        cout<<"Try again with a new course\n";
        cout<<"Enter here :";
        cin>>s2;
    }
    if(s2!=s1)
        return s2;
}
class student
{
    protected:
        string name;
        string roll_number;
    public:
        virtual void display()=0;
        
        string GetRoll(){
            return roll_number;
        }
};

class pg_student : virtual public student
{
    protected:
        string course1;
        string course2;
        string course3;
    public:
        void display(){
            cout<<" Roll Number : "<<roll_number<<endl;
            cout<<" Name : "<<name<<endl;
            cout<<" Course 1 : "<<course1<<endl;
            cout<<" Course 2 : "<<course2<<endl;
            cout<<" Course 3 : "<<course3<<endl;
            cout<<endl;
        }
};

class research_student : virtual public student
{
    protected:
        string course;
        string research_area;
    public:
        void display(){
            cout<<" Roll Number : "<<roll_number<<endl;
            cout<<" Name : "<<name<<endl;
            cout<<" Course 1 : "<<course<<endl;
            cout<<" Research Area : "<<research_area<<endl;
            cout<< endl;
        }
};

class TA : public pg_student,research_student
{
    protected:
        string course_assigned;
        string role;
        
    public:
        void SetDetails(string n,string rn,string r,string ca,string c1,string c2,string c3){
            name=n;
            roll_number=rn;
            role=r;
            course_assigned=ca;
            course1=c1;
            course2=c2;
            course3=c3;
        }
        void SetDetails(string n,string rn,string r,string ca,string c,string ra){
            name=n;
            roll_number=rn;
            role=r;
            course_assigned=ca;
            course=c;
            research_area=ra;
        }
        
        void display(){
            cout<< "*** Student Details ***\n";
            cout<<" Course Assigned : "<<course_assigned<<endl;
            
            if(role=="pg") {
                cout<<" Role : PG Student "<<endl;
                pg_student :: display();
            }
            
            if(role=="research"){
                cout<<" Role : Research Student "<<endl;
                research_student :: display();
            }
        }
};

int main()
{
    int choice,ch,flag=0;
    string name,roll_number,course1,course2,course3,course_assigned,course,research_area;
    string Roll;
    
    TA ta[150];
    int count=0,a;
    
    while(1){
        cout << " Enter "<<endl
             << " 1. Set Details "<<endl
             << " 2. Display "<<endl
             << " 3. Exit "<<endl;
        cin>>choice;
        switch(choice){
            case 1:
              flag=0;
             cout<<" Enter Roll Number "<<endl;
                getline(cin>>ws,roll_number);
                 for(int i=0;i<count;i++)
                {
                    Roll=ta[i].GetRoll();
                    
                    if(Roll==roll_number)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag ==1 ){
                    cout<< "The roll number already exists !! try a unique roll number\n";
                    break;
                }
                cout<<" Enter name "<<endl;
                getline(cin>>ws,name);
               
                cout<<" Enter role "<<endl
                    <<" 1. PG student "<<endl
                    <<" 2. research student "<<endl;
                cin>>ch;
                
                if(ch==1)
                {
                    cout<<" Enter Course 1 "<<endl;
                    getline(cin>>ws,course1);
                    cout<<" Enter Course 2 "<<endl;
                    getline(cin>>ws,course2);
                   course2= p_check(course1,course2);
                    cout<<" Enter Course 3 "<<endl;
                    getline(cin>>ws,course3);
                    course3= c3_check(course1,course2,course3);
                    cout<<" Enter the  Course Assigned "<<endl;
                    getline(cin>>ws,course_assigned);
                    course_assigned=a_check(course1,course2,course3,course_assigned);
                    ta[count].SetDetails(name,roll_number,"pg",course_assigned,course1,course2,course3);
                    count++;
                    
                }
                else if(ch==2){
                    cout<<" Enter Course "<<endl;
                    getline(cin>>ws,course);
                    cout<<" Enter Research Area "<<endl;
                    getline(cin>>ws,research_area);
                      cout<<" Enter Course Assigned "<<endl;
                    getline(cin>>ws,course_assigned);
                   course_assigned= p_check(course,course_assigned) ;
                    ta[count].SetDetails(name,roll_number,"research",course_assigned,course,research_area);
                     count++;
                }
                else
                cout<< "Enter the correct role and try again\n";
                
            break;
            case 2:
             if(count==0){
                cout << "No data present\n";
                break;
                }
                cout<< "1.To view individual student data using their roll numbers \n 2.To view all student data\n";
                cin >> a;
                if(a==1){
                cout<<" Enter the roll number "<<endl;
                getline(cin>>ws,roll_number);
               
                for(int i=0;i<count;i++)
                {
                    Roll=ta[i].GetRoll();
                    
                    if(Roll==roll_number)
                    {
                        flag=1;
                        ta[i].display();
                        break;
                    }
                }
                if(flag==0)
                    cout<<" Invalid Roll Number "<<endl;
                }
               else  if(a==2){
                   for(int i=0;i<count;i++)
                        ta[i].display();
                }
                else
                cout<< "Enter the correct input and try again\n";
            break;
            case 3:
            exit(0);
            default:
            cout<< "Enter the correct input\n";
        }
    }
    return 0;
}