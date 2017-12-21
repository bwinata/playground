#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

uint32_t fibonacci (uint32_t value)
{
        // Fib (n) = Fib (n-1) + Fib (n-2)
        if (value <= 1) return 1;

        uint32_t a = fibonacci (value - 1);
        uint32_t b = fibonacci (value - 2);

        return a + b;
}

void stack_frame (int8_t value)
{
        // Count down and preserve each value in own stack stack_frame
        if (value == 0) return;

        int8_t v = value;
        stack_frame (value - 1);

        printf ("%d\n", v);
}

int main (void)
{
        assert (fibonacci (5) == 8);
        assert (fibonacci (6) == 13);

        stack_frame (8);
}
