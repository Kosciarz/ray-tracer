#include <iostream>
#include <exception>

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
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}