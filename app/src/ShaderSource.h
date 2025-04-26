#pragma once

#include "Result.h"

#include <string>
#include <filesystem>

struct ShaderPaths
{
    std::filesystem::path vertex;
    std::filesystem::path fragment;
};

struct ShaderSource
{
    std::string vertex;
    std::string fragment;

    static Result<ShaderSource> Load(const ShaderPaths& paths);
};