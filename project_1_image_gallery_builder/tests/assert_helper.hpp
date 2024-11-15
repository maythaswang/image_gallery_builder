#pragma once
#include <iostream>
#include <string>
#include <GLCommon.h>
#include <lin_alg/lin_alg.h>

void assert_vec3(lin_alg::vec3 input, lin_alg::vec3 expected, std::string test_name)
{
    if (!(std::abs(input[0] - expected[0]) < 1e-6 && std::abs(input[1] - expected[1]) < 1e-6 && std::abs(input[2] - expected[2]) < 1e-6))
    {
        std::string e = "Failed: " + test_name + "!!";
        // throw (e);
        std::cout << e << '\n';
    }
}

void assert_vec4(lin_alg::vec4 input, lin_alg::vec4 expected, std::string test_name)
{
    if (!(std::abs(input[0] - expected[0]) < 1e-6 && std::abs(input[1] - expected[1]) < 1e-6 && std::abs(input[2] - expected[2]) < 1e-6 && std::abs(input[3] - expected[3]) < 1e-6))
    {
        std::string e = "Failed: " + test_name + "!!";
        // throw (e);
        std::cout << e << '\n';
    }
}

void assert_mat3(lin_alg::mat3 input, lin_alg::mat3 expected, std::string test_name)
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (std::abs(input[i][j] - expected[i][j]) > 1e-6)
            {
                std::string e = "Failed: " + test_name + "!!";
                std::cout << e << '\n';
                return;
            }
        }
    }
}