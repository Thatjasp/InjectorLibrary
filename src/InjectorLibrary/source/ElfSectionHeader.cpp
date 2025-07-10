#include "ElfSectionHeader.h"
#include <elf.h>
#include <utility>
namespace InjectorLibrary {

ElfSectionHeader::ElfSectionHeader() { }
ElfSectionHeader::ElfSectionHeader(ElfSectionHeader&& other)
    : m_sectionHeaders(std::move(other.m_sectionHeaders))
{
}
ElfSectionHeader::ElfSectionHeader(const ElfSectionHeader& other)
    : m_sectionHeaders(other.m_sectionHeaders)
{
}
ElfSectionHeader::ElfSectionHeader(std::vector<Elf64_Shdr>&& sectionHeaders)
    : m_sectionHeaders(sectionHeaders)
{
}
ElfSectionHeader::ElfSectionHeader(const std::vector<Elf64_Shdr>& sectionHeaders)
    : m_sectionHeaders(sectionHeaders)
{
}
std::vector<Elf64_Shdr>& ElfSectionHeader::getSectionHeaders()
{
    return m_sectionHeaders;
}

ElfSectionHeader& ElfSectionHeader::operator=(std::vector<Elf64_Shdr>&& sectionHeaders)
{
    std::swap(this->m_sectionHeaders, sectionHeaders);
    return *this;
}

ElfSectionHeader& ElfSectionHeader::operator=(ElfSectionHeader&& elfHeader)
{
    std::swap(this->m_sectionHeaders, elfHeader.m_sectionHeaders);
    return *this;
}

ElfSectionHeader& ElfSectionHeader::operator=(const ElfSectionHeader& elfHeader)
{
    *this = ElfSectionHeader(elfHeader);
    return *this;
}

ElfSectionHeader& ElfSectionHeader::operator=(const std::vector<Elf64_Shdr>& elfHeader)
{
    *this = ElfSectionHeader(elfHeader);
    return *this;
}

}
