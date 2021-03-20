#ifndef ERRORS_H_
#define ERRORS_H_

enum err_t {
    SUCCESS,
    WRONG_FILE,
    ALLOCATION_ERR,
    DATA_ERR
};

void ErrorHandler(const err_t &code);

#endif /* ERRORS_H_ */
