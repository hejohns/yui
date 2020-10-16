// vec_append<α>.c
#include <yui/common.h>
#include <stdlib.h>
#include <stdbool.h>

void vec_append<α>(struct vec<α> *this, const α val){
    if(!(this->size < this->capacity)){
        this->data = yui_realloc(
                this->data,
                sizeof(α) * 2 * this->capacity);
        this->capacity = 2 * this->capacity;
    }
    *vec_at<α>(this, this->size) = val;
    this->size++;
    this->dirty = true;
}
