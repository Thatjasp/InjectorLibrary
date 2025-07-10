#pragma once
#include "IBinaryFile.h"
#include "ICodeCaveAlg.h"
#include "vector"
namespace InjectorLibrary {
class Injector {
public:
    Injector(std::shared_ptr<IBinaryFile>, std::shared_ptr<IBinaryFile>, CodeCave);
    void injectTarget(int address);

private:
    std::vector<char> getByteData(const std::shared_ptr<IBinaryFile>& p_binary);
    std::shared_ptr<IBinaryFile> mp_payloadFile;
    std::shared_ptr<IBinaryFile> mp_binaryFile;
    CodeCave m_curCodeCave;
};
}
