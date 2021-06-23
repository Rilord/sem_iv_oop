#include "model_loader.h"
#include "edge_array.h"
#include "errors.h"
#include "model.h"
#include "vertex_array.h"
#include "vertex_loader.h"
#include "edge_loader.h"

int read_center(vec3& d, FILE* file) {
    if (fscanf(file, "%lf %lf %lf", &d.x, &d.y, &d.z) != 3)
        return WRONG_CENTER;

    return SUCCESS;
}

int scan_model(model_t& model, FILE* file) {
    vertex_array_t dots = vertex_array_init();

    int res = scan_vertices(dots, file);

    if (res)
        return res;

    face_array_t faces = face_array_init();

    if ((res = get_faces(faces, file))) {
        vertex_array_free(dots);
        return res;
    }

    vec3 center;


    if ((res = read_center(center, file))) {
        vertex_array_free(dots);
        face_array_free(faces);
        return res; 
    }

    model = model_init(&dots, &faces);

    set_center(model, center);

    return res;
}

int scan_file(model_t& model, const char* filename) {
    FILE* f = fopen(filename, "r");

    if (f == NULL) {
        return READ_ERROR;
    }

    model_t temp_model = model_init();
    int res = scan_model(temp_model, f);
    fclose(f);

    if (!res) {
        model_free(model);
        model = temp_model;
    }

    return res;
}

static int dump_dots(const model_t& model, FILE* file) {
    vertex_array_t va = get_vertex_arr((model_t&)model);
    unsigned int ndots = vertex_array_len(va);

    if (ndots) {
        fprintf(file, "%u\n", ndots);
        for (unsigned int i = 0; i < ndots; i++) {
            vec3 dot = get_dot(va, i);
            fprintf(file, "%lf %lf %lf\n", dot.x, dot.y, dot.z);
        }
    }

    fprintf(file, "\n");

    return SUCCESS;
}

static int dump_edges(const model_t& model, FILE* file) {
    face_array_t fa = get_face_arr((model_t&)model);
    unsigned int nedges = face_array_len(fa);

    if (nedges) {
        fprintf(file, "%u\n", nedges);

        for (unsigned int i = 0; i < nedges; i++) {
            face face = get_face(fa, i);
            fprintf(file, "%d %d %d\n", face.i1, face.i2, face.i3);
        }
    }

    fprintf(file, "\n");

    return SUCCESS;
}

static int dump_center(const model_t& model, FILE* file) {
    vec3 center = model.center;

    fprintf(file, "%lf %lf %lf\n", center.x, center.y, center.z);

    return SUCCESS;
}

int save_to_file(const model_t& model, const char* filename) {
    FILE* f = fopen(filename, "w");

    if (f == NULL) {
        return WRITE_ERROR;
    }

    dump_dots(model, f);
    dump_edges(model, f);
    dump_center(model, f);

    fclose(f);

    return SUCCESS;
}
