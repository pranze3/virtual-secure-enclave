#include <map>
#include <iostream>
#include "regs.h"

class SecureEnclave {
    //map to handle address-data pairs
    private:
        std::map<uint32_t, uint32_t> registers;
    
    public:
        void write(uint32_t addr, uint32_t data) {
            registers[addr] = data;
        }
    
        uint32_t read(uint32_t addr) {
            if (registers.find(addr) != registers.end()) {
                return registers[addr];
            }
            return 0xDEADBEEF;
        }
};

// creating global variable
SecureEnclave* enclave_instance = nullptr;

void hw_init() {
    if (!enclave_instance) enclave_instance = new SecureEnclave();
}

void hw_write_reg(uint32_t addr, uint32_t data) {
    if (enclave_instance) enclave_instance->write(addr, data);
}

uint32_t hw_read_reg(uint32_t addr) {
    if (enclave_instance) return enclave_instance->read(addr);
    return 0;
}

