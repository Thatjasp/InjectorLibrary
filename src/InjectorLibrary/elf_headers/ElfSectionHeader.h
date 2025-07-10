#pragma once
#include <elf.h>
#include <vector>
namespace InjectorLibrary {
class ElfSectionHeader {
public:
    ElfSectionHeader();
    ElfSectionHeader(std::vector<Elf64_Shdr>&&);
    ElfSectionHeader(const std::vector<Elf64_Shdr>&);
    ElfSectionHeader(const ElfSectionHeader& other);
    ElfSectionHeader(ElfSectionHeader&& other);
    ElfSectionHeader& operator=(std::vector<Elf64_Shdr>&&);
    ElfSectionHeader& operator=(ElfSectionHeader&&);
    ElfSectionHeader& operator=(const ElfSectionHeader&);
    ElfSectionHeader& operator=(const std::vector<Elf64_Shdr>&);
    std::vector<Elf64_Shdr>& getSectionHeaders();

private:
    std::vector<Elf64_Shdr> m_sectionHeaders;
};
}
