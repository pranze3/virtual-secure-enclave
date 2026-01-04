#include <iostream>
#include <cstdint>
#include <cstring>
#include "regs.h"

class SecureEnclave {
    private:
        uint8_t physical_memory[4096];

    public:
        SecureEnclave() {
            std::memset(physical_memory, 0, 4096);
            std::cout << "secure enclave powered up!" <<std::endl;
        }
        
        void write (uint32_t addr, uint32_t data) {
            if (addr > 4092) {
                std::cout << "write out of bounds" <<std::endl;
                return;
            }
            //write logic
            uint8_t *memptr = &physical_memory[addr];
            volatile uint32_t* castptr = reinterpret_cast<volatile uint32_t*>(memptr);
            *castptr = data;
        }

        uint32_t read (uint32_t addr) {
            if (addr > 4092) {
                std::cout << "read out of bounds" <<std::endl;
                return 0;
            }

            //read logic
            uint8_t *memptr = &physical_memory[addr];
            volatile uint32_t* castptr = reinterpret_cast<volatile uint32_t*>(memptr);
            return *castptr;
        }              

};

    //wrapper for the C firmware
    SecureEnclave* enclave_instance = nullptr;

    extern "C" {
        void hw_init() {
            if (enclave_instance == nullptr) {
                enclave_instance = new SecureEnclave();
            }
        }

        void hw_write_reg(uint32_t addr, uint32_t data) {
            if (enclave_instance) {
                enclave_instance->write(addr, data);
            }
        }

        uint32_t hw_read_reg(uint32_t addr) {
            if (enclave_instance) {
                return enclave_instance->read(addr);
            }
            return 0;
        }
    }

