// vec<α>.h
#ifndef VEC ## α ## _H
#define VEC ## α ## _H
#include <yui/common.h>
#include <stddef.h>
#include <stdbool.h>

struct vec<α>{
    α *data;
    size_t size;
    size_t capacity;
    bool dirty;
};

static inline struct vec_init<α>(){
    return (struct vec<α>){
        yui_malloc(64*sizeof(α)),
        0,
        64,
        false
    };
}

static inline α *vec_at<α>(struct vec<α> *this, size_t pos){
    return (this->data) + (sizeof(α) * pos);
}

static inline void vec_free<α>(struct vec<α> *vec){
    yui_free(&(vec->data));
    vec->size = 0;
    vec->capacity = 0;
}

int vec_find<α>(struct vec<α>, 
        const void *,
        int (*)(const void * const void *));
#endif /* VEC ## α ## _H */
