#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>


// -----------------------------------------------------------------------------
// -- Public Functions
// -----------------------------------------------------------------------------

char * Strstr (char * haystack, char * needle)
{
        if (haystack == NULL) { return NULL;     }
        if (needle   == NULL) { return haystack; }

        unsigned int haystack_len = strlen (haystack);
        unsigned int needle_len   = strlen (needle);

        unsigned int i = 0, j = 0;

        for (i = 0; i < haystack_len; i++) {
                if (haystack[i] == needle[0]) {
                        for (j = 0; j < needle_len; j++) {
                                if (haystack[i + j] == needle[j]) {
                                        if (j == strlen (needle)-1) return &haystack[i];
                                } else break;
                        }
                }
        }
        return NULL;
}

// -----------------------------------------------------------------------------

char * Strstr2 (char * haystack, char * needle)
{
        if (haystack == NULL) { return NULL; }
        if (needle   == NULL) { return haystack; }

        char * haystack_ptr = haystack;
        char * needle_ptr   = needle;

        while (haystack_ptr != NULL) {
                if (*haystack_ptr == *needle) {
                        char * temp_ptr = haystack_ptr;
                        while (needle_ptr != NULL) {
                                if (*temp_ptr == *needle_ptr) {
                                        temp_ptr++;
                                        needle_ptr++;
                                        if (*temp_ptr == 0 && *needle_ptr == 0)
                                                return haystack_ptr;
                                } else {
                                        needle_ptr = needle;
                                        break;
                                }
                        }
                }
                haystack_ptr++;
        }
        return NULL;
}

// -----------------------------------------------------------------------------

int main (void)
{
        char * haystack = "Hello World";
        char * needle   = "World";

        assert (Strstr (NULL, NULL) == NULL);
        assert (Strstr (haystack, NULL) == haystack);
        assert (Strstr (haystack, needle) == &haystack[6]);

        assert (Strstr2 (NULL, NULL) == NULL);
        assert (Strstr2 (haystack, NULL) == haystack);
        assert (Strstr2 (haystack, needle) == &haystack[6]);
}
