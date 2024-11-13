#ifndef PROGRAM_INIT_H
#define PROGRAM_INIT_H
#pragma once
#include <GLCommon.h>
#include <iostream>

/**
 * @brief Initializes the libraries required.
 *
 */
namespace ProgramInit
{
    /**
     * @brief Initialize GLFW
     *
     */
    bool initialize_glfw();

    /**
     * @brief Load all function pointers using GLAD
     *
     */
    bool initialize_glad();

    /**
     * @brief Function for GLFW error callback
     * @param error
     * @param description
     * 
     */
    void error_callback(int, const char *);
}

#endif