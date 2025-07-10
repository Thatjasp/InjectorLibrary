#pragma once
#include "ElfHeader.h"
#include "ElfProgramHeader.h"
#include "ElfSectionHeader.h"
#include <elf.h>
#include <filesystem>
#include <iosfwd>
namespace InjectorLibrary {
class ElfHeaderManager {
public:
    ElfHeaderManager(std::filesystem::path);
    void changeEntryPoint(int address);
    ElfProgramHeader getProgramHeader();
    ElfSectionHeader getSectionHeader();
    ElfHeader getHeader();

private:
    ElfHeader m_elfHeader;
    ElfProgramHeader m_programHeader;
    ElfSectionHeader m_sectionHeader;
    std::filesystem::path m_binaryPath;
    std::streampos m_startOfFile;
};
}
