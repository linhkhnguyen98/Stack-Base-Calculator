#include <stdio.h>
#include <stdlib.h>

#include "operate.h"
#include "instruction.h"
#include "stack.h"
#include "operate.h"

/// operate on the instruction pointed by inst which is located at the given pc.  Return
/// the new PC or -1 if there was an error
///
/// errors may include:
///   insufficent operands on the stack
///   unrecognized instruction.
int operate(int pc, instr_t* inst) {
    //instr_t *inst;
    // pointer inst points to opcode (int)
    int v;
    switch (inst->opcode) {
        case PUSH: /* perform push expression */
            push(inst->operand);
            pc++;
            break;
        case POP: /* perform pop expression */
            if (check_stack(1, pc) == -1)
                pc = -1;
            else {
                int val;
                if (!pop(&val))
                    pc = -1;
                else
                    pc++;
            }
            break;
            /* add other instru1
            ction handling here. */
        case SWAP:
            if (check_stack(2, pc) == -1)
                pc = -1;
            else {
                int v1, v2;
                if (!pop(&v1) || !pop(&v2))
                    pc = -1;
                else {
                    push(v1);
                    push(v2);
                    pc++;
                }
            }
            break;
        case ROT:
            if (check_stack(2, pc) == -1)
                pc = -1;
            else {
                rot();
                pc++;
            }
            break; 
        case DUP:
            if (check_stack(1, pc) == -1)
                pc = -1;
            else {
                int val;
                if (!pop(&val))
                    pc = -1;
                else {
                    push(val);
                    push(val);
                    pc++;
                }
            }
            break;
        case GET:
            scanf("%d", &v);
            push(v);
            pc++;
            break;
        case PRINT:
            if (check_stack(1, pc) == -1)
                pc = -1;
            else {
                int val;
                if (!pop(&val))
                    pc = -1;
                else {
                    printf("%d\n", val);
                    push(val);
                    pc++;
                }
            }
            break;
        case PRINTSTACK:
            if (check_stack(1, pc) == -1)
                pc = -1;
            else {
                printstack();
                pc++;
            }
            break;
        case BTRUE:
            if (check_stack(1, pc) == -1)
                pc = -1;
            else {
                int x;
                if (!pop(&x))
                    pc = -1;
                else {
                    if (x != 0)
                        pc += inst->operand;
                    else
                        pc++;
                }
            }
            break;
        case CMPI:
            if (check_stack(1, pc) == -1)
                pc = -1;
            else {
                int x;
                if (!pop(&x))
                    pc = -1;
                else {
                    push(x);
                    if (x == inst->operand)
                        push(1);
                    else
                        push(0);
                    pc++;
                }
            }
            break;
        case HALT:
            pc = -1;
            break;
        case ADD:
            if (check_stack(2, pc) == -1)
                pc = -1;
            else {
                int x, y;
                if (!pop(&x) || !pop(&y))
                    pc = -1;
                else {
                    push(x + y);
                    pc++;
                }
            }
            break;
        case SUB:
            if (check_stack(2, pc) == -1)
                pc = -1;
            else {
                int x,y;
                if (!pop(&x) || !pop(&y))
                    pc = -1;
                else {
                    push(y - x);
                    pc++;
                }
            }
            break;
        case MULT:
            if (check_stack(2, pc) == -1)
                pc = -1;
            else {
                int x,y;
                if (!pop(&x) || !pop(&y))
                    pc = -1;
                else {
                    push(y * x);
                    pc++;
                }
            }
            break;
        case NOT:
            if (check_stack(1, pc) == -1)
                pc = -1;
            else {
                int x;
                if (!pop(&x))
                    pc = -1;
                else {
                    push(!x);
                    pc++;
                }
            }
            break;
        default:
            fprintf(stderr, "Illegal opcode 0x%04x at pc %04d\n", inst->opcode, pc);
            exit(EXIT_FAILURE);
    }
    return pc;
}

int check_stack(unsigned int x, int pc) {
    if (get_stack_size() < x)
        return -1;
    else
        return pc;
}
