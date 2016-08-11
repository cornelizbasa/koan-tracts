#include <stdint.h>

typedef int8_t num_t;
typedef uint8_t count_t;

// Complete the sort_even function according to its contract.
// It should: 
// - return the number of even elements,
// - sort the even elements, and
// - keep the odd ones in place.

// @post sorted_even(a, n)
// @post unchanged_odd(a, @old(a), n)
// @post same_elem(a, @old(a), n)
// @return count_even(a, n)
count_t sort_even(num_t *a, count_t n)
{
    count_t count;
    int changed = 1;
    
    while(changed) {
        count_t i;
        for(i = 0, changed = 0, count = 0; /* */; i++) {
            count_t j;
            if(/* */) {
                continue;
            }
            count++;
            for(j = i + 1; j < n; j++) {
                if(/* */) {
                
                }
                if(a[j] < a[i]) {
                
                }
            }
        }
    }
    return count;
}

#ifdef _KLEE_ // hand-coded auxiliary functions for contracts
count_t count_even(num_t *a, count_t n)
{
    count_t i;
    count_t count;
    for(i = 0, count = 0; i < n; i++) {
        if(0 == a[i] % 2) {
            count++;
        }
    }
    return count;
}

int unchanged_odd(num_t *a, num_t *old_a, count_t n)
{
    count_t i;
    for(i = 0; i < n; i++) {
        if(0 != a[i] % 2) {
            if(a[i] != old_a[i]) {
                return 0;
            }
        }
    }
    return 1;
}

int sorted_even(num_t *a, count_t n)
{
    count_t i;
    int found;
    num_t max;
    for(i = 0, found = 0; i < n; i++) {
        if(0 == a[i] % 2) {
            if(0 == found) {
                max = a[i];
                found = 1;
                continue;
            }
            if(max > a[i]) {
                return 0;
            }
            max = a[i];
        }
    }
    return 1;
}

int same_elem(num_t *a, num_t *old_a, count_t n)
{
    count_t i;
    for(i = 0; i < n; i++) {
        count_t j, k;
        count_t count_a = 0, count_old_a = 0;
        for(j = 0; j < n; j++) {
            if(a[j] == a[i]) {
                count_a++;
            }
        }
        for(k = 0; k < n; k++) {
            if(a[k] == a[i]) {
                count_old_a++;
            }
        }
        if(count_a != count_old_a) {
            return 0;
        }
    }
    return 1;
}
#endif /* _KLEE_ */ // hand-coded auxiliary functions for contracts

#ifdef _KLEE_ // verifier to be generated
#include <koan_common.h>
void copy(void *dest, void *src, count_t n)
{
    count_t i;
    num_t *dest_num_t = (num_t *)dest;
    num_t *src_num_t = (num_t *)src;

    for(i = 0; i < n; i++) {
        dest_num_t[i] = src_num_t[i];
    }
}

void verify_sort_even(count_t n)
{
   num_t a[n], old_a[n];
   
   klee_make_symbolic(&a[0], n * sizeof(num_t), gensym(a, __LINE__));
   
   copy(old_a, a, n * sizeof(num_t));
   
   int result = count_even(a, n) == sort_even(a, n);
 
   assert(result);   

   assert(sorted_even(a, n));

   assert(unchanged_odd(a, old_a, n));

   assert(same_elem(a, old_a, n));
}

#define COUNT_MAX 3

int main(int argc, char *argv[])
{
    verify_sort_even(0);
    verify_sort_even(1);
    verify_sort_even(COUNT_MAX / 2);
    verify_sort_even(COUNT_MAX);
    return 0;
}
#endif /* _KLEE_ */
