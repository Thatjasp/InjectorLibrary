#pragma once
#include "IBinaryFile.h"
#include <optional>
namespace InjectorLibrary {
struct CodeCave {
    // [startPos, endPos)
    std::streampos startPos;
    std::streampos endPos;
    uint64_t size;
};
class ICodeCaveAlg {
public:
    ICodeCaveAlg(std::shared_ptr<IBinaryFile> binaryFile)
        : m_binaryFile(binaryFile) { };
    virtual std::optional<CodeCave> findCave() = 0;

protected:
    std::shared_ptr<IBinaryFile> m_binaryFile;
};
}
