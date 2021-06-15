#include "dialog.h"
#define FAULT 666

int dialog(){
    int index = 0, enter_size = 20, out = 0;
    wchar_t* string = (wchar_t*)calloc(enter_size, sizeof(wchar_t));
    wchar_t* endptr;
    fputws(L"\nEnter one of the following values for the action:\n", stdout);
    fputws(L"0 (zero) - Complete the program\n", stdout);
    fputws(L"1 - Print each word that occurs no more than once in the text.\n", stdout);
    fputws(L"2 - Each substring in the text having the form “<день> <месяц> <год> г.” is replaced by a substring of the form “ДД / ММ / ГГГГ”.\n", stdout);
    fputws(L"3 - Sort sentences by product of lengths of words in a sentence.\n", stdout);
    fputws(L"4 - Delete all sentences that contain the symbol ‘#’ or ‘№’ but do not contain a single digit.\n", stdout);
    fputws(L"5 - Display the text\n", stdout);
    fputws(L"Enter the value: ", stdout);
    while ((string[index] = getwchar()) != '\n'){
        if (index == enter_size - 1){
            enter_size += 20;
            string = (wchar_t*)realloc(string, enter_size*sizeof(wchar_t));
        }
        index++;
    }
    fputws(L"\n", stdout);
    if (string[0] == '\n'){
        free(string);
        return FAULT;
    }
    string[index] = '\0';
    for (int i = 0; string[i] != '\0'; i++)
        if (iswdigit(string[i])) continue;
        else{
           free(string);
           return FAULT;
        }
    out = (int)wcstol(string, &endptr, 10);
    free(string);
    return out;
}

