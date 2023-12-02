#include <stdio.h>
#include <stdlib.h>

int main()
{
   char num;
   FILE *fptr;

   if ((fptr = fopen("input.txt","r")) == NULL){
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   }
    num=fgetc(fptr);
    while(num != EOF){
        printf("%c",num);
        num=fgetc(fptr);
    }

    fclose(fptr);


  
   return 0;
}