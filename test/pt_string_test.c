#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define PT_STRING_IMPLEMENTATION
#include "../src/shared/pt_string.h"

int main() {
    string s1 = string_create("TEST");
    string s2 = string_copy(s1);
    assert(string_equals(s1, s2));
    assert(string_equals_cstring(s1, "TEST"));

    s1 = string_append(s1, s2);
    assert(string_equals_cstring(s1, "TESTTEST"));

    assert(string_length(s2) == 4);
    string_clear(s2);
    assert(string_length(s2) == 0);
    s2 = string_set(s2, "This is a test");

    string s3 = string_create("123456789012345");
    assert(string_length(s3) == 15);
    assert(string_capacity(s3) == 15);
    s3 = string_append_cstring(s3, "1234567890");
    assert(string_length(s3) == 25);
    assert(string_capacity(s3) == 25);
    s3 = string_set(s3, "12345");
    assert(string_length(s3) == 5);
    assert(string_capacity(s3) == 25);
    
    string s4 = string_create("567");
    assert(string_contains(s3, s4));
    assert(string_contains_cstring(s3, "789"));
    assert(string_contains(s3, s1) == false);
    assert(string_contains_cstring(s3, "321") == false);

    string s5 = string_substring(s2, 8, string_length(s2) - 1);
    assert(string_equals_cstring(s5, "a test"));

    string s6 = string_create("Hello!");
    s6 = string_append_format(s6, " %s: %s. It will last %d ms", s1, s2, 13);

    printf("String with formatted appends: %s", s6);

    printf("All pt_string tests PASS!");
}


