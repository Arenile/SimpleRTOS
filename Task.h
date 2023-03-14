#ifndef TASK_H

#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <unistd.h>

enum TASK_ADD_RESULT {
    SUCCESS, 
    FAIL
} typedef RESULT;

struct Task {
    uint8_t id;
    char* name;
    void (*task)(int, char**);
    char** args;
    int argc;
} typedef TaskHandle, *pTaskHandle;

void start_scheduler();
pTaskHandle add_task(char* name, void (*task)(int, char**), char** args, int argc);
int delete_task(pTaskHandle del_task);
void init_rtos();

#endif