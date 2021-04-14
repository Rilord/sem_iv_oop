#include "my_string.h"
#include "errors.h"
#include <cstring>

string_t string_init(const char *str, unsigned int n) {
    string_t tmp; 

    strncpy(tmp.data, str, n);
    tmp.len = n;

    return tmp;
}

int string_alloc(string_t &str, unsigned int n) {
    str.data = new char[n + 1];

    if (str.data != nullptr) {
        str.len = n;
        return SUCCESS;
    }

    return ALLOC_ERROR;
    
}

void string_free(string_t &str) {
    delete str.data;
    str.data = nullptr;
    str.len = 0;
}
