#include <stdio.h>
void ganmang(int a[],int b[]){
    for(int i=0;i<40;i++){
        a[i]=b[i];
    }
}
void xuatmang(int a[]){
    int b=39;
    for(int i=0;i<39;i++){
        if(a[i]!=0){
            b=i;
            break;
        }
    }
    for(int i=b;i<40;i++){
        printf("%d",a[i]);
    }
}
void congmang(int a[],int b[], int c[]){
    int d=0;
    for(int i=39;i>=0;i--){
        c[i]=a[i]+b[i]+d;
        if(c[i]>9){
            d=1;
            c[i]=c[i]-10;
        }
        else
            d=0;       
    }
}
int main(){
    int n;
    do{
      printf("nhap n>0 va n<2147483647: ");
      scanf("%d",&n);
    }while(n<1);
    int f1[40]={},f2[40]={},fn[40]={};
    f1[39]=0;
    f2[39]=1;
    printf("Thu tu         Gia tri");
    for(int i=1;i<=n;i++){
        if(i<=2){
            if(i==1){
                ganmang(fn,f1);
            }else{
                ganmang(fn,f2);
            }
        }
        else{
            congmang(f1,f2,fn);
            ganmang(f1,f2);
            ganmang(f2,fn);
        }
        printf("\n%-5d -    ",i);
        xuatmang(fn);
        
    }
    return 0;
}