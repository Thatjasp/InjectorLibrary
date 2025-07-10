#pragma once
#include <elf.h>
namespace InjectorLibrary {
class ElfHeader {
public:
    ElfHeader();
    ElfHeader(Elf64_Ehdr&& elf64Header);
    ElfHeader(const Elf64_Ehdr& elf64Header);
    ElfHeader(const ElfHeader& other);
    ElfHeader(ElfHeader&& other);
    ElfHeader& operator=(Elf64_Ehdr&&);
    ElfHeader& operator=(ElfHeader&&);
    ElfHeader& operator=(const ElfHeader&);
    ElfHeader& operator=(const Elf64_Ehdr&);
    Elf64_Ehdr getHeader();

private:
    Elf64_Ehdr m_elf64Header;
};
}
