#ifndef ERRORS_H_
#define ERRORS_H_

#include <stdio.h>


#define SUCCESS 0
#define FAIL 1
#define WRONG_FILE 2
#define ALLOCATION_ERR 3
#define DATA_ERR 4
#define SHADER_ERR 5
#define WINDOW_ERR 6

void ErrorHandler(const int &code);

#endif /* ERRORS_H_ */
