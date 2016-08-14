#include <klee/klee.h>
#include <assert.h>
int main(int argc, char *argv[])
{
    int x;
    klee_make_symbolic(&x, sizeof(x), "x");
    assert(0 != x * x - 2 * x + 1);
    return 0;
}
