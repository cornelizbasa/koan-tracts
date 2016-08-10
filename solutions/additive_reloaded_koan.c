#include <stdint.h>

typedef int8_t num_t;

// Store the sum in *a, but leave *b unchanged, 
// using only comparisons and unary operators.

// @post *a == @old(*a) + *b
// @const *b 
//   a.k.a. @post *b == @old(*b)
void sum_ptr(num_t *a, num_t *b)
{
    num_t y = *b;
    if (y > 0) {
        for(; y > 0; y--, (*a)++);
    } else {
        for(; y < 0; y++, (*a)--);
    }
}

#ifdef _KLEE_
#include <koan_common.h>
void verify_sum_ptr()
{    
    num_t a;
    num_t old_a;
    num_t b;
    num_t old_b;

    int postcond_1;
    int postcond_2;

    klee_make_symbolic(&a, sizeof(a), gensym(a, __LINE__));
    klee_make_symbolic(&b, sizeof(b), gensym(b, __LINE__));

    old_a = a;
    old_b = b;
 
    sum_ptr(&a, &b);
    
    postcond_1 = a == (num_t)(old_a + b) ;
    postcond_2 = b == old_b;

    assert(postcond_1);
    assert(postcond_2);
}

int main(int argc, char *argv[])
{
    verify_sum_ptr();
}
#endif /* _KLEE_ */
