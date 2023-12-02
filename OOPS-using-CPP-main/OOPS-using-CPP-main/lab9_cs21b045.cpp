#include<bits/stdc++.h>

using namespace std;

class Node
{
    public:
    char data;
    Node* right;
};


class Queue
{
    public:
    Node* front =NULL;
    Node* rear = NULL;

    void Enqueue(char c){

        Node *n=new Node;
        n->data=c;
        n->right=NULL;
       
        if(front==NULL)
        {
            front=n;
            rear=n;
        }
        else
        {
           rear->right=n;
           rear=n;
        }
    }

    char Dequeue() {
        try{
           if(front==NULL){
              throw front;
           }
           else{
            char x=front->data;
            front=front->right;
            return x;
           }
        }
        catch(Node* front){
            cout<<"The given linklist is empty\n";
        }  
    }

    int Empty() {
        if(front==NULL) {
            return 1;
        }
        return 0;
    }
};

Queue q1,q2;

void insert(char c){
     q1.Enqueue(c);
     while(!q2.Empty())
     {
        q1.Enqueue(q2.Dequeue());
     }
     Queue q=q2;
     q2=q1;
     q1=q;
}

char pop()
{   
    try{
       if(q2.Empty()){
         throw 0;
       }
       else{
           char x=q2.Dequeue();
           return x;
        } 
    }
    catch(int x){
        cout<<"stack underflow \n";
   } 
}

char Top(){
    return (q2.front)->data;
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

string Check_Infix(string infix)
{
    int k;
    for(k=0;k<infix.length();k++)
    {
        if(k%2==0)
        {
            try 
            {
                if(Operator(infix[k])){
                throw k;
                }
            }
            catch(...)
            {
                
                cout<<"Enter a valid infix expression :\n";
                cin>>infix;
                infix=Check_Infix(infix);
            }
        }
        else{
            try {
                if(!Operator(infix[k])){
                throw k;
                }
            }
            catch(...)
            {
                cout<<"Enter a valid infix expression :\n";
                cin>>infix;
                infix=Check_Infix(infix);
            }
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
            Postfix[j]=pop();
            j++;
        }
        }
        
        while(Top()!='(')
        {
          Postfix[j]=pop();
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