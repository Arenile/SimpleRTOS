#include "Task.h"

void** taskList;
uint8_t taskCount;

void init_rtos(void) {
    taskCount = 0;
}

/* Interface for adding a task to the schedule. 
 * This returns a pointer to the task handle.
 * Your task should provide a function implementation at
 * a minimum of the form "func(int argc, char** argv)"
*/
pTaskHandle add_task(char* name, void (*task)(int, char**), char** args, int argc) {
    pTaskHandle new_task = malloc(sizeof(TaskHandle));
    if (task != NULL) {
        void** newList = realloc(taskList, sizeof(pTaskHandle)*(taskCount +1));
        taskList = newList;

        new_task->id = taskCount;
        new_task->name = name;
        new_task->task = task;
        new_task->args = args;
        new_task->argc = argc;

        taskList[taskCount] = new_task;
        taskCount++;

        return new_task;
    }
    return NULL;
}

int delete_task(pTaskHandle del_task) {
    if (del_task != NULL) {
        uint8_t del_id = del_task->id;

        free(taskList[del_id]);

        void** newList = realloc(taskList, sizeof(pTaskHandle)*(--taskCount));
        taskList = newList;

        /* Note the most efficient way to do this, but
         * it will work for fixing the list for now
        */
        for (int i = del_id; i < taskCount; i++) {
            if (taskList[i] != NULL) {
                ((pTaskHandle)taskList[i])->id = i;
            }
        }

        return 0;
    }
    else {
        return 1;
    }
}

void start_scheduler() {
    while(1){
        for (int i = 0; i < taskCount; i++) {
            printf( "Running task = %s\n", 
                    ((pTaskHandle)taskList[i])->name
                    );

            (((pTaskHandle)taskList[i])->task)(((pTaskHandle)taskList[i])->argc, ((pTaskHandle)taskList[i])->args);

        }
    sleep(1); // Sleep 1 second
    }
}