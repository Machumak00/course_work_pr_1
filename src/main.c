#include "txtio.h"
#include "txted.h"
#include "del_sent.h"
#include "dialog.h"

int main(){
    setlocale(LC_ALL,"");
    text text;
    input_txt(&text);
    del_sent(&text);
    output_txt(&text);
    int n;
    while ((n = dialog()) != 0){
        switch (n){
            case 1:
                func_1(&text);
                break;
            case 2:
                func_2(&text);
                break;
            case 3:
                func_3(&text);
                break;
            case 4:
                func_4(&text);
                break;
            case 5:
                output_txt(&text);
                break;
            default:
                fputws(L"Incorrect value entered! Please use the correct entry.\n", stdout);
                break;
        }
    }
    for (int i = 0; i < text.sent_count; i++){
        free(text.text[i].words_arr);
    }
    free(text.text);
    return 0;
}

