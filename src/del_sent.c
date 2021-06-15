#include "del_sent.h"
#include "cmp.h"

void del_sent (text* text)
{
    int len_arr = 20, num = 0, shift = 0, ind_sent1 = 0, ind_sent2 = 0, sent_arr_num, shift_num, *arr_num;
    arr_num = (int*)malloc(sizeof(int)*len_arr);
    for (ind_sent1 = 0; ind_sent1 < text->sent_count; ind_sent1++)
        for (ind_sent2 = ind_sent1 + 1; ind_sent2 < text->sent_count; ind_sent2++)
            if (wcslen(text->text[ind_sent1].words_arr) == wcslen(text->text[ind_sent2].words_arr))
                if (wcscasecmp(text->text[ind_sent1].words_arr, text->text[ind_sent2].words_arr) == 0){
                    if (num >= len_arr - 2){
                        len_arr += 20;
                        arr_num = realloc(arr_num, sizeof(int)*len_arr);
                    }
                    if (in_out(arr_num, num, ind_sent1)){
                        arr_num[num] = ind_sent1;
                        num++;
                    }
                    if (in_out(arr_num, num, ind_sent2)){
                        arr_num[num] = ind_sent2;
                        num++;
                    }
                }
    qsort(arr_num, num, sizeof(int), cmp);
    for (ind_sent1 = 0; ind_sent1 < num; ind_sent1++){
        shift_num = arr_num[ind_sent1] - shift;
        for (int j = 0; text->text[shift_num].words_arr[j]; j++){
            text->text[shift_num].words_arr[j] = '\0';
        }
        sent_arr_num = text->sent_count - 1;
        for (ind_sent2 = shift_num; ind_sent2 < sent_arr_num; ind_sent2++){
            if(text->text[ind_sent2].alloc_sent < text->text[ind_sent2+1].alloc_sent){
                text->text[ind_sent2].words_arr = realloc(text->text[ind_sent2].words_arr, sizeof(wchar_t)*text->text[ind_sent2+1].alloc_sent);
            }
            text->text[ind_sent2].symb_count = text->text[ind_sent2+1].symb_count;
            text->text[ind_sent2].alloc_sent = text->text[ind_sent2+1].alloc_sent;
            wcscpy(text->text[ind_sent2].words_arr, text->text[ind_sent2+1].words_arr);
        }
        text->sent_count -= 1;
        shift += 1;
    }
    free(arr_num);
}

int in_out (int* arr_num, int num, int ind){
    for(int i = 0 ; i < num; i++){
        if (arr_num[i] == ind){
            return 0;
        }
    }
    return 1;
}

