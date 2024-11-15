#pragma once
#include <iostream>
#include <string>
#include <GLCommon.h>
#include <lin_alg/lin_alg.h>
#include "./assert_helper.hpp"

// Homemade scuffed tester

void test_mat4_create()
{
    lin_alg::mat4 foo(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    lin_alg::mat4 bar(0.0f);
    assert_mat4(foo, bar, "test_create_empty");

    foo = lin_alg::mat4();
    bar = lin_alg::mat4(1.0f);
    assert_mat4(foo, bar, "test_create_I");

    lin_alg::mat3 fuu(0,1,2,3,4,5,6,7,8);
    lin_alg::mat4 buu(fuu);
    assert_mat4(buu, lin_alg::mat4(0,1,2,0,3,4,5,0,6,7,8,0,0,0,0,1), "test_create_from_mat3");
}

void test_mat4_access()
{
    // TEST_ACCESS_1
    lin_alg::mat4 foo(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (foo[i][j] != 4 * i + j)
            {
                std::cout << "Failed: test_access_1" << '\n';
                return;
            }
        }
    }

    // TEST_ACCESS_2
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            float tmp = 15 - foo[i][j];
            foo[i][j] = tmp;
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (foo[i][j] != 15 - (4 * i + j))
            {
                std::cout << "Failed: test_access_2" << '\n';
                return;
            }
        }
    }
}

void test_mat4_add()
{
    lin_alg::mat4 a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    lin_alg::mat4 b(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    lin_alg::mat4 c = a + b;
    assert_mat4(c, lin_alg::mat4(2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17), "test_add");
}

void test_mat4_minus()
{
    lin_alg::mat4 a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    lin_alg::mat4 b(1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    lin_alg::mat4 c = a - b;
    assert_mat4(c, lin_alg::mat4(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15), "test_minus");
}

void test_mat4_scalar_mult()
{
    lin_alg::mat4 a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    int scalar = 5;
    assert_mat4(lin_alg::mat4(5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80), a * 5, "test_scalar_mult_5");

    scalar = 0;
    assert_mat4(lin_alg::mat4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0), a * scalar, "test_scalar_mult_0");

    scalar = -5;
    assert_mat4(lin_alg::mat4(-5, -10, -15, -20, -25, -30, -35, -40, -45, -50, -55, -60, -65, -70, -75, -80), a * scalar, "test_scalar_mult_-5");
}

void test_mat4_mat4_mult()
{
    lin_alg::mat4 a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    lin_alg::mat4 b(16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1);
    assert_mat4(a * b, lin_alg::mat4(80, 70, 60, 50, 240, 214, 188, 162, 400, 358, 316, 274, 560, 502, 444, 386), "test_mat4_mat4_mult");

    lin_alg::mat4 c;
    assert_mat4(a * c, a, "test_mat4_mat4_mult_Identity");
}

void test_mat4_vec4_right_mult()
{
    lin_alg::vec4 v(1, 2, 3, 4);
    lin_alg::mat4 A(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);
    lin_alg::vec4 x = A * v;
    assert_vec4(x, lin_alg::vec4(90, 100, 110, 120), "test_right_multiply_mat4_vec4");
}

void test_mat4_transpose()
{

    lin_alg::mat4 a(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16);

    assert_mat4(lin_alg::transpose(a), lin_alg::mat4(1,5,9,13,2,6,10,14,3,7,11,15,4,8,12,16), "test_basic_transpose");
}

void test_mat4()
{
    std::cout << "Testing mat4..." << '\n';
    test_mat4_create();
    test_mat4_access();
    test_mat4_add();
    test_mat4_minus();
    test_mat4_scalar_mult();
    test_mat4_mat4_mult();
    test_mat4_vec4_right_mult();
    // test_mat4_transpose();

    std::cout << "Testing completed!" << '\n';
}