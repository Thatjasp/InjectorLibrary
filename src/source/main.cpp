#include "ElfBinary.h"
#include "ElfCodeCaveAlg.h"
#include "IBinaryFile.h"
#include "Injector.h"
#include <memory>
int main()
{
    using namespace InjectorLibrary;
    std::shared_ptr<IBinaryFile<ElfBinary>> p_elfBinary = std::make_shared<InjectorLibrary::ElfBinary>("./hello");

    std::shared_ptr<IBinaryFile<ElfBinary>> p_infectedBinary = std::make_shared<ElfBinary>("./infect");

    ElfCodeCaveAlg codeCaveAlg(p_elfBinary);

    ElfHeaderManager elfHeaderManager = p_elfBinary->getHeaderManager<ElfHeaderManager>();

    auto pHdr = elfHeaderManager.getProgramHeader().getFirstLoadableSegment();

    std::optional<InjectorLibrary::CodeCave> optionalCodeCave
        = codeCaveAlg.findCave();
    if (optionalCodeCave) {
        InjectorLibrary::Injector injector(p_elfBinary, p_infectedBinary, *optionalCodeCave);
        injector.injectTarget(pHdr->p_vaddr + (*optionalCodeCave).startPos);
    }
}
