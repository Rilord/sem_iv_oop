#ifndef STRING_
#define STRING_

struct string {
    char *data;
    unsigned int len;
};

using string_t = struct string;

string_t string_init(const char *str = nullptr, unsigned int n = 0);
int string_alloc(string_t &str, unsigned int n);
void string_free(string_t &str);

#endif // STRING_
