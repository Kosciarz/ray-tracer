#include <iostream>

#include "Application.h"
#include "RayTracerLayer.h"

using namespace raytracer;

int main(int argc, char* argv[])
{
    try
    {
        Application app = Application::Create();
        app.PushLayer<RayTracerLayer>();
        app.Run();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
}