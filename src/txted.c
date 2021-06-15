#include "txted.h"
#define MONTHS 12

void func_1(text* text){
    wchar_t** arr, *sent = NULL, *state, *str;
    int n = 0, arr_size = 20, no_words = 0;

    arr = (wchar_t**)calloc(sizeof(wchar_t*), arr_size);

    for(int i = 0; i < text->sent_count; i++){
        sent = (wchar_t*)calloc(sizeof(wchar_t), text->text[i].alloc_sent);
        wcscpy(sent, text->text[i].words_arr);

        for (str = wcstok(sent, L" ,.", &state); str != NULL; str = wcstok(NULL, L" ,.", &state)){
            if (n == arr_size - 2){
                arr_size += 20;
                arr = (wchar_t**)realloc(arr, sizeof(wchar_t*)*arr_size);
            }
            arr[n] = (wchar_t*)calloc(sizeof(wchar_t), (wcslen(str)) + 1);
            wcscpy(arr[n], str);
            n++;
        }
    }

    for (int j = 0; j < n - 1; j++){
        str = arr[j];
        if (wcscmp(str, L"") != 0)
            for (int k = j + 1; k < n; k++){
                if (wcscmp(str, arr[k]) == 0){
                    arr[k] = L"";
                    arr[j] = L"";
                }
            }
    }

    for (int i = 0 ; i < n; i++)
    {
        if (wcscmp(arr[i], L"") != 0){
            fputws(arr[i], stdout);
            fputws(L"\n", stdout);
            no_words++;
        }
    }
    if (no_words == 0)
        fputws(L"No unique words in the text\n", stdout);
    fputws(L"\nThe func_1 is done.\n", stdout);

    for (int i = 0 ; i < n; i++){
        if (wcscmp(arr[i], L"") != 0)
            free(arr[i]);
    }
    free(sent);
    free(arr);
}

void func_2(text* text){
    wchar_t *months[MONTHS] = {L"января", L"февраля", L"марта", L"апреля", L"мая", L"июня",
                               L"июля", L"августа",L"сентября", L"октября", L"ноября", L"декабря"};
    int max_days[MONTHS] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int month_symbs[MONTHS] = {6, 7, 5, 6, 3, 4, 4, 7, 8, 7, 6, 7};
    int month_num = 0;
    wchar_t *checker = NULL;
    int date, year, leap;
    
    for (int sent = 0; sent < text->sent_count; sent++){
        leap = 0;
        for (month_num = 0; month_num < MONTHS; month_num++)
            if ((checker = wcsstr(text->text[sent].words_arr, months[month_num])) != NULL)
                break;
        if (checker == NULL) continue;
        
        if (!((iswdigit(*(checker - 3)) && iswdigit(*(checker - 2)) && iswspace(*(checker + month_symbs[month_num]))
        && iswdigit(*(checker + month_symbs[month_num] + 1)) && iswdigit(*(checker + month_symbs[month_num] + 2))
        && iswdigit(*(checker + month_symbs[month_num] + 3)) && iswdigit(*(checker + month_symbs[month_num] + 4))
        && iswspace(*(checker + month_symbs[month_num] + 5)) && (*(checker + month_symbs[month_num] + 6) == L'г')
        && (*(checker + month_symbs[month_num] + 7) == L'.')))) continue;
        if (!(iswdigit(*(checker - 3)))) date = (int)wcstol(checker - 2, NULL, 10);
        else date = (int)wcstol(checker - 3, NULL, 10);
        year = (int)wcstol(checker + month_symbs[month_num] + 1, NULL, 10);
        if (year % 4 == 0) leap = 1;
        if (!(((date >= 1) && (date <= max_days[month_num])) || ((leap == 1) && (month_num == 1)
        && (date == 29))) && (year >= 0)) continue;
        
        if (month_num + 1 < 10){
            if (year < 10) swprintf(checker - 1, 10, L"/0%d/000%d.", month_num + 1, year);
            else if (year < 100) swprintf(checker - 1, 10, L"/0%d/00%d.", month_num + 1, year);
            else if (year < 1000) swprintf(checker - 1, 10, L"/0%d/0%d.", month_num + 1, year);
            else if (year < 10000) swprintf(checker - 1, 10, L"/0%d/%d.", month_num + 1, year);
        }
        else{
            if (year < 10) swprintf(checker - 1, 10, L"/%d/000%d.", month_num + 1, year);
            else if (year < 100) swprintf(checker - 1, 10, L"/%d/00%d.", month_num + 1, year);
            else if (year < 1000) swprintf(checker - 1, 10, L"/%d/0%d.", month_num + 1, year);
            else if (year < 10000) swprintf(checker - 1, 10, L"/%d/%d.", month_num + 1, year);
        }
    }
    fputws(L"The func_2 is done.\n", stdout);
}

void func_3(text* text){
    int words = 0, n = 1;
    wchar_t *sent = NULL, *str, *state;
    for (int i = 0; i < text->sent_count; i++){
        sent = (wchar_t*)calloc(sizeof(wchar_t), text->text[i].alloc_sent);
        wcscpy(sent, text->text[i].words_arr);

        for (str = wcstok(sent, L" ,.", &state); str != NULL; str = wcstok(NULL, L" ,.", &state)) {
            n *= (int) wcslen(str);
            words++;
        }
        if (words == 1) text->text[i].mult_wrd = 0;
        else text->text[i].mult_wrd = n;
        n = 1;
        words = 0;
    }
    qsort(text->text, text->sent_count, sizeof(sentence), cmp_txt);
    fputws(L"The func_3 is done.\n", stdout);
    free(sent);
}

void func_4(text* text){
    int lat, num;
    wchar_t *sent = NULL;
    for (int i = 0; i < text->sent_count; i++){
        sent = (wchar_t*)calloc(sizeof(wchar_t), text->text[i].alloc_sent);
        wcscpy(sent, text->text[i].words_arr);
        if (wcschr(sent, L'#')) lat = 1;
        else lat = 0;
        if (wcschr(sent, L'№')) num = 1;
        else num = 0;
        if (!((wcschr(sent, L'0')) || (wcschr(sent, L'1')) || (wcschr(sent, L'2')) || (wcschr(sent, L'3')) ||
        (wcschr(sent, L'4')) || (wcschr(sent, L'5')) || (wcschr(sent, L'6')) || (wcschr(sent, L'7')) ||
        (wcschr(sent, L'8')) || (wcschr(sent, L'9'))) && (lat != num)){
            for (int j = 0; j <= text->text[i].symb_count; j++){
                text->text[i].words_arr[j] = L'\0';
            }
        }
    }
    del_void(text);
    free(sent);
    fputws(L"The func_4 is done.\n", stdout);
}

void del_void(text* text){
    int count;
    int i = 0;
    while(i < text->sent_count){
        if (wcscmp(text->text[i].words_arr, L"") == 0){
            count = text->sent_count - 1;
            for(int j = i; j < count; j++){
                if (text->text[j].alloc_sent < text->text[j+1].alloc_sent){
                    text->text[j].words_arr = (wchar_t*)realloc(text->text[j].words_arr, sizeof(wchar_t)*text->text[j+1].alloc_sent);
                    text->text[j].alloc_sent = text->text[j+1].alloc_sent;
                }
                wcscpy(text->text[j].words_arr,text->text[j+1].words_arr);
                text->text[j].symb_count = text->text[j+1].symb_count;
            }
            text->sent_count -= 1;
            continue;
        }
        i++;
    }
} 
