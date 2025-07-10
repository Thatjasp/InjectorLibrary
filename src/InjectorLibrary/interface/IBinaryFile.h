#pragma once
#include <any>
#include <filesystem>
#include <iosfwd>
namespace InjectorLibrary {
struct InjectionCave {
    std::streampos start;
    std::streampos end;
};

class IBinaryFile {
public:
    IBinaryFile(std::filesystem::path path)
        : m_path(path)
    {
    }
    virtual void changeEntryPoint(int address) = 0;
    virtual InjectionCave getInjectionCave() = 0;
    std::filesystem::path getPath()
    {
        return m_path;
    }
    virtual std::any getHeaderManager() = 0;

protected:
    std::filesystem::path m_path;
};
}
