#pragma once

#include "Result.h"

#include <string>
#include <filesystem>

struct ShaderPaths
{
    std::filesystem::path vertex;
    std::filesystem::path fragment;
};

struct ShaderSources
{
    std::string vertex;
    std::string fragment;

    static Result<ShaderSources> Load(const ShaderPaths& paths);
};