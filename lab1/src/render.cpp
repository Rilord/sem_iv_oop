#include "render.hpp"
#include "GLFW/glfw3.h"
#include "camera.hpp"
#include "obj_loader.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <math.h>



const char *readFile(const char *filePath) {
    char *buf = 0;
    size_t len;
    FILE *f = fopen(filePath, "r");

    if (!f)
        return NULL;

    fseek(f, 0, SEEK_END);
    len = ftell(f);
    fseek(f, 0, SEEK_SET);
    buf = (char *) malloc(len);

    if (!buf) 
        return NULL;

    fread(buf, 1, len, f);
    return buf;
}

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

  last_delim = strrchr(path, '/');

  if (last_delim == NULL) {
    /* no delimiter in the string. */
    return path;
  }

  /* remove '/' */
  last_delim[0] = '\0';

  return path;
}

static void getNormalToPlane(vec3f N, vec3f v0, vec3f v1, vec3f v2) {
    float v10[3];
    float v20[3];
    float len2;

    v10[0] = v1[0] - v0[0];
    v10[1] = v1[1] - v0[1];
    v10[2] = v1[2] - v0[2];

    v20[0] = v2[0] - v0[0];
    v20[1] = v2[1] - v0[1];
    v20[2] = v2[2] - v0[2];

    N[0] = v20[1] * v10[2] - v20[2] * v10[1];
    N[1] = v20[2] * v10[0] - v20[0] * v10[2];
    N[0] = v20[0] * v10[1] - v20[1] * v10[0];

    len2 = N[0] * N[0] + N[1] * N[1] + N[2] * N[2];

    if (len2 > 0.0f) {
        float len = (float) sqrt((double) len2);

        N[0] /= len;
        N[1] /= len;
    }


}



int LoadShader(const char *vertex_path, const char *fragment_path, GLuint program) {
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    /* Load shaders */

    const char *vertShaderSrc = readFile(vertex_path);
    const char *fragShaderSrc = readFile(fragment_path);

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

void getFileData(void* ctx, const char* filename,
                          const char* obj_filename, char** data, size_t* len) {
  (void)ctx;

  if (!filename) {
    fprintf(stderr, "null filename\n");
    (*data) = NULL;
    (*len) = 0;
    return;
  }

  const char* ext = strrchr(filename, '.');

  size_t data_len = 0;

  if (strcmp(ext, ".gz") == 0) {
    assert(0); /* todo */

  } else {
    char* basedirname = NULL;

    char tmp[1024];
    tmp[0] = '\0';

    /* For .mtl, extract base directory path from .obj filename and append .mtl
     * filename */

    if (basedirname) {
      strncpy(tmp, basedirname, strlen(basedirname));

#if defined(_WIN32)
      strncat(tmp, "/", 1023 - strlen(tmp));
#else
      strncat(tmp, "/", 1023 - strlen(tmp));
#endif
      strncat(tmp, filename, 1023 - strlen(tmp));
      tmp[strlen(tmp)] = '\0';
    } else {
      strncpy(tmp, filename, strlen(filename));
      tmp[strlen(tmp)] = '\0';
    }

    printf("tmp = %s\n", tmp);

    if (basedirname) {
      free(basedirname);
    }

    *data = mmap_file(&data_len, tmp);
  }

  (*len) = data_len;
}

int parse_obj_raw(obj_attrib_t &attrib, obj_shape_t **shapes, size_t &num_shapes, const char *filename) {
    int rc = obj_parse_obj(attrib, shapes, num_shapes, filename, getFileData, NULL, OBJ_FLAG_TRIANGULATE);

    if (rc != OBJ_SUCCESS) {
        return -1;
    }
    return SUCCESS; 
}

int loadObj(DrawObject &model, const char *filePath, float bmin[3], float bmax[3]) {

    obj_attrib_t attrib;
    obj_shape_t *shapes = NULL;
    size_t num_shapes;
    size_t num_materials;
    
    if (parse_obj_raw(attrib, &shapes, num_shapes, filePath))
        return -1;



    std::cout << "number of shapes = " << (int) num_shapes << "\n";
    std::cout << "number of materials = " << (int) num_materials << "\n";

    bmin[0] = bmin[1] = bmin[2] = FLT_MAX;
    bmax[0] = bmax[1] = bmax[2] = -FLT_MAX;
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

            obj_vertex_index_t idx0 = attrib.faces[face_offset + 3 * f + 0];
            obj_vertex_index_t idx1 = attrib.faces[face_offset + 3 * f + 1];
            obj_vertex_index_t idx2 = attrib.faces[face_offset + 3 * f + 2];

            for (k = 0; k < 3; k++) {
                int f0 = idx0.v_idx;
                int f1 = idx1.v_idx;
                int f2 = idx2.v_idx;

                v[0][k] = attrib.vertices[3 * (size_t) f0 + k];
                v[1][k] = attrib.vertices[3 * (size_t) f1 + k];
                v[2][k] = attrib.vertices[3 * (size_t) f2 + k];
                bmin[k] = (v[0][k] < bmin[k]) ? v[0][k] : bmin[k];
                bmin[k] = (v[1][k] < bmin[k]) ? v[1][k] : bmin[k];
                bmin[k] = (v[2][k] < bmin[k]) ? v[2][k] : bmin[k];
                bmax[k] = (v[0][k] < bmax[k]) ? v[0][k] : bmax[k];
                bmax[k] = (v[1][k] < bmax[k]) ? v[1][k] : bmax[k];
                bmax[k] = (v[2][k] < bmax[k]) ? v[2][k] : bmax[k];
            }

            if (attrib.num_normals > 0) {
                int f0 = idx0.vn_idx;
                int f1 = idx1.vn_idx;
                int f2 = idx2.vn_idx;

                if (f0 >= 0 && f1 >= 0 && f2 >= 0) {
                    for (k = 0; k < 3; k++) {
                        n[0][k] = attrib.normals[3 * (size_t) f0 + k];
                        n[1][k] = attrib.normals[3 * (size_t) f1 + k];
                        n[2][k] = attrib.normals[3 * (size_t) f2 + k];
                    }
                } else {
                    getNormalToPlane(n[0], v[0], v[1], v[2]);
                    n[1][0] = n[0][0];
                    n[1][1] = n[0][1];
                    n[1][2] = n[0][2];
                    n[2][0] = n[0][0];
                    n[2][1] = n[0][1];
                    n[2][2] = n[0][2];
                }

                for (k = 0; k < 3; k++) {
                    vb[(3 * i + k) * stride + 0] = v[k][0];
                    vb[(3 * i + k) * stride + 1] = v[k][1];
                    vb[(3 * i + k) * stride + 2] = v[k][2];
                    vb[(3 * i + k) * stride + 3] = n[k][0];
                    vb[(3 * i + k) * stride + 4] = n[k][1];
                    vb[(3 * i + k) * stride + 5] = n[k][2];

                    c[0] = n[k][0];
                    c[1] = n[k][1];
                    c[2] = n[k][2];
                    len2 = c[0] * c[0] + c[1] * c[1] + c[2] * c[2];

                    if (len2 > 0.0f) {
                        float len = (float) sqrt((double) len2);

                        c[0] /= len;
                        c[1] /= len;
                        c[2] /= len;
                    }

                    vb[(3 * i + k) * stride + 6] = (c[0] * 0.5f + 0.5f);
                    vb[(3 * i + k) * stride + 7] = (c[1] * 0.5f + 0.5f);
                    vb[(3 * i + k) * stride + 8] = (c[2] * 0.5f + 0.5f);
                }
            }

            face_offset += (size_t) attrib.face_num_verts[i];
        }

        o.vb = 0;

        o.num = 0;

        if (num_triangles > 0) {
            glGenBuffers(1, &o.vb);
            glBindBuffer(GL_ARRAY_BUFFER, o.vb);
            glBufferData(GL_ARRAY_BUFFER,
                    (GLsizeiptr) (num_triangles * 
                        3 * stride * sizeof(float)), 
                    vb, GL_STATIC_DRAW);
            o.num = (int) num_triangles;
        }

        model = o;

        free(vb);

    }

    obj_attrib_free(attrib); 
    obj_shapes_free(shapes, num_shapes);

    return SUCCESS;
}

void draw(DrawObject &obj, camera_t &cam, GLFWwindow &window) {
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glVertexPointer(3, GL_FLOAT, 36, (const void *) 0);
    glNormalPointer(GL_FLOAT, 36, (const void *)(sizeof(float) * 3));
    glColorPointer(3, GL_FLOAT, 36, (const void *)(sizeof(float) * 6));
    glDrawArrays(GL_TRIANGLES, 0, 3 * obj.num); 
}
