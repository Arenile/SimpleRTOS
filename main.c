#include "Task.h"

void howdy();
void dad_joke();
void kid_respond();

char* arg1 = "howdy from dad\n";
char* arg2 = "again\n";

int main (int argc, char **argv) {

    char** pArgs = malloc(sizeof(arg1)+sizeof(arg2));
    pArgs[0] = arg1;
    pArgs[1] = arg2;

    //printf("pargs = %s", pArgs);

    init_rtos();

    pTaskHandle dad_task = add_task("dad", &dad_joke, pArgs, 2);
    pTaskHandle howdy_task = add_task("howdy", &howdy, NULL, 0);
    pTaskHandle kid_task = add_task("kid", &kid_respond, NULL, 0);

    if (dad_task == NULL) {
        perror("FAILED TO ADD DAD TASK!");
        return 1;
    }
    if (howdy_task == NULL) {
        perror("FAILED TO ADD HOWDY TASK");
        return 1;
    }

    // if (delete_task(howdy_task) != 0) {
    //     perror("FAILED TO DELETE HOWDY TASK");
    //     return 1;
    // }

    start_scheduler();

    return 0;
}

void howdy(int argc, char** argv) {
    printf("argc = %d\n", argc);
    printf("Howdy partner!\n");
}

void dad_joke(int argc, char** argv) {
    printf("argc = %d\n", argc);
    for (int i = 0; i < argc; i++) {
        printf("%s", argv[i]);
    }
}

void kid_respond(int argc, char** argv) {
    printf("argc = %d\n", argc);
    printf("Yes?\n");
}