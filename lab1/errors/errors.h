#ifndef ERRORS_
#define ERRORS_

#define SUCCESS 0
#define ALLOC_ERROR 1
#define READ_ERROR 2
#define WRITE_ERROR 3
#define LOADED 4
#define WRONG_FACES_NUM 5
#define MOVE_ERROR 6
#define ROTATION_ERROR 7
#define SCALING_ERROR 8
#define WRONG_VERTICES_NUM 9
#define WRONG_VERTICES 10
#define WRONG_FACES 11
#define WRONG_CENTER 12

void error_manager(int err);

#endif // ERRORS_
