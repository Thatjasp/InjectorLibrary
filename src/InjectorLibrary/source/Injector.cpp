#include "Injector.h"
#include <fstream>
#include <iostream>
#include <iterator>
namespace InjectorLibrary {
Injector::Injector(std::shared_ptr<IBinaryFile> binaryFile, std::shared_ptr<IBinaryFile> payloadFile, CodeCave codeCave)
    : mp_binaryFile(binaryFile)
    , m_curCodeCave(codeCave)
    , mp_payloadFile(payloadFile)
{
}
void Injector::injectTarget(int address)
{
    std::vector<char> payloadVec = getByteData(mp_payloadFile);
    std::ofstream cleanStream(mp_binaryFile->getPath(), std::ios::binary | std::ios::out | std::ios_base::in);
    std::cout << "Code Cave Start Pos" << std::hex << m_curCodeCave.startPos << "\n";
    std::cout << "Code Cave end Pos" << std::hex << m_curCodeCave.endPos << "\n";
    cleanStream.seekp(m_curCodeCave.startPos, std::ios_base::beg);
    cleanStream.write(payloadVec.data(), payloadVec.size());
    cleanStream.close();
    mp_binaryFile->changeEntryPoint(address);
    //  TODO
}

std::vector<char> Injector::getByteData(const std::shared_ptr<IBinaryFile>& p_binary)
{
    InjectionCave injectionCave = p_binary->getInjectionCave();
    std::ifstream targetStream(p_binary->getPath(), std::ios::binary);
    targetStream.seekg(injectionCave.start);
    while (targetStream.peek() == 0) {
        targetStream.get();
    }

    std::streamsize targetStreamSize = injectionCave.end - targetStream.tellg();
    std::vector<char> vec;

    vec.reserve(targetStreamSize);

    vec.insert(vec.begin(), std::istream_iterator<char>(targetStream), std::istream_iterator<char>());
    targetStream.close();
    return vec;
}
}
