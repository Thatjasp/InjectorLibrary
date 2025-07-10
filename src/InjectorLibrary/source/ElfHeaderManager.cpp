#include "ElfHeaderManager.h"
#include "ElfHeader.h"
#include "ElfProgramHeader.h"
#include "ElfSectionHeader.h"
#include "fstream"
#include <elf.h>
#include <iostream>
#include <sys/types.h>
namespace InjectorLibrary {
ElfHeaderManager::ElfHeaderManager(std::filesystem::path binaryPath)
    : m_binaryPath(binaryPath)
{
    std::ifstream binaryStream(binaryPath, std::ios::binary);
    if (!binaryStream) {
        std::cerr << "Could not open file" << std::endl;
        return;
    }

    Elf64_Ehdr ehdr {};
    binaryStream.read(reinterpret_cast<char*>(&ehdr), sizeof(ehdr));
    // Header magic numbers
    if (!binaryStream || ehdr.e_ident[0] != 0x7f || ehdr.e_ident[1] != 'E' || ehdr.e_ident[2] != 'L' || ehdr.e_ident[3] != 'F') {
        std::cerr << "File is not an elf binary" << std::endl;
        return;
    }

    u_int64_t programHeaderOffset = ehdr.e_phoff;
    u_int16_t programHeaderNums = ehdr.e_phnum;

    binaryStream.seekg(programHeaderOffset);
    std::vector<Elf64_Phdr> programHeaders;
    for (int i = 0; i < programHeaderNums; ++i) {
        Elf64_Phdr phdr;
        binaryStream.read(reinterpret_cast<char*>(&phdr), sizeof(phdr));
        programHeaders.push_back(phdr);
    }
    uint64_t sectionOffset = ehdr.e_shoff;
    uint16_t sectionHeaderNums = ehdr.e_shnum;
    std::vector<Elf64_Shdr> sectionHeaders;
    binaryStream.seekg(sectionOffset);
    for (int i = 0; i < sectionHeaderNums; ++i) {
        Elf64_Shdr shdr;
        binaryStream.read(reinterpret_cast<char*>(&shdr), sizeof(shdr));
        sectionHeaders.push_back(shdr);
    }
    m_sectionHeader = std::move(sectionHeaders);
    m_programHeader = std::move(programHeaders);
    m_elfHeader = std::move(ehdr);
    std::cout << "CLOSESD" << std::endl;
    binaryStream.close();
}
void ElfHeaderManager::changeEntryPoint(int address)
{
    std::ofstream binaryStream(m_binaryPath, std::ios::binary | std::ios::out | std::ios_base::in);
    auto elfHeader = m_elfHeader.getHeader();
    elfHeader.e_entry = address;
    binaryStream.write(reinterpret_cast<char*>(&elfHeader), sizeof(elfHeader));
    binaryStream.close();
}
ElfSectionHeader ElfHeaderManager::getSectionHeader()
{
    return m_sectionHeader;
}
ElfProgramHeader ElfHeaderManager::getProgramHeader()
{
    return m_programHeader;
}
ElfHeader ElfHeaderManager::getHeader()
{
    return m_elfHeader;
}
}
