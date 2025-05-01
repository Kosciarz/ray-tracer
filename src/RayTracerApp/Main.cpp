#include <iostream>

#include "Application.h"

int main(int argc, char* argv[])
{
    auto appResult = raytracer::Application::Init();
    if (appResult.IsErr())
    {
        std::cerr << "Application failed to initialize: " << appResult.Error() << '\n';
        return EXIT_FAILURE;
    }

    raytracer::Application app = appResult.ValueMove();
    app.Run();
}