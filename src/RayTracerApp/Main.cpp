#include <iostream>

#include "App/Application.h"

using namespace raytracer;

int main(int argc, char* argv[])
{
    try
    {
        Application app = Application::Create();
        app.Run();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}