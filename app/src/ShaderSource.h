#pragma once

#include <string>
#include <optional>
#include <filesystem>

struct ShaderSource
{
    std::optional<std::string> vertex;
    std::optional<std::string> fragment;

    bool IsValid() const;

    operator bool() const;

    static ShaderSource Load(const std::filesystem::path& vertexPath,
        const std::filesystem::path& fragmentPath);
};