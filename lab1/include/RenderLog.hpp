#ifndef RENDER_LOG_H_
#define RENDER_LOG_H_

#include <stdio.h>

#define RESET   "\033[0m"
#define RED "\033[31m"
#define YELLOW "\033[33m"
#define GREEN   "\033[32m"

#define ERR_FLAG RED "[ERROR]" RESET
#define WARNING_FLAG YELLOW "[WARNING]" RESET
#define PROCEED_FLAG GREEN "[ERROR]" RESET

typedef enum {
    LOG_ERROR,
    LOG_WARNING,
    LOG_PROCEED
} logFlag;

#define RenderError(msg) \
    fprintf(stderr, ERR_FLAG "[%17s] [%15s:%4d] %s\n", __FILE__, __func__, __LINE__, msg)

#define RenderWarn(msg) \
    fprintf(stderr, WARNING_FLAG "[%17s] [%15s:%4d] %s\n", __FILE__, __func__, __LINE__, msg)

#define RenderProceed(msg) \
    fprintf(stderr, PROCEED_FLAG "[%17s] [%15s:%4d] %s\n", __FILE__, __func__, __LINE__, msg)

#endif /* RENDER_LOG_H_ */
