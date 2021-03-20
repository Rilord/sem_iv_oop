#ifndef RENDER_H_
#define RENDER_H_

#define SUCCESS (0x00)

#define RENDER_FILE_READ_ERR (0x03)
#define RENDER_VERTEX_SHADER_COMPILATION_ERR (0x04)
#define RENDER_FRAGMENT_SHADER_COMPILATION_ERR (0x05)
#define RENDER_LINLKING_ERR (0x06)

#include "obj_loader.hpp"
#include "window.hpp"
#include "camera.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

void build_rotmatrix(float m[4][4], const float q[4]);

typedef struct {
    GLuint vb;
    int num;
} DrawObject;


typedef struct window{
    GLFWwindow *window;
    camera_t cam;
    DrawObject model;
    void (*draw) (struct window &window);
    GLuint program;
} window_t;

int startWindowContext(const int width, const int height, window_t &window);

int runGLEW();

int initImGui(window_t &window);

void runLoop(window_t &window);

void setCallbacks(window_t &window);






const char *readFile(const char *filePath);

int LoadShader(const char *vs, const char *fs, GLuint program);

int loadObj(const char *filePath);


void setupModel(DrawObject &obj);

void draw(DrawObject &obj, camera_t &cam, window_t &window);

int setMat4(GLuint program, const char *name, const mat4 &mat);

void getFileData(void *ctx, const char *filename,
        const char *obj_filename, char **data, size_t *len);

int parse_obj_raw(obj_attrib_t &attrib, obj_shape_t **shapes, size_t &num_shapes, const char *filename);

int InitScene(window_t &window);

void CheckErrors(const char* desc);


#endif /* RENDER_H_ */
