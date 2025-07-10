#include "ElfBinary.h"
#include "IBinaryFile.h"
#include <filesystem>

namespace InjectorLibrary {

ElfBinary::ElfBinary(std::filesystem::path binaryPath)
    : IBinaryFile(binaryPath)
    , m_elfHeaderManager(binaryPath)
{
}

void ElfBinary::changeEntryPoint(int address)
{
    m_elfHeaderManager.changeEntryPoint(address);
}

InjectionCave ElfBinary::getInjectionCave()
{
    auto elfHeader = m_elfHeaderManager.getHeader().getHeader();
    uint16_t programHeaderSize = (elfHeader.e_phnum * elfHeader.e_phentsize);
    uint64_t programHeaderOffset = elfHeader.e_phoff;

    uint64_t sectionHeaderOffset = elfHeader.e_shoff;

    return { .start = programHeaderSize + programHeaderOffset + 1, .end = sectionHeaderOffset };
}

std::any ElfBinary::getHeaderManager()
{
    return m_elfHeaderManager;
}
}
