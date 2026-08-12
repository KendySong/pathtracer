#include "Core/Application.hpp"

int main(int argc, char* argv[])
{
    srand(Settings::seed);
    Application app;
    app.run();
}