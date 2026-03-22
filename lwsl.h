#ifndef LWSL_H
#define LWSL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define SB_INIT_CAPACITY 4

typedef int32_t  int32;
typedef uint32_t uint32;
typedef int32_t  bool32;


typedef struct
{
    char* Str;
    size_t Count;
    size_t Capacity;
}string_builder;

typedef struct
{
    const char* Data;
    size_t Count;
}string_view;

size_t GetFileSize(const char* FilePath);
string_builder* InitStringBuilderWithCapacity(size_t Capacity);
void AppendCstrToStringBuilder(string_builder* Sb, const char* Cstr);
void ReadEntireFile(string_builder* Sb, const char* FilePath);
void FreeStringBuilder(string_builder* Sb);
string_view* InitStringViewWithStringBuilder(string_builder* Sb);
string_view* InitStringView(char* Data, size_t Count);
void FreeStringView(string_view* Sv);

#endif // LWSL_H

#ifdef LWSL_IMPLEMENTATION

size_t GetFileSize(const char* FilePath)
{
    size_t Result = 0;
    FILE* Fp = fopen(FilePath, "rb");
    if(!Fp)
    {
        printf("Failed to Open File");
        return 1;
    }
    while(fgetc(Fp) != EOF);
    Result = ftell(Fp);
    fclose(Fp);
    return(Result);
}

string_builder* InitStringBuilderWithCapacity(size_t Capacity)
{
    string_builder* Result = (string_builder*)malloc(sizeof(string_builder));
    if(!Result)
    {
        return NULL;
    }
    Result->Capacity = Capacity;
    Result->Str = (char*)malloc(Result->Capacity * sizeof(char));
    if(!Result)
    {
        return NULL;
    }
    Result->Count = 0;
    return(Result);
}

// ItemSize is number of chars you want to add it to the Sb.
#define REALLOC(Sb, ItemSize)                                   \
do{                                                             \
    while(((Sb)->Count) + ItemSize > (Sb)->Capacity){           \
        (Sb)->Capacity *= 2;                                    \
        char* Temp = realloc((Sb)->Str, (Sb)->Capacity);        \
        if (!Temp) {                                            \
            printf("Reallocation failed");                      \
            break;                                              \
        }                                                       \
        (Sb)->Str = Temp;                                       \
    }                                                           \
}while(0)

void AppendCstrToStringBuilder(string_builder* Sb, const char* Cstr)
{
    size_t Length = strlen(Cstr);
    REALLOC(Sb, Length);
    memcpy(Sb->Str + Sb->Count, Cstr, Length * sizeof(char));
    Sb->Count += Length;
}

#define AddNullCharToStringBuilder(Sb)                          \
do {                                                            \
    REALLOC(Sb, 1);                                             \
    (Sb)->Str[(Sb)->Count++] = '\0';                            \
} while(0)


void ReadEntireFile(string_builder* Sb, const char* FilePath)
{

    size_t FileSize = GetFileSize(FilePath);
    char* NewStr = Sb->Str;

    REALLOC(Sb, FileSize);
    FILE* Fp = fopen(FilePath, "rb");
    if(!Fp)
    {
        printf("Failed to Open File");
        return;
    }
    while(FileSize--)
    {
        Sb->Str[Sb->Count++] = fgetc(Fp);
    }
    fclose(Fp);
}

string_view* InitStringViewWithStringBuilder(string_builder* Sb)
{
    string_view* Sv = (string_view*)malloc(sizeof(string_view));
    if(!Sv)
    {
        return NULL;
    }
    Sv->Data = Sb->Str;
    Sv->Count = Sb->Count;
    return(Sv);
}

string_view* InitStringView(char* Data, size_t Count)
{
    string_view* Sv = (string_view*)malloc(sizeof(string_view));
    if(!Sv)
    {
        return NULL;
    }
    Sv->Data = Data;
    Sv->Count = Count;
    return(Sv);
}

void FreeStringBuilder(string_builder* Sb)
{
    if(Sb)
    {
        free(Sb->Str);
        free(Sb);
    }
}

void FreeStringView(string_view* Sv)
{
    if(Sv)
    {
        free(Sv);
    }
}
#endif // LWSL_IMPLEMENTATION
