#include <stdint.h>

typedef int8_t num_t;

// Return the sum of a and b using only comparisons and unary operators.

// @return a + b
num_t sum(num_t a, num_t b)
{
    if(b > 0) {
        // ...
    } else {
        for(; b < 0;);
    }    
    return a;
}

#ifdef _KLEE_
#include <koan_common.h>
void verify_sum()
{    
    num_t a;
    num_t b;

    int return_ok;

    klee_make_symbolic(&a, sizeof(a), gensym(a, __LINE__));
    klee_make_symbolic(&b, sizeof(b), gensym(b, __LINE__));

    return_ok = (num_t)(a + b) == sum(a, b);

    assert(return_ok);
}

int main(int argc, char *argv[])
{
    verify_sum();
}
#endif /* _KLEE_ */
