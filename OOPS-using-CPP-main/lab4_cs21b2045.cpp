#include<iostream>
using namespace std;

class list{
   private:
    int data;
    list *next,*back;
    public:
    list* insert(list* head,int k);
    list* deletenode(list* head,int a);
    void display(list* head);
    list* append(list* head,int t);
    list* merge(list* head1,list* head2);
};

list *head1=NULL,*head2=NULL;

list* list:: insert(list* head,int k){
    list *ptr=head;
    list *node=new list();
    node->data=k;
    while(1){
        if(ptr==NULL){
            head=node;
            break;
        }
        else if(ptr->data>k){
            if(ptr==head){
            node->next=head;
            head->back=node;
            head=node;
            }
            else{
            (ptr->back)->next=node;
            node->back=(ptr->back)->next;
            node->next=ptr;
            ptr->back=node;
            }
            break;
        }
        else if(ptr->next==NULL){
            ptr->next=node;
            node->back=ptr;
            break;
        }
        else if(ptr->data<k){
            ptr=ptr->next;
        }
    }
    return(head);
}

list* list:: deletenode(list* head,int a)
{
    if(head==NULL){
        cout<<"List is Empty"<<endl;
        return(NULL);
    }
    int k,t;
    cout<<"Enter the position of the  element which you want to delete(starts with 1):";
    cin>>t;
    if (t>a)
        cout << "Position doesnot exists\n";
    else{
        list *temp=head;
        for(int i=0;i<a;i++){
           if(i==t-1)
            k=temp->data;
           else
            temp=temp->next;
        }
        list *parent=NULL;
        list *ptr=head;
       while(1){
        if(ptr->data<k){
            parent=ptr;
            ptr=ptr->next;
        }
        else{ 
        if(ptr->data==k){
            if(ptr==head){
                list *ptr=head; 
                head=head->next;
                delete(ptr);
            }
            else{
               parent->next=ptr->next;
               if(ptr->next!=NULL){
               (ptr->next)->back=parent;
               }
               delete(ptr);
            }
            break;
        }
        else{
            cout<<"Number is not present in the list";
            break;
        }
        }
    }
    }
    return(head);
}

void list :: display(list* head)
{
    if(head==NULL)
        cout<<"List is Empty"<<endl;
    else{
        list *temp=head;
       while(temp!=NULL){
        cout<<temp->data<<"      ";
        temp=temp->next;
       }
    cout<<endl;
    }
}
list* list :: append(list *head3,int data){
    list *new_node=new list();
    list  *last ;
    new_node->data=data;
    new_node->next=NULL;
    if (head3 == NULL){
		new_node->back = NULL;
		head3=last = new_node;		
	}
    else{
    new_node->back=last;
    last->next=new_node;
    last=new_node;
    }
    return head3;
}

list* list :: merge(list* head1,list* head2)
{
    int count=0;
    list *ptr1=head2;
    list *ptr2=head1;
   list *head3=NULL;
    while(ptr1!=NULL && ptr2 != NULL){
         count++;
        if(ptr1->data >=ptr2->data){
           head3=append(head3,ptr2->data);
           ptr2=ptr2->next;
        }
        else{
            head3=append(head3,ptr1->data);
            ptr1 =ptr1->next;
        }    
    }
    if(ptr1!=NULL){
        while(ptr1 !=NULL){
                count++;
                head3 =append(head3,ptr1->data);
                ptr1=ptr1->next;
            }
    }
    if(ptr2!=NULL){
        while(ptr2 !=NULL){
            count++;
                head3 =append(head3,ptr2->data);
                ptr2=ptr2->next;
            }
    }
    cout << "Elements in the list 1:";
    display(head1);
    cout<<endl;
    cout << "Elements in the list 2:";
    display(head2);
    cout <<"Computational time is :"<< count<< endl;
    return(head3);
}

int main()
{
    int m=0,n=0;   
   list  *head3=NULL;
    list a1; 
    while(1)
    {
        int choice;
        cout<<"Enter: 1. Insert;    2. Delete;    3. Display;   4. Merge;   5. Exit\n";
        cin>>choice;
        switch(choice)
        {
            case 1:
            int k,l;
             cout<<"Which list do you want to insert   1.List1   2.List2  :";
             cin>>k;
             if(k==1){
                m++;
                cout<<"Enter the number:";
                cin>>l;
                head1=a1.insert(head1,l);
             }
             else if(k==2){
                cout<<"Enter the number:";
                cin>>l;
                n++;
                head2=a1.insert(head2,l);
             }
             else
             cout << "enter the correct option\n";
             break;
            case 2:
             cout<<"Which list do you want to delete  1.List1   2.List2   :";
             cin>>k;
             if(k==1){
             head1=a1.deletenode(head1,m);
             }
             else if (k==2){
             head2=a1.deletenode(head2,n);
             }
             else
             cout << "enter the correct option:";
             m=m-1;
             break;
            case 3:
             cout<<"Which list do you want to Display  1.List1   2.List2:";
             cin>>k;
             if(k==1){
                cout << "Elements in the list 1:";
                a1.display(head1);
             }
             else if(k==2){
                cout << "Elements in the list 2:";
                a1.display(head2);
             }
             else
             cout << "Enter correct option\n";
             break;
             case 4:
             head3=a1.merge(head1,head2);
             cout << "Elements in the list 3/merged list:";
             a1.display(head3);
             break;
            case 5:
             exit(0);
            default:
                  cout<<"Enter the correct option\n";
            break;
        }
    }
   return 0;
}