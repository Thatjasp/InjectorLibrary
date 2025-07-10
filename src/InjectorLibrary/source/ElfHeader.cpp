#include "ElfHeader.h"
#include <elf.h>
#include <utility>
namespace InjectorLibrary {

ElfHeader::ElfHeader() { }
ElfHeader::ElfHeader(ElfHeader&& other)
    : m_elf64Header(std::move(other.m_elf64Header))
{
}
ElfHeader::ElfHeader(const ElfHeader& other)
    : m_elf64Header(other.m_elf64Header)
{
}
ElfHeader::ElfHeader(Elf64_Ehdr&& elf64Header)
    : m_elf64Header(std::move(elf64Header))
{
}
ElfHeader::ElfHeader(const Elf64_Ehdr& elf64Header)
    : m_elf64Header(elf64Header)
{
}
Elf64_Ehdr ElfHeader::getHeader()
{
    return m_elf64Header;
}

ElfHeader& ElfHeader::operator=(Elf64_Ehdr&& elf64Header)
{
    std::swap(this->m_elf64Header, elf64Header);
    return *this;
}
ElfHeader& ElfHeader::operator=(ElfHeader&& elfHeader)
{
    std::swap(this->m_elf64Header, elfHeader.m_elf64Header);
    return *this;
}
ElfHeader& ElfHeader::operator=(const ElfHeader& elfHeader)
{
    *this = ElfHeader(elfHeader);
    return *this;
}
ElfHeader& ElfHeader::operator=(const Elf64_Ehdr& elfHeader)
{
    *this = ElfHeader(elfHeader);
    return *this;
}

}
