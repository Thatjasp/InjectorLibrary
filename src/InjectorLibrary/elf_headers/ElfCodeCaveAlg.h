#include "ElfBinary.h"
#include "ICodeCaveAlg.h"
namespace InjectorLibrary {
class ElfCodeCaveAlg : public ICodeCaveAlg<ElfBinary> {
public:
    ElfCodeCaveAlg(std::shared_ptr<IBinaryFile<ElfBinary>> binaryFile);
    std::optional<CodeCave> findCave() override;
};
}
