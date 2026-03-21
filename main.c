#define LWSL_IMPLEMENTATION
#include "lwsl.h"
int main()
{
    string_builder* Sb = InitStringBuilderWithCapacity(SB_INIT_CAPACITY);
    ReadEntireFile(Sb,"test.txt");
    AddNullCharToStringBuilder(Sb);
    printf("%s", Sb->Str);
    printf("%zu", Sb->Count);
    return(0);
}
