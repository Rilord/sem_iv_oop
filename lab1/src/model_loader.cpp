#include "model_loader.hpp"
#include "errors.hpp"


static err_t parseLine(parsing_buffer &buf, string &p) {
    char linebuf[128]; 

    auto error = SUCCESS;

    assert(p.len < 127);

    memcpy(linebuf, p.str, p.len);

    if (parseFloat3(buf.v, linebuf)) {
        error = DATA_ERR;
    }

    return SUCCESS;
}


static err_t parseFloat3(vec3 &vertex, string &str) {
    if (sscanf(str.str, "%f %f %f", &vertex[0], &vertex[1], &vertex[2]) != 3) {
        return DATA_ERR;       
    }
    return SUCCESS;
}

err_t parseVertexFile(model_file &model_data, model_t &model) {

    FILE *f;
    ssize_t read;
    size_t len = 128;
    size_t vertices_num = 0;

    parsing_buffer buf;
    string line;

    f = fopen(model_data.filename, "r");

    if (f == NULL) 
        return WRONG_FILE;

    vertices_num = getVerticesNum(f);


    }

    return SUCCESS;
}

static size_t getVerticesNum(FILE *f) {

    size_t count_lines = 0;
    char chr = getc(f);

    while (chr != EOF) {
        if (chr == '\n') {
            count_lines++;
        }
        chr = getc(f);
    }

    fseek(f, 0, SEEK_SET);

    return count_lines;
}



