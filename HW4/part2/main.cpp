#include <iostream>
#include <string>
using namespace std;
int main()
{
    char str1[10] = {0};
    scanf("%[^\n]s\n",str1);
    for (char i : str1)
        printf("%c", i);

    return 0;
}
