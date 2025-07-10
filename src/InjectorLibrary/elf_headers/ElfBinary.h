#pragma once
#include "ElfHeaderManager.h"
#include "IBinaryFile.h"
#include <filesystem>
namespace InjectorLibrary {

class ElfBinary : public IBinaryFile {
public:
    ElfBinary(std::filesystem::path);
    void changeEntryPoint(int address) override;
    InjectionCave getInjectionCave() override;
    std::any getHeaderManager() override;

private:
    ElfHeaderManager m_elfHeaderManager;
};
}
