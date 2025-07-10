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
template <typename T>
class ICodeCaveAlg {
public:
    ICodeCaveAlg(std::shared_ptr<IBinaryFile<T>> binaryFile)
        : m_binaryFile(binaryFile) { };
    virtual std::optional<CodeCave> findCave() = 0;

protected:
    std::shared_ptr<IBinaryFile<T>> m_binaryFile;
};
}
