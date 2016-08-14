#include <klee/klee.h>
#include <assert.h>
int main(int argc, char *argv[])
{
    int x;
    klee_make_symbolic(&x, sizeof(x), "x");
    return 1 / (x * x - 2 * x + 1);
}
