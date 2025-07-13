#include <exception>

#include <spdlog/spdlog.h>

#include "App/Application.hpp"

int main()
{
    try
    {
        raytracer::Application app;
        app.Run();
    }
    catch (const std::exception& e)
    {
        spdlog::error("{}", e.what());
    }
}
