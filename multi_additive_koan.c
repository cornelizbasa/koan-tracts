#include <stdint.h>

typedef int8_t num_t;

// Complete sum_or_product_ptr without using only comparisons and unary operators.
// Using sum_ptr is OK.

// Blimey, a global var!
int op;

// Deja-vu

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

// @const *a
// @const *b
// @const op
// @return op == 0 ? *a + *b: *a * *b
num_t sum_or_product_ptr(num_t *a, num_t *b)
{
    num_t x = *a;
    if (0 == op) {
        return x;
    } else {
        num_t y = 0;
        if(/* ... */ 0) {
            for (/* ... */) {
            
            }
            return y;
        } 
        if (x < 0) {
            // ...   
                sum_ptr(&y, b);
            // ...
            return -y;
        }
        // ...
    }
}

#ifdef _KLEE_
#include <koan_common.h>
void verify_sum_or_product_ptr()
{    
    num_t a;
    num_t old_a;
    num_t b;
    num_t old_b;

    int old_op;

    int return_ok;

    klee_make_symbolic(&op, sizeof(op), gensym(op, __LINE__));

    klee_make_symbolic(&a, sizeof(a), gensym(a, __LINE__));
    klee_make_symbolic(&b, sizeof(b), gensym(b, __LINE__));

    old_a = a;
    old_b = b;
    
    old_op = op;
    
    return_ok = (num_t)(op == 0 ? a + b: a * b) == sum_or_product_ptr(&a, &b);

    assert(return_ok);
    
    assert(old_a == a);
    assert(old_b == b); 
    
    assert(old_op == op);
}

int main(int argc, char *argv[])
{
    verify_sum_or_product_ptr();
    return 0;
}
#endif /* _KLEE_ */
