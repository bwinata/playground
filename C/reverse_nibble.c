#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

uint64_t reverse_nibble (uint64_t input)
{
        uint8_t byte_length = sizeof (input), i = 0;
        uint64_t swapped = 0;

        for (i = 0; i < byte_length; i++) {
                uint8_t byte = input >> (8 * i);

                uint64_t swapped_byte = ((byte & 0x0F) << 4) | ((byte & 0xF0) >> 4);
                swapped = swapped | (swapped_byte << 8 * i);
        }
        return swapped;
}

// -----------------------------------------------------------------------------

uint64_t reverse_nibble2 (uint64_t input)
{
        char * byte = (char *)&input;
        uint8_t i = 0;

        for (i = 0; i < sizeof (input); i++) {
                *byte = (*byte & 0x0F) << 4 | (*byte & 0xF0) >> 4;
                byte++;
        }
        return input;
}

// -----------------------------------------------------------------------------

int main (void)
{
        assert (reverse_nibble (0xAF) == 0xFA);
        assert (reverse_nibble (0xFF) == 0xFF);
        assert (reverse_nibble (0xA0F0) == 0x0A0F);
        assert (reverse_nibble (0xBDFE) == 0xDBEF);

        assert (reverse_nibble2 (0xEF) == 0xFE);
        assert (reverse_nibble2 (0xAF) == 0xFA);
        assert (reverse_nibble2 (0xA0F0) == 0x0A0F);
        assert (reverse_nibble2 (0xBDFE) == 0xDBEF);
}
