#pragma once
#include <iostream>
#include <string>
#include <GLCommon.h>
#include <lin_alg/lin_alg.h>
#include "./assert_helper.hpp"

// Homemade scuffed tester

void test_mat3_create()
{
    lin_alg::mat3 foo(0, 0, 0, 0, 0, 0, 0, 0, 0);
    lin_alg::mat3 bar(0.0f);
    assert_mat3(foo, bar, "test_create_empty");

    foo = lin_alg::mat3();
    bar = lin_alg::mat3(1.0f);
    assert_mat3(foo, bar, "test_create_I");

    lin_alg::mat4 fuu(0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15);
    lin_alg::mat3 buu(fuu);
    assert_mat3(buu, lin_alg::mat3(0,1,2,4,5,6,8,9,10), "test_create_from_mat4");
}

void test_mat3_access()
{
    // TEST_ACCESS_1
    lin_alg::mat3 foo(0, 1, 2, 3, 4, 5, 6, 7, 8);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (foo[i][j] != 3 * i + j)
            {
                std::cout << "Failed: test_access_1" << '\n';
                return;
            }
        }
    }

    // TEST_ACCESS_2
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            float tmp = 8 - foo[i][j];
            foo[i][j] = tmp;
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (foo[i][j] != 8 - (3 * i + j))
            {
                std::cout << "Failed: test_access_2" << '\n';
                return;
            }
        }
    }
}

void test_mat3_add()
{
    lin_alg::mat3 a(1, 2, 3, 4, 5, 6, 7, 8, 9);
    lin_alg::mat3 b(1, 1, 1, 1, 1, 1, 1, 1, 1);
    lin_alg::mat3 c = a + b;
    assert_mat3(c, lin_alg::mat3(2, 3, 4, 5, 6, 7, 8, 9, 10), "test_add");
}

void test_mat3_minus()
{
    lin_alg::mat3 a(1, 2, 3, 4, 5, 6, 7, 8, 9);
    lin_alg::mat3 b(1, 1, 1, 1, 1, 1, 1, 1, 1);
    lin_alg::mat3 c = a - b;
    assert_mat3(c, lin_alg::mat3(0, 1, 2, 3, 4, 5, 6, 7, 8), "test_minus");
}

void test_mat3_scalar_mult()
{
    lin_alg::mat3 a(1, 2, 3, 4, 5, 6, 7, 8, 9);
    int scalar = 5;
    assert_mat3(lin_alg::mat3(5, 10, 15, 20, 25, 30, 35, 40, 45), a * 5, "test_scalar_mult_5");

    scalar = 0;
    assert_mat3(lin_alg::mat3(0, 0, 0, 0, 0, 0, 0, 0, 0), a * scalar, "test_scalar_mult_0");

    scalar = -5;
    assert_mat3(lin_alg::mat3(-5, -10, -15, -20, -25, -30, -35, -40, -45), a * scalar, "test_scalar_mult_-5");
}

void test_mat3_mat3_mult()
{
    lin_alg::mat3 a(1, 2, 3, 4, 5, 6, 7, 8, 9);
    lin_alg::mat3 b(9, 8, 7, 6, 5, 4, 3, 2, 1);
    assert_mat3(a * b, lin_alg::mat3(30, 24, 18, 84, 69, 54, 138, 114, 90), "test_mat3_mat3_mult");

    lin_alg::mat3 c;
    assert_mat3(a * c, a, "test_mat3_mat3_mult_Identity");
}

void test_mat3_vec3_right_mult()
{
    lin_alg::vec3 v(1, 2, 3);
    lin_alg::mat3 A(1, 2, 3, 4, 5, 6, 7, 8, 9);
    lin_alg::vec3 x = A * v;
    assert_vec3(x, lin_alg::vec3(30, 36, 42), "test_right_multiply_mat3_vec3");
}

void test_mat3_transpose()
{
    lin_alg::mat3 a(1, 2, 3, 4, 5, 6, 7, 8, 9);
    lin_alg::mat3 b(9, 8, 7, 6, 5, 4, 3, 2, 1);

    assert_mat3(lin_alg::transpose(a), lin_alg::mat3(1, 4, 7, 2, 5, 8, 3, 6, 9), "test_basic_transpose");

    lin_alg::mat3 c = lin_alg::transpose(a) * lin_alg::transpose(b);

    assert_mat3(c, lin_alg::mat3(90, 54, 18, 114, 69, 24, 138, 84, 30), "test_mult_transpose");
}

void test_mat3()
{
    std::cout << "Testing mat3..." << '\n';
    test_mat3_create();
    test_mat3_access();
    test_mat3_add();
    test_mat3_minus();
    test_mat3_scalar_mult();
    test_mat3_mat3_mult();
    test_mat3_vec3_right_mult();
    test_mat3_transpose();

    std::cout << "Testing completed!" << '\n';
}