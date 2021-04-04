#include "model_loader.hpp"
#include "errors.hpp"


static int parseLine(model_t &model, string &p) {
    char str[32], type;
    vec3 VertexBuf;
    vec3i IndexBuf;

    auto error = SUCCESS;

    string linebuf { str, 32 };

    memcpy(linebuf.str, p.str, p.len);

    type = linebuf.str[0];

    switch(type) {
        case 'v':
            if (parseFloat3(VertexBuf, linebuf)) {
                error = DATA_ERR;
                }
            setVertex(model, VertexBuf);
            break;
        case 'f':
            if (parseInt3(IndexBuf, linebuf)) {
                error = DATA_ERR;
            }
            setFace(model, IndexBuf);
            break;
        default:
            error = DATA_ERR;  
            break;
    }
    
    return error;
}

static int parseFloat3(vec3 &vertex, string &str) {
    if (sscanf(str.str + VALUES_OFFSET, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2]) != 3) {
        return DATA_ERR;       
    }
    return SUCCESS;
}

static int parseInt3(vec3i &vertex, string &str) {
    if (sscanf(str.str + VALUES_OFFSET, "%d %d %d\n", &vertex[0], &vertex[1], &vertex[2]) != 3) {
        return DATA_ERR;       
    }
    return SUCCESS;
}

int parseVertexFile(model_t &model, string &file) {

    auto error = SUCCESS;
    FILE *f;
    ssize_t read;
    size_t len = 32;
    size_t vertices_num = 0;

    vec3 buf;
    string line;

    f = fopen(file.str, "r");

    if (f == NULL) 
        return WRONG_FILE;

    if ((error = prepareData(model, f)) != SUCCESS) {
        return 
    }

    while (getline(&line.str, &line.len, f)) {
        error = parseLine(model, line);
        if (error != SUCCESS)
            break;
    }

    fclose(f);

    return error;
}

static int prepareData(model_t &model, FILE *f) {
    int error = SUCCESS;
    unsigned int v_count = 0;
    unsigned int f_count = 0;
    char chr = getc(f);

    while (chr != EOF) {
        if (chr == 'v')
            v_count++;
        if (chr == 'f')
            f_count++;
        chr = getc(f);
    }

    if (!v_count || !f_count)
        return DATA_ERR;

    model.vertices = new vec3[v_count];
    model.vert_num = v_count;
    model.indices = new int[f_count * 3];
    model.indices_num = f_count;

    fseek(f, 0, SEEK_SET);

    return error;
}

