#include "errors.h"
#include <stdio.h>

void error_manager(int errnum) {
    switch (errnum) {
    case READ_ERROR:
        printf("Ошибка \nПроизошла ошибка при чтении файла.");
        break;

    case ALLOC_ERROR:
        printf("Ошибка \nПроизошла ошибка при выделении.");
        break;

    case WRITE_ERROR:
        printf(NULL, "Ошибка",
                              "Произошла ошибка записи в файл.");
        break;

    case WRONG_VERTICES_NUM:
        printf(NULL, "Ошибка",
                              "Введенно неправильное кол-во точек.");
        break;

    case WRONG_FACES_NUM:
        printf(NULL, "Ошибка",
                              "Введенно неправильное кол-во ребер.");
        break;

    case WRONG_VERTICES:
        printf(
            NULL, "Ошибка",
            "Точки должны быть заданы действительными числами.");
        break;

    case WRONG_FACES:
        printf(NULL, "Ошибка",
                              "Связи должны быть заданы целыми числами.");
        break;

    case WRONG_CENTER:
        printf(
            NULL, "Ошибка", "Центр должен быть задан действительными числами.");
        break;
    }
}
