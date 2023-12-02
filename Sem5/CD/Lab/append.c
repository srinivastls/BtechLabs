#include <stdio.h>
#include <stdlib.h>

int main()
{
   char num[100];
   FILE *fptr;

   fptr = fopen("output.txt","a");
    scanf("%s",&num);
    fputs(num,fptr);

    fclose(fptr);


  
   return 0;
}