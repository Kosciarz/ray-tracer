#include <iostream>

#include "App/Application.hpp"

int main(int argc, char* argv[])
{
    try
    {
        raytracer::Application app;
        app.Run();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}