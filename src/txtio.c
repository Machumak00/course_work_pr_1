#include "txtio.h"

void input_txt(struct Text *text){
    fputws(L"Please enter the text: \n",stdout);
    int checker = 0, dot = 0, ind_sent = 0, ind_symb = 0;
    wchar_t symbol;
    text->alloc_text = 10;
    text->text = (sentence*)malloc(sizeof(sentence)*text->alloc_text);
    text->sent_count = 0;
    while ((symbol = getwchar()) != '\n'){
        if ((symbol == L' ' || symbol == L'.' || symbol == ',' ) && ind_symb == 0) continue;
        if (checker == 1 && (symbol == L',' || symbol == ' ')) continue;
        else if (checker == 1 && symbol == '.'){
            text->text[ind_sent].words_arr[ind_symb-1] = symbol;
            text->text[ind_sent].words_arr[ind_symb] = '\0';
            text->text[ind_sent++].symb_count = ind_symb-1;
            ind_symb = 0;
            dot = 1;
            text->sent_count++;
            continue;
        }
        checker = 0;
        if (ind_symb == 0){
            text->text[ind_sent].alloc_sent = 50;
            text->text[ind_sent].words_arr = (wchar_t*)malloc(sizeof(wchar_t)*(text->text[ind_sent].alloc_sent));
        }
        text->text[ind_sent].words_arr[ind_symb++] = symbol;
        dot = 0;
        if (ind_sent == text->alloc_text - 1){
            text->alloc_text += 20;
            text->text = (sentence*)realloc(text->text, sizeof(sentence)*(text->alloc_text));
        }
        if(ind_symb == text->text[ind_sent].alloc_sent - 3){
            text->text[ind_sent].alloc_sent += 30;
            text->text[ind_sent].words_arr = (wchar_t*)realloc(text->text[ind_sent].words_arr, sizeof(wchar_t)*(text->text[ind_sent].alloc_sent));
        }
        if (symbol == '.'){
            text->text[ind_sent].words_arr[ind_symb] = '\0';
            text->text[ind_sent++].symb_count = ind_symb;
            text->sent_count += 1;
            ind_symb = 0;
            dot = 1;
        }
        else if (symbol == ' ' || symbol == ','){
           checker = 1;
        }
    }
    if (dot == 0){
        if (text->text[ind_sent].words_arr[ind_symb-1] == ' ' || text->text[ind_sent].words_arr[ind_symb] == ','){
            text->text[ind_sent].words_arr[ind_symb-1] = '.';
            text->text[ind_sent].words_arr[ind_symb] = '\0';
        }
        else{
            text->text[ind_sent].words_arr[ind_symb] = '.';
            text->text[ind_sent].words_arr[ind_symb+1] = '\0';
        }
        text->sent_count++;
        text->text[ind_sent].symb_count = ind_symb;
    }

}

void output_txt(text *text){
    fputws(L"\nYour text is:\n", stdout);
    for(int i = 0 ; i < text->sent_count; i++){
        fputws(text->text[i].words_arr, stdout);
    }
    fputws(L"\n", stdout);
}
