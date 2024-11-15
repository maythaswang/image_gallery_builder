#pragma once
#include <iostream>
#include <string>
#include <GLCommon.h>
#include <lin_alg/lin_alg.h>
#include "./assert_helper.hpp"
// Homemade scuffed tester

void test_vec4_create()
{
    lin_alg::vec4 foo;
    lin_alg::vec4 bar(0, 0, 0, 0);
    assert_vec4(foo, bar, "test_create_empty");
}

void test_vec4_access()
{
    lin_alg::vec4 foo(1, 2, 3, 4);
    if (foo.x != 1 || foo.y != 2 || foo.z != 3 || foo.w != 4)
    {
        std::cout << "Failed: test_access_with_xyzw" << '\n';
    }

    foo.x = 3;
    foo.y = 2;
    foo.z = 1;
    foo.w = 0;
    assert_vec4(foo, lin_alg::vec4(3, 2, 1, 0), "test_access_edit_with_xyzw");

    foo[0] = 4;
    foo[1] = 5;
    foo[2] = 6;
    foo[3] = 7;
    assert_vec4(foo, lin_alg::vec4(4, 5, 6, 7), "test_access_as_array");
}

void test_vec4_add()
{
    lin_alg::vec4 a(1.0f, 2.0f, 3.0f, 4);
    lin_alg::vec4 b(2.0f, 3, 4, 5);
    lin_alg::vec4 c = a + b;
    assert_vec4(c, lin_alg::vec4(3, 5, 7, 9), "test_add");
}

void test_vec4_minus()
{
    lin_alg::vec4 a(1.0f, 2.0f, 3.0f, 4);
    lin_alg::vec4 b(2.0f, 3, 4, 5);
    lin_alg::vec4 c = a - b;
    assert_vec4(c, lin_alg::vec4(-1, -1, -1, -1), "test_minus");
}

void test_vec4_scalar_mult()
{
    lin_alg::vec4 a(1.0f, 2.0f, 3.0f, 4);
    int scalar = 5;
    assert_vec4(lin_alg::vec4(5, 10, 15, 20), a * scalar, "test_scalar_mult_5");

    scalar = 0;
    assert_vec4(lin_alg::vec4(0, 0, 0, 0), a * scalar, "test_scalar_mult_0");

    scalar = -5;
    assert_vec4(lin_alg::vec4(-5, -10, -15, -20), a * scalar, "test_scalar_mult_-5");
}

void test_vec4_normalize()
{
    lin_alg::vec4 a(1.0f, 2.0f, 3.0f,4.0f);
    assert_vec4(lin_alg::normalize(a), lin_alg::vec4(0.1825741f, 0.36514837167f, 0.5477225575f, 0.73029674334f), "test_normalize_positive");

    a = lin_alg::vec4(0.0f, -0.0f, 0.0f,0);
    assert_vec4(lin_alg::normalize(a), lin_alg::vec4(0, -0, 0,0), "test_normalize_zero"); // TODO: Maybe make a assert error function?
}

void test_vec4()
{
    // I'll hold off on testing vec4 outer product since im getting lazy and its probably not going to be used for this assignment.
    std::cout << "Testing vec4..." << '\n';
    test_vec4_create();
    test_vec4_access();
    test_vec4_add();
    test_vec4_minus();
    test_vec4_scalar_mult();
    test_vec4_normalize();
    // test_vec4_outer_product();
    std::cout << "Testing completed!" << '\n';
}