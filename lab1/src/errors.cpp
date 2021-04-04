#include "errors.hpp"

void ErrorHandler(const int &code) {
    switch(code) {
        case WRONG_FILE: 
            fprintf(stderr, "Wrong File!");
            break;
        case ALLOCATION_ERR:
            fprintf(stderr, "Couldn't allocate memory!");
            break;
        case DATA_ERR:
            fprintf(stderr, "Wrong data in file!");
            break;
        case SHADER_ERR:
            fprintf(stderr, "Couldn't compile shader");
            break;
        case WINDOW_ERR:
            fprintf(stderr, "Couldn't initialize window");
            break;
        default:
            fprintf(stderr, "Unknows command!");

    }
}
