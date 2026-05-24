#include "app/standalone_app.hpp"

#include <exception>
#include <iostream>

int main()
{
    try
    {
        prettyscope::StandaloneApp app;
        return app.run();
    }
    catch (const std::exception& error)
    {
        std::cerr << "Prettyscope failed: " << error.what() << '\n';
        return 1;
    }
}
