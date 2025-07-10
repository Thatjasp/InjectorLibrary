#include "ElfCodeCaveAlg.h"
#include "ICodeCaveAlg.h"
#include <fstream>
#include <iostream>
namespace InjectorLibrary {
ElfCodeCaveAlg::ElfCodeCaveAlg(std::shared_ptr<IBinaryFile> binaryFile)
    : ICodeCaveAlg(binaryFile)
{
}
std::optional<CodeCave> ElfCodeCaveAlg::findCave()
{
    InjectionCave injectionCave = m_binaryFile->getInjectionCave();

    CodeCave maxCave;
    char curByte;
    std::streamsize maxSize = 0;
    std::streamsize curSize = 0;

    std::streampos leftPosition;

    std::ifstream binaryFileStream(m_binaryFile->getPath(), std::ios::binary);
    if (!binaryFileStream) {
        std::cerr << m_binaryFile->getPath().string() << " Was not able to be open" << std::endl;
        return std::nullopt;
    }

    binaryFileStream.seekg(injectionCave.start);

    while (binaryFileStream.tellg() != injectionCave.end) {
        std::streampos curPosition = binaryFileStream.tellg();
        binaryFileStream.get(curByte);
        if (curByte == 0) {
            leftPosition = curPosition;
            // Makes Code Cave [leftptr,rightptr)
            while (binaryFileStream.tellg() < injectionCave.end
                && curByte == 0) {
                curSize++;
                binaryFileStream.get(curByte);
                curPosition = binaryFileStream.tellg();
            }
            if (curSize > maxSize) {
                maxCave.size = curSize;
                maxCave.startPos = leftPosition;
                maxCave.endPos = curPosition;
                maxSize = curSize;
            }
            curSize = 0;
        }
    }
    std::cout << "CODE CAVE CLOSED" << std::endl;
    binaryFileStream.close();
    return maxCave;
}
}
