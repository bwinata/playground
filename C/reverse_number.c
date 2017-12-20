#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

uint32_t reverse_num (uint32_t num)
{
        uint32_t rev = 0;

        while (num != 0) {
                int digit = num % 10;
                num /= 10;

                rev = (rev * 10) + digit;
        }
        return rev;
}

int main (void)
{
        assert (reverse_num (52) == 25);
        assert (reverse_num (78) == 87);
        assert (reverse_num (100) == 1);
        assert (reverse_num (243) == 342);
        assert (reverse_num (5) == 5);
        assert (reverse_num (0) == 0);
        assert (reverse_num (5243) == 3425);
        assert (reverse_num (32195) == 59123);

}
