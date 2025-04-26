#include "ShaderSource.h"
#include "Result.h"

#include <string>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

static Result<std::string> ReadFile(const fs::path& path)
{
    if (path.empty())
        return Result<std::string>::Err("Shader path is empty");

    std::ifstream file(path, std::ios::in);
    if (!file)
        return Result<std::string>::Err("Cannot open shader file: " + path.string());

    const auto fileSize = fs::file_size(path);
    std::string contents(fileSize, 0);
    file.read(contents.data(), fileSize);
    return Result<std::string>::Ok(contents);
}

Result<ShaderSource> ShaderSource::Load(const ShaderPaths& paths)
{
    auto vertex = ReadFile(paths.vertex);
    if (!vertex)
        return Result<ShaderSource>::Err("Failed to load vertex shader: " + vertex.Error());
    
    auto fragment = ReadFile(paths.fragment);
    if (!fragment)
        return Result<ShaderSource>::Err("Failed to load vertex shader: " + fragment.Error());

    ShaderSource source{vertex.Value(), fragment.Value()};
    return Result<ShaderSource>::Ok(source);
}