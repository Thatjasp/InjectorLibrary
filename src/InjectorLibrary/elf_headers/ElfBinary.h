#pragma once
#include "ElfHeaderManager.h"
#include "IBinaryFile.h"
#include <filesystem>
namespace InjectorLibrary {

class ElfBinary : public IBinaryFile<ElfBinary> {
public:
    ElfBinary(std::filesystem::path);
    void changeEntryPoint(int address) override;
    InjectionCave getInjectionCave() override;
    ElfHeaderManager getHeaderManager();

private:
    ElfHeaderManager m_elfHeaderManager;
};
}
