#include "ShaderSource.h"

#include <string>
#include <optional>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

static std::optional<std::string> ReadFile(const fs::path& path);

bool ShaderSource::IsValid() const
{
    return vertex.has_value() && !vertex->empty()
        && fragment.has_value() && !fragment->empty();
}

ShaderSource::operator bool() const
{
    return IsValid();
}

ShaderSource ShaderSource::Load(const fs::path& vertexPath, const fs::path& fragmentPath)
{
    return ShaderSource{ReadFile(vertexPath), ReadFile(fragmentPath)};
}

static std::optional<std::string> ReadFile(const fs::path& path)
{
    std::ifstream file(path, std::ios::in);
    if (!file)
        return std::nullopt;

    const auto fileSize = fs::file_size(path);
    std::string contents(fileSize, 0);
    file.read(contents.data(), fileSize);
    return contents;
}