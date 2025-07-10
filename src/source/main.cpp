#include "ElfBinary.h"
#include "ElfCodeCaveAlg.h"
#include "IBinaryFile.h"
#include "Injector.h"
#include <memory>
int main()
{
    std::shared_ptr<InjectorLibrary::IBinaryFile> p_elfBinary = std::make_shared<InjectorLibrary::ElfBinary>("./hello");

    std::shared_ptr<InjectorLibrary::IBinaryFile> p_infectedBinary = std::make_shared<InjectorLibrary::ElfBinary>("./infect");

    InjectorLibrary::ElfCodeCaveAlg codeCaveAlg(p_elfBinary);

    InjectorLibrary::ElfHeaderManager elfHeaderManager = std::any_cast<InjectorLibrary::ElfHeaderManager>(p_elfBinary->getHeaderManager());

    auto pHdr = elfHeaderManager.getProgramHeader().getFirstLoadableSegment();

    std::optional<InjectorLibrary::CodeCave> optionalCodeCave
        = codeCaveAlg.findCave();
    if (optionalCodeCave) {
        InjectorLibrary::Injector injector(p_elfBinary, p_infectedBinary, *optionalCodeCave);
        injector.injectTarget(pHdr->p_vaddr + (*optionalCodeCave).startPos);
    }
}
