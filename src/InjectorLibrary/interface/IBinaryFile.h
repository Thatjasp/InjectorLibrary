#pragma once
#include <filesystem>
#include <iosfwd>
namespace InjectorLibrary {
struct InjectionCave {
    std::streampos start;
    std::streampos end;
};
template <typename T>
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
    template <typename U>
    U getHeaderManager()
    {
        T& derivedBinaryFile = static_cast<T&>(*this);
        return derivedBinaryFile.getHeaderManager();
    }

protected:
    std::filesystem::path m_path;
};
}
