#include <stdio.h>
#include <stdlib.h>

int main()
{
   char num;
   FILE *fptr;
   FILE *ptr;
    ptr = fopen("input.txt","r");
    fptr = fopen("output.txt","w");
    num=fgetc(ptr);
    while(num != EOF){
        fput(num,fptr);
        num=fgetc(ptr);
    }

    fclose(fptr);


  
   return 0;
}