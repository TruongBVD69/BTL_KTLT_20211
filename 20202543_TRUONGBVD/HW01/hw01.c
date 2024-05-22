
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
 
void printBinary(int n, int i)
{
    int k;
    for (k = i - 1; k >= 0; k--) {
 
        if ((n >> k) & 1)
            printf("1");
        else
            printf("0");
    }
}
 
typedef union {
 
    float f;
    struct
    {   
        unsigned int mantissa : 23;
        unsigned int exponent : 8;
        unsigned int sign : 1;
 
    } raw;
} myfloat;

unsigned int convertToInt(int* arr, int low, int high)
{
    unsigned f = 0, i;
    for (i = high; i >= low; i--) {
        f = f + arr[i] * pow(2, high - i);
    }
    return f;
}
 
 
void printIEEE(myfloat var)
{
  
    printf("%d | ", var.raw.sign);
    printBinary(var.raw.exponent, 8);
    printf(" | ");
    printBinary(var.raw.mantissa, 23);
    printf("\n");
}
 
// Driver Code
int main()
{

    unsigned int ieee[32];

    float  f = 0;
    // Instantiate the union
    myfloat var;
 
    // Get the real value
    printf("Type number you want to convert: ");
    scanf("%f", &f);
    var.f = f;
 
    // Get the IEEE floating point representation
    printf("IEEE 754 representation of %f is : \n",
           var.f);
    printIEEE(var);

    printf("Type sign bit:");
    scanf("%d", &ieee[0]);

    printf("Type exponent bits:");
    for (int i = 0; i < 8; i++)
    {
        /* code */
        scanf("%d ", &ieee[1 + i]);
    }

    printf("Type mantissa bits:");
    for (int i = 0; i < 23; i++)
    {
        /* code */
        scanf("%d ", &ieee[9 + i]);
    }
    
    unsigned out = convertToInt(ieee, 9, 31);
    
    var.raw.mantissa = out;

    out = convertToInt(ieee, 1, 8);

    var.raw.exponent = out;

    var.raw.sign = ieee[0];

    printf("The float value of the given"
           " IEEE-754 representation is : \n");
    printf("%f", var.f);
 
    return 0;
}