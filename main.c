#define LWSL_IMPLEMENTATION
#include "lwsl.h"

#define DEBUG
#ifdef DEBUG

void PrintString(const char* Str, size_t Count)
{
    for(size_t i = 0; i < Count; ++i)
    {
        if((i+1) % 8 == 0)
        {
            printf("\n");
            continue;
        }
        printf("%02X ", Str[i]);
    }
    printf("\n");
}
#endif

int main()
{
    string_builder* Sb = InitStringBuilderWithCapacity(SB_INIT_CAPACITY);
    ReadEntireFile(Sb, "test/sqlite3.c");
    string_view* Sv = InitStringViewWithStringBuilder(Sb);
    PrintString(Sv->Data, Sv->Count);

    return(0);
}
