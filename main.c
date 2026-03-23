#define LWSL_IMPLEMENTATION
#include "lwsl.h"

int main()
{
    string_builder* Sb = InitStringBuilderWithCapacity(SB_INIT_CAPACITY);
    ReadEntireFile(Sb, "test/sqlite3.c");
    string_view* Sv = InitStringViewWithStringBuilder(Sb);
    PRINT_STRING_VIEW(Sv);
    return(0);
}
