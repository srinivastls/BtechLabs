#include<bits/stdc++.h>
using namespace std;
queue<char>q1,q2;
void insert(char c){
     q1.push(c);
     while(!q2.empty())
     {
        q1.push(q2.front());
        q2.pop();
     }
    queue <char> q=q2;
     q2=q1;
     q1=q;
}
char delet(){   
    try{
       if(q2.empty()){
         throw 0;
       }
       else{
           char x=q2.front();
           q2.pop();
           return x;
        } 
    }
    catch(int x){
        cout<<"stack underflow \n";
   } 
}

char Top(){
    return (q2.front());
}

int Operator(char o){
    if(o=='+' || o=='-'|| o=='*' || o=='/'|| o=='(' || o=='^'||o==')'){
        return 1;
    }
    else{
        return 0;
    }
}

int Precedence(char a){
    if(a=='^'){
        return 3;
    }
    else if(a=='*' || a=='/'){
        return 2;
    }
    else if(a=='+'|| a=='-'){
        return 1; 
    }
    else{
        return 0;
    }
}

string Check_Infix(string infix){
    int k,count=0;
    for(k=0;k<infix.length();k++){
        if(count%2==0){
            try{
                if(Operator(infix[k])){
                throw count;
                }
            }
            catch(...){
                cout<<"Enter a valid infix expression :\n";
                cin>>infix;
                infix=Check_Infix(infix);
            }
            count++;
        }
        else{
            try {
                if(!Operator(infix[k])){
                throw count;
                }
            }
            catch(...){
                cout<<"Enter a valid infix expression :\n";
                cin>>infix;
                infix=Check_Infix(infix);
            }
            count++;
        }  
    }
    return infix;
}
char* Infix_to_Postfix(string Infix){
    int d=Infix.size();
    insert('(');
    char*Postfix=(char*)malloc(sizeof(char)*d);
    int i=0;
    int j=0;
    while(Infix[i]!='\0'){
        if(!Operator(Infix[i])){
            Postfix[j]=Infix[i];
            j++;
            i++; 
        }
        else if(Precedence(Infix[i])>Precedence(Top())){
                insert(Infix[i]);
                i++;  
              }
        else{
            Postfix[j]=delet();
            j++;
        }
        }
        
        while(Top()!='('){
          Postfix[j]=delet();
          j++;
        }
     return Postfix;
}

int main()
{
    char x;
    int t=0;
    string infix,postfix;
    
    while(1)
    {
    cout<<"1.Get infix expresssion "<<"\n2.Print infix expression"<<"\n3.Print Postfix Expreesion"<<"\n4.Exit\n";
    cout<<"Enter here:";
    cin>>x;
    switch(x){
        case '1':
        cout<<"Enter the infix expression with out brackets  :\n";
        cin>>infix;
        t++;
        infix=Check_Infix(infix);
        break;
        case '2':
        if(t==0)
        cout << "Enter a infix expression and try again\n";
        else{
        cout<<"The infix expression is: \n";
        cout<<infix<<endl;
        }
        break;
        case '3':
        if(t==0)
        cout << "Enter a infix expression and try again\n";
        else{
        postfix=Infix_to_Postfix(infix);
        cout<<"The postfix expression is : \n";
        cout<<postfix<<endl;
        }
        break;
        case '4':
        exit (0);
        default:
        cout<<"Enter a valid input \n";
    }
    }
    return 0;
}