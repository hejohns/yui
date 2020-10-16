// common.h
#ifndef COMMON_H
#define COMMON_H

#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#if !defined(__STRICT_ANSI__) && defined(__GNUC__)
#  warning "using gcc attributes"
#else
#  warning "disabling gcc attributes"
#  define __attribute__(x) /* mask attributes for non-gnuc compilers */
#endif

/* 
 * define YUI_USE_STATIC_BUF to use a static char buffer
 * of size YUI_MEMSWP_BUFSIZ chars
 *
 * define YUI_USE_VLA to use vla/memcpy for memswp
 *
 * define YUI_USE_DUFFS to use duff's device for memswp
 *
 * default is as in glibc, to be safe and only use a single char buffer
 */
void memswp(void *restrict a, void *restrict b, size_t size);

__attribute__((malloc))
void *yui_malloc(size_t size);

__attribute__((malloc))
void *yui_malloc_c(
        size_t size,
        void *(*callback)(va_list),
        ...
        );

/* usage is different than stdlib's free()
 *
 * void *ptr = yui_malloc(1);     vs     void *ptr = malloc(1);
 * yui_free(&ptr);                       free(ptr), ptr = NULL;
 */
void yui_free(void *ptr);

__attribute__((malloc))
void *yui_calloc(size_t nmemb, size_t size);

__attribute__((malloc))
void *yui_calloc_c(
        size_t nmemb,
        size_t size,
        void *(*callback)(va_list),
        ...
        );

void *yui_realloc(void *ptr, size_t size);

void *yui_realloc_c(
        void *ptr,
        size_t size,
        void *(*callback)(va_list),
        ...
        );
#endif /* COMMON_H */
