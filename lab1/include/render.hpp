#ifndef RENDER_H_
#define RENDER_H_

#define TINYOBJ_LOADER_C_IMPLEMENTATION
#define RESET   "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN   "\033[32m"

#define ERR_FLAG RED << "[ERROR]" << RESET
#define WARNING_FLAG YELLOW << "[WARNING]" << RESET
#define PROCEED_FLAG GREEN << "[ERROR]" << RESET

#define SUCCESS (0x00)

#define RENDER_FILE_READ_ERR (0x03)
#define RENDER_VERTEX_SHADER_COMPILATION_ERR (0x04)
#define RENDER_FRAGMENT_SHADER_COMPILATION_ERR (0x05)
#define RENDER_LINLKING_ERR (0x06)

#include "tinyobj_loader_c.h"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <string>

typedef struct {
    GLuint vb;
    int num;
} DrawObject;

#ifdef __linux__
static const char * vs_src[] = 
{
    "#version 330\n"
    "layout (location = 0) in vec3 inPos;\n"
    "layout (location = 1) in vec3 inCol;\n"
    "out vec3 vertCol;\n"
    "uniform mat4 u_projectionMat44;\n"
    "uniform mat4 u_viewMat44;\n"
    "uniform mat4 u_modelMat44;\n"
    "void main()\n"
    "{\n"
    "    vertCol       = inCol;\n"
    "    vec4 modelPos = u_modelMat44 * vec4( inPos, 1.0 );\n"
    "    vec4 viewPos  = u_viewMat44 * modelPos;\n"
    "    gl_Position   = u_projectionMat44 * viewPos;\n"
    "}\n"
};

static const char * fs_src[] = 
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
static const char * vs_src[] = 
{
    "#version 150\n"
    "layout (location = 0) in vec3 inPos;\n"
    "layout (location = 1) in vec3 inCol;\n"
    "out vec3 vertCol;\n"
    "uniform mat4 u_projectionMat44;\n"
    "uniform mat4 u_viewMat44;\n"
    "uniform mat4 u_modelMat44;\n"
    "void main()\n"
    "{\n"
    "    vertCol       = inCol;\n"
    "    vec4 modelPos = u_modelMat44 * vec4( inPos, 1.0 );\n"
    "    vec4 viewPos  = u_viewMat44 * modelPos;\n"
    "    gl_Position   = u_projectionMat44 * viewPos;\n"
    "}\n"
};


static const char * fs_src[] = 
{
    "#version 150\n"
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


std::string readFile(const char *filePath);

int LoadShader(const char *vertex_path, const char *fragment_path);

int loadObj(const char *filePath);

int draw(DrawObject &obj);


#endif /* RENDER_H_ */
