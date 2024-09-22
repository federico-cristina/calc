#include "calc/base/utf8.h"

int handle(int value)
{
    return eprintfn("an error has been occurred: %d.", value), 1;
}

int main()
{
    int i = (utf8_category(0x3042) & UTF8_CATEGORY_LO) == UTF8_CATEGORY_LO;
    
    return 0;
}
