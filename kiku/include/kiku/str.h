// str.h
#ifndef STR_H
#define STR_H

#include <kiku/common.h>
#include <stdio.h>

/* Modeled after libc functions
 *
 * Takes address of char pointer to realloc if necessary
 * Does NOT support callbacks on *alloc fails
 */

typedef int kiku_str_size_type;

static const unsigned int kiku_str_multiplier = 2;

static inline kiku_str_size_type kiku_str_capacity(const char *ptr){
    // kiku_str_size_type keeping track of capacity is directly before char *
    return *(kiku_str_size_type *)(ptr - sizeof(kiku_str_size_type));
}

/* size - same as strlen would return (not including null term)
 */
static inline void kiku_str_realloc(char **ptr, kiku_str_size_type size){
    // not meant to be called by end user
    char *tmp = kiku_realloc(*ptr - sizeof(kiku_str_size_type),
            sizeof(kiku_str_size_type) + size + 1);
    *(kiku_str_size_type *)tmp = size;
    *ptr = tmp + sizeof(kiku_str_size_type);
}

static inline char *kiku_str_init(char **ptr, kiku_str_size_type size){
    *ptr = kiku_calloc(sizeof(kiku_str_size_type) + size + 1,
            1);
    *(kiku_str_size_type *)(*ptr) = size;
    *ptr += sizeof(kiku_str_size_type);
    return *ptr;
}

static inline void kiku_str_free(char **ptr){
    free(*ptr - sizeof(kiku_str_size_type));
    *ptr = NULL;
}

static inline int kiku_str_vsprintf(char **ptr, const char *format, va_list ap){
/* https://stackoverflow.com/questions/37947200/c-variadic-wrapper
 */
    va_list ap2;
    va_copy(ap2, ap);
    int len = vsnprintf(*ptr, kiku_str_capacity(*ptr) + 1, format, ap);
    if(len < 0){
        // snprintf returns negative len if error occurred
        **ptr = '\0';
        // pass on len up call stack for handling by caller
        return len;
    }
    if(len > (int)kiku_str_capacity(*ptr)){
        kiku_str_realloc(ptr, kiku_str_multiplier * len);
        vsnprintf(*ptr, len + 1, format, ap2);
    }
    va_end(ap2);
    return len;
}

static int kiku_str_sprintf(char **ptr, const char *format, ...){
/* https://stackoverflow.com/questions/37947200/c-variadic-wrapper
 */
    va_list ap;
    va_start(ap, format);
    int ret = kiku_str_vsprintf(ptr, format, ap);
    va_end(ap);
    return ret;
}

static inline char *kiku_str_strcat(char **dest, const char *src){
    kiku_str_size_type destLen = strlen(*dest);
    kiku_str_size_type srcLen = strlen(src);
    if(destLen + srcLen > kiku_str_capacity(*dest)){
        // *dest not large enough to hold resultant string
        kiku_str_realloc(dest, destLen + srcLen);
    }
    memcpy((*dest) + destLen, src, srcLen + 1);
    return *dest;
}

static inline void kiku_str_reserve(char **ptr, kiku_str_size_type size){
    // If new capacity is greater, reallocate storage. Otherwise does nothing
    if(sizeof(kiku_str_size_type) + size + 1 > kiku_str_capacity(*ptr)){
        kiku_str_realloc(ptr, size);
    }
}

static inline void kiku_str_shrink_to_fit(char **ptr){
    kiku_str_realloc(ptr, strlen(*ptr));
}

#endif /* STR_H */
