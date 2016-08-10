#ifndef KOAN_COMMON_H
#include <klee/klee.h>
#include <assert.h>

#define gensym(base, line)  gensym1(base, line)
#define gensym1(base, line) strsym(base ## _line_ ## line)
#define strsym(a) #a
#endif /* KOAN_COMMON_H */
