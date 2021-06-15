#ifndef TXTIO_H
#define TXTIO_H

#include <stdio.h>
#include <stdlib.h>
#include <wctype.h>
#include <wchar.h>
#include <locale.h>

struct Sentence{
    wchar_t* words_arr;
    int alloc_sent;
    int symb_count;
    int mult_wrd;
};

typedef struct Sentence sentence;

struct Text{
    sentence* text;
    int alloc_text;
    int sent_count;
};

typedef struct Text text;

void input_txt(text *text);
void output_txt(text *text);

#endif
