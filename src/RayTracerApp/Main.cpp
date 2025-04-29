#include "Application.h"


int main()
{
    auto appResult = raytracer::Application::Init();
    if (appResult.IsErr())
        return EXIT_FAILURE;

    auto app = appResult.ValueMove();
    app.Run();
}