#include "render.hpp"
#include "tinyobj_loader_c.h"

#include <cstring>
#include <iostream>
#include <fstream>
#include <sys/mman.h>

static char* mmap_file(size_t* len, const char* filename) {
  FILE* f;
  long file_size;
  char* p;
  int fd;

  (*len) = 0;

  f = fopen(filename, "r");
  if (!f) {
    perror("open");
    return NULL;
  }
  fseek(f, 0, SEEK_END);
  file_size = ftell(f);
  fclose(f);


  p = (char*)mmap(0, (size_t)file_size, PROT_READ, MAP_SHARED, fd, 0);

  if (p == MAP_FAILED) {
    perror("mmap");
    return NULL;
  }


  (*len) = (size_t)file_size;

  return p;

}

static char* get_dirname(char* path) {
  char* last_delim = NULL;

  if (path == NULL) {
    return path;
  }

#if defined(_WIN32)
  /* TODO: Unix style path */
  last_delim = strrchr(path, '\\');
#else
  last_delim = strrchr(path, '/');
#endif

  if (last_delim == NULL) {
    /* no delimiter in the string. */
    return path;
  }

  /* remove '/' */
  last_delim[0] = '\0';

  return path;
}

static void getFileData(void *ctx, const char *filename, const int is_mtl,
        const char *obj_filename, char **data, size_t *len) {

    (void) ctx;

    if (!filename) {
        std::cout << ERR_FLAG << "no filename\n";
        (*data) = NULL;
        (*len) = 0;
        return;
    }

    const char *ext = strrchr(filename, '.');

    size_t data_len = 0;

    char *basedirname = NULL;

    char tmp[1024];

    tmp[0] = '\0';

    if (is_mtl && obj_filename) {
        basedirname = my_strdup(obj_filename, strlen(obj_filename));
        basedirname = get_dirname(basedirname);
    }

    strncat(tmp, filename, 1023 - strlen(tmp));
    tmp[strlen(tmp)] = '\0';

    printf("tmp = %s\n", tmp);

    if (basedirname) {
        free(basedirname);
    }


    *data = mmap_file(&data_len, tmp);


    (*len) = data_len;
}


int LoadShader(const char *vertex_path, const char *fragment_path, GLuint program) {
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    /* Load shaders */
    std::string vertShaderStr = readFile(vertex_path);
    std::string fragShaderStr = readFile(fragment_path);

    const char *vertShaderSrc = vertShaderStr.c_str();
    const char *fragShaderSrc = fragShaderStr.c_str();

    GLint result = GL_FALSE;
    int logLen;

    std::cout << PROCEED_FLAG << "Compiling vertex shader.\n";

    /* Compile vertex shader */
    glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
    glCompileShader(vertShader);

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) /* Show error and surrender */
    {
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLen);

        char *ErrorLog = (char *) malloc((logLen + 1) * sizeof(char));


        glGetShaderInfoLog(vertShader, logLen, NULL, &ErrorLog[0]);

        std::cout << ERR_FLAG << ErrorLog << "\n";

        return RENDER_VERTEX_SHADER_COMPILATION_ERR;

    }

    std::cout << PROCEED_FLAG << "Compiling fragment shader.\n";

    /* Compile fragment shader */
    glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) /* Show error and surrender */
    {
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLen);

        char *ErrorLog = (char *) malloc((logLen + 1) * sizeof(char));


        glGetShaderInfoLog(fragShader, logLen, NULL, &ErrorLog[0]);

        std::cout << ERR_FLAG << ErrorLog << "\n";

        return RENDER_VERTEX_SHADER_COMPILATION_ERR;

    }

    /* Linking program */

    std::cout << PROCEED_FLAG << "Linking program\n";

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (result == GL_FALSE) /* Show error and surrender */
    {
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLen);

        char *ErrorLog = (char *) malloc((logLen + 1) * sizeof(char));


        glGetShaderInfoLog(fragShader, logLen, NULL, &ErrorLog[0]);

        std::cout << ERR_FLAG << ErrorLog << "\n";

        glDeleteShader(fragShader);
        glDeleteShader(vertShader);

        return RENDER_VERTEX_SHADER_COMPILATION_ERR;

    }

    return SUCCESS;
}

int loadObj(const char *filePath) {

    tinyobj_attrib_t attrib;
    tinyobj_shape_t *shapes = NULL;
    size_t num_shapes;
    tinyobj_material_t *materials = NULL;
    size_t num_materials;

    unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;

    int rc = tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &materials, 
            &num_materials, filePath, getFileData, NULL, flags);

    if (rc != TINYOBJ_SUCCESS) {
        return 0;
    }

    std::cout << "number of shapes = " << (int) num_shapes << "\n";
    std::cout << "number of materials = " << (int) num_materials << "\n";

    DrawObject o;

    float *vb;

    size_t face_offset = 0;
    size_t i;

    size_t num_triangles = attrib.num_face_num_verts;

    size_t stride = 9;

    vb = (float *) malloc(sizeof(float) * stride * num_triangles * 3);

    if (vb == NULL)
        return 0;

    for (i = 0; i < attrib.num_face_num_verts; i++) {
        size_t f;

        for (f = 0; f < (size_t) attrib.face_num_verts[i] / 3; f++) {
            size_t k;
            float v[3][3];
            float n[3][3];
            float c[3];
            float len2;

            tinyobj_vertex_index_t idx0 = attrib.faces[face_offset + 3 * f + 0];
            tinyobj_vertex_index_t idx1 = attrib.faces[face_offset + 3 * f + 1];
            tinyobj_vertex_index_t idx2 = attrib.faces[face_offset + 3 * f + 2];

            for (k = 0; k < 3; k++) {
                int f0 = idx0.v_idx;
                int f1 = idx1.v_idx;
                int f2 = idx2.v_idx;

                v[0][k] = attrib.vertices[3 * (size_t) f0 + k];
                v[1][k] = attrib.vertices[3 * (size_t) f1 + k];
                v[2][k] = attrib.vertices[3 * (size_t) f2 + k];
            }
        }
    }



    return SUCCESS;
}
