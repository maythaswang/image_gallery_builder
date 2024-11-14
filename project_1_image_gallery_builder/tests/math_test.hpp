#pragma once
#include <GLCommon.h>
#include <lin_alg/lin_alg.h>

#include <iostream>
#include <string> 

// Homemade scuffed tester
void assert_vec3(lin_alg::vec3 input, lin_alg::vec3 expected, std::string test_name)
{
    if (!(input[0] - expected[0] < 1e-8 && input[1] - expected[1] < 1e-8 && input[2] - expected[2] < 1e-8)) {
        std::string e = "Failed: " + test_name + "!!"; 
        // throw (e);
        std::cout << e << '\n';
    }
}

void test_vec3_create()
{
    lin_alg::vec3 foo;
    lin_alg::vec3 bar(0,0,0);
    assert_vec3(foo, bar, "test_create_empty");
}

void test_vec3_add() {
    lin_alg::vec3 a(1.0f, 2.0f, 3.0f);
    lin_alg::vec3 b(2.0f, 3, 4);
    lin_alg::vec3 c = a + b;
    assert_vec3(c, lin_alg::vec3(3, 5, 7), "test_add");
}

void test_vec3_minus() {
    lin_alg::vec3 a(1.0f, 2.0f, 3.0f);
    lin_alg::vec3 b(2.0f, 3, 4);
    lin_alg::vec3 c = a - b;
    assert_vec3(c, lin_alg::vec3(-1, -1, -1), "test_add");
}

void test_vec3_scalar_mult() {
    lin_alg::vec3 a(1.0f, 2.0f, 3.0f);
    int scalar = 5;
    assert_vec3(lin_alg::vec3(5,10,15), a * scalar, "test_scalar_mult_5");

    scalar = 0;
    assert_vec3(lin_alg::vec3(0, 0, 0), a * scalar, "test_scalar_mult_0");

    scalar = -5;
    assert_vec3(lin_alg::vec3(-5, -10, -15), a * scalar, "test_scalar_mult_-5");
}

void test_vec3_normalize() { 
    lin_alg::vec3 a(1.0f, 2.0f, 3.0f);
    assert_vec3(lin_alg::normalize(a), lin_alg::vec3(0.26726124191f, 0.53452248382f, 0.80178372573f), "test_normalize_positive");
     
    a = lin_alg::vec3(0.0f, -0.0f, 0.0f);
    assert_vec3(lin_alg::normalize(a), lin_alg::vec3(0,-0,0), "test_normalize_zero"); // TODO: Maybe make a assert error function?
}

void test_vec3_cross() {
    lin_alg::vec3 eye = lin_alg::vec3(0, 0, 3.0);
    lin_alg::vec3 center = lin_alg::vec3(0, 0, 0);
    lin_alg::vec3 up = lin_alg::vec3(0, 1.0, 0);

    lin_alg::vec3 direction = lin_alg::normalize(center - eye);
    lin_alg::vec3 right = lin_alg::normalize(lin_alg::cross(direction, up));

    assert_vec3(right, lin_alg::vec3(1, -0, 0) ,"test_cross_product_right_camera."); 


    eye = lin_alg::vec3(-2.27595f, 1.47525f, 2.2099f);
    center = lin_alg::vec3(-1.8f, 0, 0);
    up = lin_alg::vec3(0.499883f, 0.86388f, -0.061874f);

    direction = lin_alg::normalize(center - eye);
    right = lin_alg::normalize(lin_alg::cross(direction, up));

    assert_vec3(right, lin_alg::vec3(0.786005f, -0.422495f, 0.451326f) ,"test_cross_product_right_camera_2."); 
}   

void test_vec3()
{
    // I'll hold off on testing ivec3 since im getting lazy.
    std::cout << "Testing vec3..." << '\n';
    test_vec3_create();
    test_vec3_add();
    test_vec3_minus();
    test_vec3_scalar_mult(); 
    test_vec3_normalize();
    test_vec3_cross();
    std::cout << "Testing completed!" << '\n';
}