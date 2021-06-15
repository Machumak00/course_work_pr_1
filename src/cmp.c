#include "txtio.h"

int cmp(const void* a, const void* b){
    if (*(int*)a > *(int*)b)
    	return 1;
    if (*(int*)a < *(int*)b)
    	return -1;
    return 0;
}

int cmp_txt(const void* a, const void* b){
    if (((sentence*)a)->mult_wrd > ((sentence*)b)->mult_wrd)
        return 1;
    if (((sentence*)a)->mult_wrd < ((sentence*)b)->mult_wrd)
        return -1;
    return 0;
}

