#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 256
#define SUCCESS 1
#define FAILURE 0

#define PREV_NONE 0
#define PREV_CHAR 1
#define PREV_OP 2

#define LAST_OP_NONE 99
#define LAST_OP_PLUS_MINUS 1
#define LAST_OP_MULTI_DEVIDE 2

typedef int data_t;
data_t stack_data[STACK_SIZE];
int stack_index;

int push(data_t push_data) {
    if (stack_index < STACK_SIZE) {
        stack_data[stack_index] = push_data;
        stack_index++;
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

int pop(data_t *pop_data) {
    if (stack_index > 0) {
        stack_index--;
        *pop_data = stack_data[stack_index];
        return SUCCESS;
    } else {
        return FAILURE;
    }
}

int main(int argc, char *argv[]) {
    char *argstr = argv[1];
    int prev = PREV_NONE;
    int last_op = LAST_OP_NONE;
    int last_op_index;
    int open_brace = 0;
    int op_popped = 0;
    for (int i = 0; i < strlen(argstr); i++) {
        /* 40 ( カッコがあったら演算子の優先度を上げる */
        if (argstr[i] == 40) {
            open_brace += 10;
        }
        /* 41 ) カッコが閉じたら演算子の優先度を下げる */
        if (argstr[i] == 41) {
            open_brace -= 10;
        }
        /* 97 a, 122 z */
        if (argstr[i] >= 97 && argstr[i] <= 122) {
            if (op_popped == 1) {
                printf(" ");
            }
            printf("%c", argstr[i]);
            prev = PREV_CHAR;
        } 
        /* 42 *, 43 +, 45 -, 47 / */
        if (argstr[i] == 42 || argstr[i] == 43 || argstr[i] == 45 || argstr[i] == 47) {
            int current_op;
            if (argstr[i] == 43 || argstr[i] == 45) {
                current_op = LAST_OP_PLUS_MINUS + open_brace;
            } else {
                current_op = LAST_OP_MULTI_DEVIDE + open_brace;
            }

            /* 今の演算子の優先度が一つ前の演算子以下だったら、一つ前の演算子をスタックから下ろす */
            if (last_op != LAST_OP_NONE && current_op <= last_op) {
                data_t popped;
                pop(&popped);
                printf(" %c", popped);
                op_popped = 1;
            } else {
                op_popped = 0;
            }
            push(argstr[i]);
            prev = PREV_OP;
            last_op = current_op;
            last_op_index = stack_index;
        }
    }

    /* 全部読み終わったらスタックから下ろしていく */
    for (int i = stack_index; i > 0; i--) {
        data_t popped;
        pop(&popped);
        printf(" %c", popped);
    }

    printf("\n");
}
