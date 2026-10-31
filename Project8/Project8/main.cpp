#include "CGApplication.h"
#include <iostream>
#include <stdexcept>

//
// PROYECTO: Project8
// 
// DESCRIPCIÓN: Aplicación gráfica que incluye modelos importados desde descripciones externas
//
int main()
{
    CGApplication app;

    try
    {
        app.run();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}