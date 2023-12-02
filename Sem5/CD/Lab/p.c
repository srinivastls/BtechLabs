#include<stdio.h>


int main(){
    FILE *f,*f1;
    f=fopen("result.txt","r");
    char t;
    f1=fopen("r.txt","w");
    t=fgetc(f);
    while(t != EOF){
        fputc(t,f1);
        printf("%c",t);
        t=fgetc(f);
        
    }
    fclose(f);
    fclose(f1);
    f1=fopen("r.txt","r");
    char k[100];
    fgets(k,100,f1);
    while(k != EOF){
        
        printf("%s",);
       t= fgetc(f1);
        
    }


    fclose(f);
    return 0;
}