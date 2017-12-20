#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef enum _bool_ {
        false = 0,
        true  = 1
}bool;

// -----------------------------------------------------------------------------

bool is_perfect_square (unsigned int value)
{
        unsigned int i = 0;
        unsigned int square = 0;

        do {
                square = (i*i);
                if (square == value) return true;
                i++;

        } while (square <= value);

        return false;
}

int main (void)
{

        assert (is_perfect_square (0) == true);
        assert (is_perfect_square (2) == false);
        assert (is_perfect_square (4) == true);
}
