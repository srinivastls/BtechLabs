#include<iostream>
#include<cstdio>
using namespace std;
class list{
    private :
    int data;
    list * next;
    public:
    list* create(int k);
    int countlist(list *head);
    list* insert(list*head,int k);
    list* insert(list*head,list* newnode);
    list* insert(list*head,int data,int loc);
    list* delet(list*head,int loc);
    list* delet(list*head);
    void search(list* head,int k);
    void search(list* head,int p,int count);
    void  display(list* head);
};


list* list :: create (int t){
    list *temp,*p;
    list *head =NULL;
    
    p= new list();
    p->data=t;
    
    p->next =NULL;
    if(head == NULL)
    head =temp=p;
    else
    {
        temp->next =p;
        temp=p;
    }
    
    temp->next =head;
    return head;
}
int list :: countlist(list* head)
{
    int count =0;
    if(head== NULL)
    return 0;
    else{
    list* temp=head;
    while(temp->next != head)
    {
        temp=temp->next;
        count++;
    }
    return count+1;
    }
}
list* list :: insert(list* head,list *newnode){
   
    printf("enter the data:");
   scanf("%d",&newnode->data);
  if (head == NULL)
  {
      head =newnode;
      return head;
  }
    
    list *ptr =head;
    while(ptr->next != head)
    {
        ptr =ptr->next;
    }
    ptr->next =newnode;
    newnode->next =head;
   head =newnode;
    
    return head;
}
list* list :: insert(list* head,int t){
   
  list c1;
  if (head == NULL)
  {
      list *t1=create(t);
    t1->data=t;
    head =t1;
     return head;
  }
    list *ptr =head;
    while(ptr->next != head)
    {
        ptr =ptr->next;
    }
    list *t1=create(t);
    t1->data=t;
    ptr->next =t1;
    t1->next =head;
    return head;
}
list* list :: insert(list* head,int t,int loc)
{
    if (loc == 1)
    {
       head= insert(head,create(t));
        return head;
        
    }
    
    list * temp =head;
    while(loc-2>0)
    {
        temp=temp->next;
        loc--;
    }
    list* t1 =create(t);
    t1->next = temp->next;
    temp->next =t1;
    
    return head;
}
void list :: display(list* head){
    if(head == NULL){
        printf("list is empty\n");
        return;
    }
    list *temp=head;
    printf("the data present is/are:\n");
    while(temp->next != head){
        printf(" %d\t",temp->data);
        temp=temp->next;
        
    }
    printf("%d\n",temp->data);
    
    printf("the no of elements is :%d\n",countlist(head));
}
list* list :: delet(list* head,int loc)
{
    if (head==NULL)
        {
            printf("list is empty");
            return head;
        }
   
    if (loc == 1)
    { 
        head=delet(head);
        return head;
    }
    if (countlist(head) ==1 && loc ==1)
        {
            head=NULL;
            return head;
        }
    if (loc > countlist(head) || loc <1){
       printf("given location is out of range\n");
       
    }
    else if (loc== countlist(head)){
      
        list * temp =head;
    while(loc-2>0)
    {
        temp=temp->next;
        loc--;
    }
    temp->next= head;
   
    return head;
    }
    else{
    list * temp =head;
    while(loc-1>0)
    {
        temp=temp->next;
        loc--;
    }
    temp->next= temp->next->next;
     return head;
    }
    return head;
    
   
}

list* list :: delet(list* head)
{
        list * temp=head;
        if (head==NULL)
        {
            printf("list is empty");
            return head;
        }
        if (countlist(head) ==1)
        {
            head=NULL;
            return head;
        }
         while(temp->next != head)
        temp=temp->next;
        head=head->next;
        temp->next=head;
        return head;
}
void  list :: search(list* head,int loc,int count)
{
   int r=loc;
   if (count ==0){
       printf("the location not found !the list is empty\n");
   }
   else{
    if (loc == 1 && count != 0)
    { 
        printf("the data in the location %d is: %d\n ",loc,head->data);
      
    }
    else if (loc > count || loc <1){
       printf("given location is out of range\n");
       
    }
    else{
    list * temp =head;
    while(loc-1>0){
        temp=temp->next;
        loc--;
    }
    
    printf("the data in the location %d is: %d\n ",r,temp->data);
    }
   }
}
void  list :: search(list* head,int k)
{
   
  int loc =0;
    if(head == NULL){
        printf("the element not found ! list is empty\n");
        return;
    }
    if(head->data == k){
       loc++;
    printf("the %d is present in location: %d\n",k,1);
    return;
    }
    else{
    list *temp=head;
    while(temp->next != head){
        loc++;
        if(temp->data == k){
        printf("the data  %d is in the location:%d\n",temp->data,loc);
        loc--;
        break;
        }
        if(temp->next->data == k){
        printf("the data  %d is in the location:%d\n",temp->next->data,loc+1);
        loc--;
        break;
        }
        temp=temp->next; 
    }
    loc++;
    }
    if(loc == countlist(head))
    {
        printf("The data not found in the list\n");
    }
}
int main()
{
    list *head=NULL;
    list c;
   int choice,k;
   
   
   while(1){
       printf("Enter:\n1.Insert\n2.Delete \n3.Search \n4.Display \n5.Exit\n");
       scanf("%d",&choice);
      switch(choice){
           case 1:
            printf("Enter:\n1.To Insert at beginning\n2.To Insert at any location\n3.To insert at end\n");
            scanf("%d",&k);
            if(k==1){
                int t;
                head=c.insert(head,c.create(t));
            }
            else if(k==2){
                int loc,t;
                printf("Enter the location to insert:");
                scanf("%d",&loc);
                if(loc==1)
                head=c.insert(head,t,loc);
                else if (loc >c.countlist(head)+1 || loc<1)
                printf("location is out of range\n");
                else{
                printf("Enter the data to insert:");
                scanf("%d",&t);
                head=c.insert(head,t,loc);
                }
            }
            else if (k==3){
                int t;
                printf("Enter the data to insert:");
                scanf("%d",&t);
                head=c.insert(head,t);
            }
            else
            printf("Enter valid input\n");
            break;
           case 2:
           printf("Enter:\n1.To Delete at beginning\n2.To Delete at any location\n3.To Delete at end\n");
            scanf("%d",&k);  
            if(k==1)
            head=c.delet(head);
            else if(k==2){
                int loc,t;
                printf("Enter the location to delete:");
                scanf("%d",&loc);
                head=c.delet(head,loc);
            }
            else if(k==3)
            head=c.delet(head,c.countlist(head));
            else
            printf("Enter valid input\n");
            break;
            case 3:
            printf("Enter :\n1.To find data in the location\n 2.To find location of the data\n");
            scanf("%d",&k);
            if (k==1){
                int loc;
                printf("Enter the location to find the data:");
                scanf("%d",&loc);
                c.search(head,loc,c.countlist(head));
                
            }
            else if(k==2){
                int t;
                printf("Enter the data to find the location:");
                scanf("%d",&t);
                c.search(head,t);
            }
            else
            printf("Enter valid input\n");
            break;
            case 4:
            c.display(head);
            break;
            case 5:
            exit (0);
            default:
            printf("Enter valid input\n");
            
       }
      
   }
   return 0; 
   
}
