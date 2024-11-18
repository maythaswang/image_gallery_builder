#ifndef PROGRAM_SETUP_H
#define PROGRAM_SETUP_H
#pragma once
#include "./WindowFactory/WindowFactory.h"
#include "./ProgramInit/ProgramInit.h"

GLFWwindow *init_glfw_glad(const unsigned int, const unsigned int, const char *);
#endif