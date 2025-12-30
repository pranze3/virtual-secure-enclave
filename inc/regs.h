#ifndef REGS_H
#define REGS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif    

    void hw_init();

    void hw_write_reg(uint32_t addr, uint32_t data);

    uint32_t hw_read_reg(uint32_t addr);
    
#ifdef __cplusplus
}
#endif

#endif
