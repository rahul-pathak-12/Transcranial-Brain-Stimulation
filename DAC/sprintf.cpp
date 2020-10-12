#include <stdio.h>

//hex and oct examples
    int main()
    {
    char buff[50];
    int ret;
    int hex = 0;
    int oct = 5626;
        ret = sprintf(buff, "%x is %d in hex and %o is %d in octal\n",hex,hex,oct,oct);
        printf("%s, %d chars long\n", buff, ret);
        printf("%s\n",buff);
    getchar();
    getchar();
    return 0;
    }
