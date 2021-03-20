#include "render.hpp"
#include "GLFW/glfw3.h"
#include "camera.hpp"
#include "obj_loader.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

#ifdef __linux__

static float prevMouseX, prevMouseY;

static const char vs_src[] = 
{
    "#version 330\n"
    "layout (location = 0) in vec3 inPos;\n"
    "layout (location = 1) in vec3 inCol;\n"
    "out vec3 vertCol;\n"
    "uniform mat4 projectionMat;\n"
    "uniform mat4 viewMat;\n"
    "uniform mat4 modelMat;\n"
    "void main()\n"
    "{\n"
    "    vertCol       = inCol;\n"
    "    vec4 modelPos = modelMat * vec4( inPos, 1.0 );\n"
    "    vec4 viewPos  = viewMat * modelPos;\n"
    "    gl_Position   = projectionMat * viewPos;\n"
    "}\n"
};

static const char fs_src[] = 
{
    "#version 400\n"
    "in vec3 vertCol;\n"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    fragColor = vec4( vertCol, 1.0 );\n"
    "}\n"
};

#endif /* linux */

#ifdef __APPLE__
static const char vs_src[] = 
{
    "#version 140\n"
    "layout (location = 0) in vec3 inPos;\n"
    "layout (location = 1) in vec3 inCol;\n"
    "out vec3 vertCol;\n"
    "uniform mat4 projectionMat;\n"
    "uniform mat4 viewMat;\n"
    "uniform mat4 modelMat;\n"
    "void main()\n"
    "{\n"
    "    vertCol       = inCol;\n"
    "    vec4 modelPos = modelMat * vec4( inPos, 1.0 );\n"
    "    vec4 viewPos  = viewMat * modelPos;\n"
    "    gl_Position   = projectionMat * viewPos;\n"
    "}\n"
};


static const char fs_src[] = 
{
    "#version 140\n"
    "in vec3 vertCol;\n"
    "\n"
    "out vec4 fragColor;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    fragColor = vec4( vertCol, 1.0 );\n"
    "}\n"
};
#endif /* APPLE */


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

  printf("%zd\n", file_size);

  fd = open(filename, O_RDONLY);
  if (fd == -1) {
      perror("open");
      return NULL;
  }

  p = (char*)mmap(0, (size_t)file_size, PROT_READ, MAP_SHARED, fd, 0);

  if (p == MAP_FAILED) {
      perror("mmap");
      return NULL;
  }

  (*len) = (size_t) file_size;

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

int LoadShader(const char *vs, const char *fs, GLuint program) {
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

    /* Load shaders */


    GLint result = GL_FALSE;
    int logLen;


    /* Compile vertex shader */
    glShaderSource(vertShader, 1, &vs, NULL);
    glCompileShader(vertShader);

    glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) /* Show error and surrender */
    {
        glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &logLen);

        char *ErrorLog = (char *) malloc((logLen + 1) * sizeof(char));


        glGetShaderInfoLog(vertShader, logLen, NULL, &ErrorLog[0]);


        return RENDER_VERTEX_SHADER_COMPILATION_ERR;

    }


    /* Compile fragment shader */
    glShaderSource(fragShader, 1, &fs, NULL);
    glCompileShader(fragShader);

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE) /* Show error and surrender */
    {
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLen);

        char *ErrorLog = (char *) malloc((logLen + 1) * sizeof(char));


        glGetShaderInfoLog(fragShader, logLen, NULL, &ErrorLog[0]);


        return RENDER_VERTEX_SHADER_COMPILATION_ERR;

    }

    /* Linking program */

    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);

    glGetProgramiv(program, GL_LINK_STATUS, &result);

    if (result == GL_FALSE) /* Show error and surrender */
    {
        glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &logLen);

        char *ErrorLog = (char *) malloc((logLen + 1) * sizeof(char));


        glGetShaderInfoLog(fragShader, logLen, NULL, &ErrorLog[0]);


        glDeleteShader(fragShader);
        glDeleteShader(vertShader);

        return RENDER_VERTEX_SHADER_COMPILATION_ERR;

    }

    return SUCCESS;
}

void draw(window_t &window) {
    mat4 perspective;
    mat4 view;
    cameraGetPerspective(window.cam, perspective);
    cameraLookAt(window.cam, view);
    setMat4(window.program, "projectionMat", perspective);
    setMat4(window.program, "viewMat", view);

    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glVertexPointer(3, GL_FLOAT, 36, (const void *) 0);
    glNormalPointer(GL_FLOAT, 36, (const void *)(sizeof(float) * 3));
    glColorPointer(3, GL_FLOAT, 36, (const void *)(sizeof(float) * 6));
    glDrawArrays(GL_TRIANGLES, 0, 3 * window.model.num); 

    CheckErrors("drawarrays");
}

int setMat4(GLuint program, const char *name, const mat4 &mat) {
    glUniformMatrix4fv(glGetUniformLocation(program, name), 1, GL_FALSE, &mat[0][0]);
    return SUCCESS;
}

int InitScene(window_t &window) {
    float bmin[3], bmax[3];
    window.program = glCreateProgram();
    LoadShader(vs_src, fs_src, window.program);
    loadModel();

    return SUCCESS; 
}

void CheckErrors(const char* desc) {
  GLenum e = glGetError();
  if (e != GL_NO_ERROR) {
    fprintf(stderr, "OpenGL error in \"%s\": %d (%d)\n", desc, e, e);
    exit(20);
  }
}
