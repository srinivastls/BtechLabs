#include<iostream>
#include<string>
#include<ctime>
using namespace std;

int random(int min, int max){
    static bool first = true;
    if (first) {
        srand( time(NULL) ); 
        first = false;
    }
    return min + rand() % (( max + 1 ) - min);
}
class bank{
      protected :
        int customer_id;
        int acc;
        string name;
        float amount;
      public:
      bank(){
            amount=500.15;
            acc=0;
        }
        void SetAmount(float amo){
            amount=amo;
        }
        void open_acc(int customer_id,string name){
            this->customer_id=customer_id;
            this->name=name;
        }
        void acc_type(int acc) {
            this->acc=acc;
        }
        void credit(float amo){
            amount+=amo;
        }
        int GetAccType() {
            return acc;
        }
        void debit(float amo){
            amount-=amo;
        }
        
        float GetAmount()
        {
            return amount;
        }
        
        int GetAccount()
        {
            return customer_id;
        }
        
        string GetName()
        {
            return name;
        }
};

class savings : public bank
{
    float interest_rate;
    
    public:
        
        savings()
        {
            interest_rate=5;
        }
        
        void update_rate(float rate)
        {
            interest_rate=rate;
        }
        
        float GetRate()
        {
            return interest_rate;
        }
};

class checking : public bank
{
    float charge_per_transact;
    
    public:
        
        checking()
        {
            charge_per_transact=50.0;
        }
        
        void update_charge(float charge_per_transact)
        {
            this->charge_per_transact=charge_per_transact;
        }
        
        float GetFee()
        {
            return charge_per_transact;
        }
};

int search_acc(int x,int c,int a[])
{
    for(int i=0;i<c;i++)
    {
        if(x==a[i])
        {
            return 1;
        }
    }
    
    return 0;
}

int main()
{
    int choice,ch,a=0,b=0,c=0,d=0,e=0,get,j,k;
    
    int acc[100];
    int accs[100];
    int accc[100];
    savings acc_s[100];
    checking acc_c[100];
    
    string name;
    int customer_id,acco;
    float cdt,dbt,rate,fee,amo;
    
    for(int i=0;i<100;i++){
        acc[i]=0;
    }
    
    for(int i=0;choice!=10;i++)
    {
        cout << " Enter "<<endl
             << " 1. To Open Account "<<endl
             << " 2. To Credit "<<endl
             << " 3. To Debit "<<endl
             << " 4. To Change / Update Interest Rate "<<endl
             << " 5. To Calculate Interest "<<endl
             << " 6. To Calculate and Update Interest "<<endl
             << " 7. To Change / Update Fee Amount "<<endl
             << " 8. To Print Checking Fee "<<endl
             << " 9. To Search Customer Details "<<endl
             << " 10. To Exit "<<endl;
             
        cin>>choice;
        
        switch(choice)
        {
            case 1:
                cout<<" Enter unique ID number "<<endl;
                cin>>customer_id;
                if(search_acc(customer_id,c,acc)==1){
                    cout<<" You are already our  customer for both type of accounts "<<endl;
                    if((search_acc(customer_id,c,acc)==1 && acc_s[j].GetAccType()!=0) && (search_acc(customer_id,c,acc)==1 && acc_c[k].GetAccType()!=0)) {
                            cout<<" you have both savings and checkings account "<<endl;
                            break;
                    }
                    if(search_acc(customer_id,c,acc)==1 && acc_s[j].GetAccType()!=0) {
                        acco =random(2000,3000);
                            cout<<"  Checkings  Account created successfully with below details: "<<endl;
                       
                                acc_c[k].acc_type(acco);
                                accc[e]=acco;
                                cout<<" Name : "<<acc_c[k].GetName()<<endl;
                        cout<<" Account type : Checkings"<<endl;
                        cout<< "Account num:"<<accc[e]<<endl;
                        cout<<" Account balance : "<<acc_c[k].GetAmount()<<endl;
                        cout<<" Fee per transaction : "<<acc_c[k].GetFee()<<endl;
                                e++;
                                break;
                        }
                        
                 if(search_acc(customer_id,c,acc)==1 && acc_c[k].GetAccType()!=0){
                     acco =random(1000,2000);
                            cout<<" your savings account created with following details:"<<endl;
                                acc_s[j].acc_type(acco);
                                accs[d]=acco;
                                cout<<" Name : "<<acc_s[j].GetName()<<endl;
                        cout<<" Account type : Savings"<<endl;
                        cout << "account num: "<< accs[d];
                        cout<<" Account balance : "<<acc_s[j].GetAmount()<<endl;
                        cout<<" Interest rate : "<<acc_s[j].GetRate()<<endl;
                                d++;
                                break;
                            }
                    }
            cout<<" Enter name "<<endl;
            getline(cin>>ws,name);
            
            acc[c]=customer_id;
            acc_s[a].open_acc(customer_id,name);
            acc_c[b].open_acc(customer_id,name);
            
            a++;
            b++;
            c++;
                
                cout<< " Enter "<<endl
                    << " 1. For savings account  "<<endl
                    << " 2. For checkings account "<<endl;
                cin>>ch;
                
                if(ch==1) {
                    if(customer_id>0){
                        for(j=0;j<a;j++) {
                            get=acc_s[j].GetAccount();
                             if(get==customer_id) {
                                break;
                            }
                        }
                        if(search_acc(customer_id,c,acc)==0 && acc_s[j].GetAccType()==0){
                            cout<<" Invalid ID "<<endl;
                            break;
                        }
                        acco =random(1000,2000);
                            cout<<" your savings account created with following details:"<<endl;
                                acc_s[j].acc_type(acco);
                                accs[d]=acco;
                                cout<<" Name : "<<acc_s[j].GetName()<<endl;
                        cout<<" Account type : Savings"<<endl;
                        cout << "account num: "<< accs[d]<< endl;
                        cout<<" Account balance : "<<acc_s[j].GetAmount()<<endl;
                        cout<<" Interest rate : "<<acc_s[j].GetRate()<<endl;
                                d++;
                            }
                        else{
                            cout<<" Invalid Input "<<endl;
                        }
                    }
                if(ch==2) {
                    cout<<" Enter unique ID number "<<endl;
                    cin>>customer_id;
                    
                    if(customer_id>0){
                        for(k=0;k<b;k++) {
                            get=acc_c[k].GetAccount();
                                
                            if(get==customer_id){
                                break;
                            }
                        }
                        if(search_acc(customer_id,c,acc)==0 && acc_c[k].GetAccType()==0)
                        {
                            cout<<" Invalid ID "<<endl;
                            break;
                        }
                            acco =random(2000,3000);
                            cout<<"  Checkings  Account created successfully with below details: "<<endl;
                       
                                acc_c[k].acc_type(acco);
                                accc[e]=acco;
                                cout<<" Name : "<<acc_c[k].GetName()<<endl;
                        cout<<" Account type : Checkings"<<endl;
                        cout<< "Account num:"<<accc[e]<<endl;
                        cout<<" Account balance : "<<acc_c[k].GetAmount()<<endl;
                        cout<<" Fee per transaction : "<<acc_c[k].GetFee()<<endl;
                                e++;
                        }
                        
                        else
                        {
                            cout<<" Invalid Input "<<endl;
                        }
                    }
            break;
            case 2:
                cout<<" Enter unique ID number "<<endl;
                cin>>customer_id;
                
                if(customer_id>0)
                {
                    if(search_acc(customer_id,c,acc)==0)
                    {
                        cout<<" Entered ID is invalid "<<endl;
                        
                    }
                        
                    else{
                        cout<< " Enter "<<endl
                            << " 1. For savings account "<<endl
                            << " 2. For checkings account "<<endl;
                        cin>>ch;
                        if(ch==1) {
                            for(j=0;j<a;j++) {
                                get=acc_s[j].GetAccount();
                                    
                                if(get==customer_id){
                                    break;
                                }
                            } 
                            cout<<" Enter the amount to be deposited "<<endl;
                            cin>>cdt;
                            if(acc_s[j].GetAccType()!=0) {
                                acc_s[j].credit(cdt);
                            }
                            else {
                                cout<<" Invalid Account "<<endl;
                            }
                        }
                        
                        if(ch==2)
                        {
                            for(k=0;k<b;j++)
                            {
                                get=acc_c[k].GetAccount();
                                    
                                if(get==customer_id)
                                {
                                    break;
                                }
                            }
                            cout<<" Enter the amount you want to credit "<<endl;
                            cin>>cdt;
                            if(acc_c[k].GetAccType()!=0){
                                acc_c[k].credit(cdt-acc_c[k].GetFee());
                            }
                            else{
                                cout<<" Invalid Account "<<endl;
                            }
                        }
                    }
                }
                
                else
                {
                    cout<<" Invalid Input "<<endl;
                }
            break;
            
            case 3:
                cout<<" Enter unique ID number "<<endl;
                cin>>customer_id;
                if(customer_id>0)
                {
                    if(search_acc(customer_id,c,acc)==0)
                    {
                        cout<<" Entered ID is invalid "<<endl;
                    }
                        
                    else
                    {
                        cout<< " Enter "<<endl
                            << " 1. For savings account "<<endl
                            << " 2. For checkings account "<<endl;
                        cin>>ch;
                        
                        if(ch==1) {
                            for(j=0;j<a;j++){
                                get=acc_s[j].GetAccount();  
                                if(get==customer_id){
                                    break;
                                }
                            }
                                
                            cout<<" Enter the amount to be debited "<<endl;
                            cin>>dbt;
                                
                            if(acc_s[j].GetAmount()>=dbt && acc_s[j].GetAccType()!=0) {
                                acc_s[j].debit(dbt);
                            }
                                
                            if(acc_s[j].GetAmount()<dbt){
                                cout<<" Insuffiecient balance "<<endl;
                            }
                            
                            if(acc_s[j].GetAccType()==0) {
                                cout<<" Invalid Account "<<endl;
                            }
                        }
                        
                        if(ch==2){
                            for(k=0;k<b;k++){
                                get=acc_c[k].GetAccount();
                                if(get==customer_id){
                                    break;
                                }
                            }  
                            cout<<" Enter the amount to be debit "<<endl;
                            cin>>dbt;
                            if(acc_c[k].GetAmount()>=dbt && acc_c[k].GetAccType()!=0) {
                                acc_c[k].debit(dbt+acc_c[k].GetFee());
                            }
                                
                            if(acc_c[k].GetAmount()<dbt) {
                                cout<<" Insufficient Balance "<<endl;
                            }
                            if(acc_c[k].GetAccType()==0) {
                                cout<<" Invalid Account "<<endl;
                            }
                        }
                    }
                }
                else{
                    cout<<" Invalid Input "<<endl;
                }
            break;
            
            case 4:
                cout<<" Current interest rate is  : "<<acc_s[0].GetRate()<<endl;
                
                cout<<" Enter the new interest rate "<<endl;
                cin>>rate;
                if(rate>0){
                    for(j=0;j<a;j++) {
                        acc_s[j].update_rate(rate);
                    }
                }
                else {
                    cout<<" Invalid input "<<endl;
                }
            break;
            case 5:
                cout<<" Enter unique ID number "<<endl;
                cin>>customer_id;
                if(customer_id>0){
                    if(search_acc(customer_id,c,acc)==0){
                        cout<<" Entered ID is invalid "<<endl;
                    }
                    else{
                        for(j=0;j<a;j++) {
                            get=acc_s[j].GetAccount();    
                            if(get==customer_id){
                                break;
                            }
                        }   
                        if(acc_s[j].GetAccType()!=0) {
                            amo=acc_s[j].GetAmount();
                            rate=acc_s[j].GetRate();   
                            cout<<" Account Balance is : "<<amo<<endl;
                            cout<<" Interest for that amount is : "<<(amo*rate)/100<<endl;
                        } 
                        else{
                            cout<<" Invalid Account "<<endl;
                        }
                    }
                }
                
                else{
                    cout<<" Invalid Input "<<endl;
                }
            break;
            
            case 6:
                cout<<" Enter unique ID number "<<endl;
                cin>>customer_id;
                
                if(customer_id>0)
                {
                    if(search_acc(customer_id,c,acc)==0)
                    {
                        cout<<" Entered ID is invalid "<<endl;
                    }
                    
                    else
                    {
                        for(j=0;j<a;j++) {
                            get=acc_s[j].GetAccount();
                                
                            if(get==customer_id) {
                                break;
                            }
                        }
                            
                        if(acc_s[j].GetAccType()!=0) {
                            amo=acc_s[j].GetAmount();
                            rate=acc_s[j].GetRate();
                            cdt=(amo*rate)/100;
                            
                            acc_s[j].credit(cdt);   
                            cout<<" Account Balance is : "<<amo<<endl;
                            cout<<" Interest for that amount is : "<<cdt<<endl;
                            cout<<" Account Balance after crediting interest : "<<acc_s[j].GetAmount()<<endl;
                        }
                        
                        else
                        {
                            cout<<" Invalid Account "<<endl;
                        }
                    }
                }
                
                else
                {
                    cout<<" Invalid Input "<<endl;
                }
            break;
            
            case 7:
                cout<<" Current fee per transaction is : "<<acc_c[0].GetFee()<<endl;
                cout<<" Enter the new fee amount "<<endl;
                cin>>fee;
                
                if(fee>0)
                {
                    for(k=0;k<b;k++)
                    {
                        acc_c[k].update_charge(fee);
                    }
                }
                
                else
                {
                    cout<<" Invalid input "<<endl;
                }
            break;
            
            case 8:
                cout<<" Enter unique ID number "<<endl;
                cin>>customer_id;
                
                if(customer_id>0)
                {
                    if(search_acc(customer_id,c,acc)==0)
                    {
                        cout<<" Entered ID is invalid "<<endl;
                    }
                    
                    else
                    {
                        for(k=0;k<b;k++)
                        {
                            get=acc_c[k].GetAccount();
                            
                            if(get==customer_id)
                            {
                                break;
                            }
                        }
                        
                        if(acc_c[k].GetAccType()!=0)
                        {
                            cout<<" Checking Fee per Transaction is : "<<acc_c[k].GetFee()<<endl;
                        }
                        
                        else
                        {
                            cout<<" Invalid Account "<<endl;
                        }
                    }
                }
                
                else
                {
                    cout<<" Invalid Input "<<endl;
                }
            break;
            
            case 9:
                cout<<" Enter unique ID number "<<endl;
                cin>>customer_id;
                if(search_acc(customer_id,c,acc)==0) {
                    cout<<" Entered ID is invalid "<<endl;
                }   
                else{
                    for(j=0;j<a;j++){
                        get=acc_s[j].GetAccount();  
                        if(get==customer_id){
                            break;
                        }
                    }
                    if(acc_s[j].GetAccType()!=0) {
                        cout<<" Name : "<<acc_s[j].GetName()<<endl;
                        cout<<" Account type : Savings"<<endl;
                        cout<< "Account num: "<< accs[j]<<endl;
                        cout<<" Account balance : "<<acc_s[j].GetAmount()<<endl;
                        cout<<" Interest rate : "<<acc_s[j].GetRate()<<endl;
                    }
                    for(k=0;k<b;k++){
                        get=acc_c[k].GetAccount();  
                        if(get==customer_id) {
                                break;
                        }
                    }
                    if(acc_c[k].GetAccType()!=0) {
                        cout<<" Name : "<<acc_c[k].GetName()<<endl;
                        cout<<" Account type : Checkings"<<endl;
                        cout<< "Account num: "<< accc[k]<<endl;
                        cout<<" Account balance : "<<acc_c[k].GetAmount()<<endl;
                        cout<<" Fee per transaction : "<<acc_c[k].GetFee()<<endl;
                    }
                }
            break;
        }   
    } 
    return 0;
}