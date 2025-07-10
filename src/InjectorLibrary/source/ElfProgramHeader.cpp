#include "ElfProgramHeader.h"
#include <elf.h>
#include <limits>
#include <optional>
#include <utility>
namespace InjectorLibrary {

ElfProgramHeader::ElfProgramHeader() { }
ElfProgramHeader::ElfProgramHeader(ElfProgramHeader&& other)
    : m_programHeaders(std::move(other.m_programHeaders))
{
}
ElfProgramHeader::ElfProgramHeader(const ElfProgramHeader& other)
    : m_programHeaders(other.m_programHeaders)
{
}
ElfProgramHeader::ElfProgramHeader(std::vector<Elf64_Phdr>&& programHeaders)
    : m_programHeaders(programHeaders)
{
}
ElfProgramHeader::ElfProgramHeader(const std::vector<Elf64_Phdr>& programHeaders)
    : m_programHeaders(programHeaders)
{
}
std::vector<Elf64_Phdr>& ElfProgramHeader::getProgramHeaders()
{
    return m_programHeaders;
}

ElfProgramHeader& ElfProgramHeader::operator=(std::vector<Elf64_Phdr>&& programHeaders)
{
    std::swap(this->m_programHeaders, programHeaders);
    return *this;
}

ElfProgramHeader& ElfProgramHeader::operator=(ElfProgramHeader&& elfHeader)
{
    std::swap(this->m_programHeaders, elfHeader.m_programHeaders);
    return *this;
}

ElfProgramHeader& ElfProgramHeader::operator=(const ElfProgramHeader& elfHeader)
{
    *this = ElfProgramHeader(elfHeader);
    return *this;
}

ElfProgramHeader& ElfProgramHeader::operator=(const std::vector<Elf64_Phdr>& elfHeader)
{
    *this = ElfProgramHeader(elfHeader);
    return *this;
}

std::optional<Elf64_Phdr> ElfProgramHeader::getFirstLoadableSegment()
{
    Elf64_Phdr minLoadablePhdr;
    Elf64_Addr lowestAddress = std::numeric_limits<Elf64_Addr>::max();

    for (const auto& pHdr : m_programHeaders) {
        if (pHdr.p_type == PT_LOAD && pHdr.p_vaddr < lowestAddress) {
            lowestAddress = pHdr.p_vaddr;
            minLoadablePhdr = pHdr;
        }
    }

    if (lowestAddress == std::numeric_limits<Elf64_Addr>::max()) {
        return std::nullopt;
    }
    return minLoadablePhdr;
}

}
