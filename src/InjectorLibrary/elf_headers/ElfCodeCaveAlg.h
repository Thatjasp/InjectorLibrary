#include "ICodeCaveAlg.h"
namespace InjectorLibrary {
class ElfCodeCaveAlg : public ICodeCaveAlg {
public:
    ElfCodeCaveAlg(std::shared_ptr<IBinaryFile> binaryFile);
    std::optional<CodeCave> findCave() override;
};
}
