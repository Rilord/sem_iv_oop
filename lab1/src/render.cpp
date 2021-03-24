#include "render.hpp"




void setMat4(GLuint uniformLocation, 
        const mat4 &mat) {
    glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, &mat[0][0]);
}

