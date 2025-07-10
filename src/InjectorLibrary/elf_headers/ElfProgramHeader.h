#pragma once
#include <elf.h>
#include <optional>
#include <vector>
namespace InjectorLibrary {
class ElfProgramHeader {
public:
    ElfProgramHeader();
    ElfProgramHeader(std::vector<Elf64_Phdr>&&);
    ElfProgramHeader(const std::vector<Elf64_Phdr>&);
    ElfProgramHeader(const ElfProgramHeader& other);
    ElfProgramHeader(ElfProgramHeader&& other);
    ElfProgramHeader& operator=(std::vector<Elf64_Phdr>&&);
    ElfProgramHeader& operator=(ElfProgramHeader&&);
    ElfProgramHeader& operator=(const ElfProgramHeader&);
    ElfProgramHeader& operator=(const std::vector<Elf64_Phdr>&);
    std::vector<Elf64_Phdr>& getProgramHeaders();
    std::optional<Elf64_Phdr> getFirstLoadableSegment();

private:
    std::vector<Elf64_Phdr> m_programHeaders;
};
}
