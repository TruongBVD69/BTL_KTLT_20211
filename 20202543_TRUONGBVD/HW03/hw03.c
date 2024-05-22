#include<stdio.h>
#include<string.h>
#include<ctype.h>

int check_inputfile(char c[]){         // Hàm con kiểm tra file đầu vào là text hay morse
    for(int i=0;i<strlen(c);i++){
        if(c[i]=='\n')
            continue;
        if(c[i]!='-'&&c[i]!='/'&&c[i]!=' '&&c[i]!='.')
            return 1;                 // nếu file đầu vào chứa 1 kí tự không phải morse thì là file text
    }
    return 0;   
}

void convert_M_to_T(char c[], FILE* f2,int h){   // Hàm chuyển từ morse sang text
    char *morse[]={".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--..","/","-----", ".----", "..---", "...--", "....-",".....", "-....", "--...", "---..", "----.","........",".-.-.-","..--..","..--..","--..--","---..."};
    char text[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',' ','0','1','2','3','4','5','6','7','8','9','#','.','?','-',',',':'};
    char b[10];     // mảng để chứa các kí tự morse đọc được
    int j;
    for(int i=0;i<strlen(c);i++){
        
        if(c[i]==' ')  // loại bỏ dấu cách 
            continue;

        if(c[i]=='\n')  // loại bỏ xuống dòng
            continue;

        for(j=0;c[i]!=' '&&i<strlen(c);j++){  // đọc các kí tự morse cho tới dấu cách thì dừng lại

                b[j]=c[i];
                i++;
        }

        b[j]='\0';    
        if(b[j-1]=='\n')
            b[j-1]='\0';  // loại bỏ kí tự xuống dòng

        for(int k=0;k<43;k++){
            if(strcmp(b,morse[k])==0){           // so sánh kí tự morse đọc được và các kí tự morse đã khai báo sẵn
                fprintf(f2,"%c",text[k]);
                break;
            }
            if(k==42){            // khi không có kí tự morse nào tương ứng thì in ra *
                fprintf(f2,"*");        
                printf("\nError: Invalid Morse code %s on line %d.",b,h+1);  // in kí tự lỗi và dòng chứa kí tự lỗi lên màn hình
            }
        }

    }
}

void convert_T_to_M(char c[], FILE* f2,int j){
    strupr(c);
    char *morse[]={".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."};
    char *morse_num[]={"-----", ".----", "..---", "...--", "....-",".....", "-....", "--...", "---..", "----." } ;
    char special[]={'.','?','-',',',':'}; 
    char *morse_special[]={".-.-.-","..--..","..--..","--..--","---..."};
    
    for(int i=0;i<strlen(c);i++){
        
        if(c[i]==' '&&c[i+1]==' ')   // loại bỏ các dấu cách đứng cạnh nhau không cần thiết
            continue;

        if(c[i]==' '&&c[i+1]=='\0')   // loại bỏ dấu cách ở cuối file đầu vào
            continue;

        if(c[i]==' '&&c[i+1]=='\n')   // loại bỏ dấu cách trước xuống dòng 
            continue;

        if(c[i]=='\n')                // loại bỏ kí tự xuống dòng
            continue;

        int dem=0;              
        for(int k=0;k<5;k++){
            if(c[i]==special[k]){
                fprintf(f2,"%s ",morse_special[k]);   // dịch các kí tự đặc biệt ? - . , :
                dem=1;
                break;                 
            }
        }
        if(dem==1)   // nếu là kí tự đặc biệt thi tiếp tục không kiểm tra nữa
            continue;

        if(isalpha(c[i]))                          // dịch nếu kí tự nếu là chữ cái 
            fprintf(f2,"%s ",morse[c[i] - 'A']);
        else
            if(isdigit(c[i]))            
                fprintf(f2,"%s ",morse_num[c[i] - '0']);  // dịch nếu kí tự nếu là số
            else
                if(c[i]==' ')           // dịch dấu cách 
                    fprintf(f2,"/ ");
                else{
                    printf("\nUnrecognised character %c on line %d",c[i],j+1);// không có kí tự morse tương ứng thì bỏ qua 
                }                                                     // và hiện lên màn hình kí tự đó cũng như dòng chứa kí tự đó
    }
}
int main(){   
    char c[1000],d[20][1000]; // c là mảng để đọc các dòng file đầu vào, d là mảng 2 chiều chứa toàn bộ các dòng file đầu vào
    char inputfile[50],outputfile[50];
    int i=0;    // biến đếm số dòng
    char inspect[10]; // mảng dùng để kiểm tra file đầu ra đã tồn tại hay chưa?
    char k;    // biến nhận yêu cầu ghi đè hay không?

    printf("Nhap dia chi input_file:");
    gets(inputfile);
    printf("Nhap dia chi output_file:");
    gets(outputfile);

    FILE *f1,*f2;

    f1=fopen(inputfile,"r");
    if(f1==NULL){
        printf("%s could not be opened.",inputfile);
        return 0;
    }
     
    while(feof(f1)==0){       // đọc và ghi các kí tự file input vào mảng 2 chiều d
        fgets(c,500,f1);           
        strcpy(d[i],c);                 
        i++;                               
    }    
    
    int check;     // biến kiểm tra file đầu vào là file text hay file morse                  
    for(int t=0;t<i;t++){
        check=check_inputfile(d[k]);
        if(check==1)                    // bằng 1 là file text còn bằng 0 là file morse
            break;
    }
    
    f2=fopen(outputfile,"r+");

    if(f2==NULL){
        printf("%s could not be opened.",outputfile);
        return 0;
    }
    
    fgets(inspect,10,f2); // lấy 10 kí tự đầu tiên của file đầu ra
    
    if(strlen(inspect)!=0){  // Kiểm tra xem file đầu ra đã tồn tại hay chưa? mảng inspect khác 0 tức là đã tồn tại
        printf("%s FILENAME already exists. Do you wish to overwrite (y,n)? your answer is ",outputfile);
        scanf("%c",&k);
        if(k=='y'){

            f2=fopen(outputfile,"w"); 
            if(check==1){
                printf("input_file is text_file");    
        
                for(int j=0;j<i;j++){  
                    convert_T_to_M(d[j],f2,j);  // thực hiện dịch text thành morse
                    if(j!=i-1)
                        fprintf(f2,"\n");                                
                }
            }else{
                printf("input_file is morse_file");
        
                for(int j=0;j<i;j++){
                    convert_M_to_T(d[j],f2,j); // thực hiện dịch morse thành text
                if(j!=i-1)
                    fprintf(f2,"\n");
                }
            }

        }else
            return 0;
    }else{                 // Đây là khi file đầu ra trống thì thực hiện dịch và in mà không cần sự đồng ý người nhập

        if(check==1){
            printf("input_file is text_file");
            
            for(int j=0;j<i;j++){  
                convert_T_to_M(d[j],f2,j);
                if(j!=i-1)
                    fprintf(f2,"\n");                                
            }
        }else{
            printf("input_file is morse_file");
            
            for(int j=0;j<i;j++){
                convert_M_to_T(d[j],f2,j);
                if(j!=i-1)
                    fprintf(f2,"\n");
            }
        }
    }
    
    fclose(f1);
    fclose(f2);
}