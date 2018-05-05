#ifndef PT_STRING_H
#define PT_STRING_H


#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>


// Types defined by this lib -- 

typedef char * string;

typedef struct {
    size_t length;
    size_t capacity;
} string_header;


// Functions provided by this lib --

string string_create(const char *cstr);
string string_copy(const string str);
void string_free(string str);

size_t string_length(const string str);

string string_set(string str, const char *cstr);
void string_clear(string str);

string string_append(string str, const string str2);
string string_append_cstring(string str, const char *cstr);
string string_append_format(string str, const char *fmt, ...);

bool string_equals(const string s1, const string s2);
bool string_equals_cstring(const string str, const char *cstr);

bool string_contains(const string str, const string str2);
bool string_contains_cstring(const string str, const char *cstr);

string string_substring(const string str, uint32_t start_idx, uint32_t end_idx);
// Future: string_index_of ?

#endif  // PT_STRING_H


#ifdef PT_STRING_IMPLEMENTATION

// "Private" Functions / Macros --

#define STRING_HEADER(s) ((string_header *)s - 1)

size_t static string_capacity(const string str)
{
    return STRING_HEADER(str)->capacity;
}

void string_set_capacity(const size_t capacity)
{
    STRING_HEADER(str)->capacity = capacity;
}

void string_set_length(const size_t length)
{
    STRING_HEADER(str)->length = length;
}


// Public interface functions --

string string_create(const char *cstr)
{
    // Allocate memory for our string + header
    size_t header_size = sizeof string_header;
    size_t len = strlen(cstr);
    size_t alloc_size = header_size + len + 1;

    void *p = malloc(alloc_size);
    if (p == NULL) {
        return p;
    }

    // Make sure we're dealing with a clean slate
    memset(p, 0, alloc_size);

    // Set up the string header
    string_header *hdr = ((string_header)p - 1);
    hdr->length = len;
    hdr->capacity = len;

    // Copy the given string into our new string
    
}

string string_copy(const string str)
{
}

void string_free(string str)
{
}

size_t string_length(const string str)
{
}

string string_set(string str, const char *cstr)
{
}

void string_clear(string str)
{
}

string string_append(string str, const string str2)
{
}

string string_append_cstring(string str, const char *cstr)
{
}

string string_append_format(string str, const char *fmt, ...)
{
}

bool string_equals(const string s1, const string s2)
{
}

bool string_equals_cstring(const string str, const char *cstr)
{
}

bool string_contains(const string str, const string str2)
{
}

bool string_contains_cstring(const string str, const char *cstr)
{
}

string string_substring(const string str, uint32_t start_idx, uint32_t end_idx)
{
}

#endif  // PT_STRING_IMPLEMENTATION



