#include <stdio.h>
#include "regs.h"

int main() {
    //initializing hw_model 
    hw_init();

    //writing to a reg and reading value into variable (simple test 1)
    hw_write_reg(0x20, 0x1234);
    uint32_t read_value = hw_read_reg(0x20);

    //checking test case
    if (read_value == 0x1234) {
        printf("PASS!\n");
    } else {
        printf("FAIL!\n");
    }
    return 0;
}

