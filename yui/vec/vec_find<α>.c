// vec_find<α>.c
#include <yui/vec<α>.h>
#include <stdlib.h>
#include <stdbool.h>

int vec_find<α>(struct vec<α> *this,
        const void *key,
        int (*compar)(const void *, const void *)){
    if(this->dirty){
        qsort(this->data, this->size, sizeof(α), compar);
        this->dirty = false;
    }
    α *bsearch_ret =
        bsearch(key, this->data, this->size, sizeof(α), compar);
    if(bsearch_ret){
        return bsearch_ret - this->data;
    }
    else{
        return -1;
    }
}
