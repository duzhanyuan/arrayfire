/*******************************************************
 * Copyright (c) 2014, ArrayFire
 * All rights reserved.
 *
 * This file is distributed under 3-clause BSD license.
 * The complete license agreement can be obtained at:
 * http://arrayfire.com/licenses/BSD-3-Clause
 ********************************************************/

#include <gtest/gtest.h>
#include <arrayfire.h>
#include <af/dim4.hpp>
#include <af/defines.h>
#include <af/traits.hpp>
#include <vector>
#include <iostream>
#include <complex>
#include <string>
#include <testHelpers.hpp>

using std::vector;
using std::string;
using std::cout;
using std::endl;
using af::cfloat;
using af::cdouble;

///////////////////////////////// CPP ////////////////////////////////////
//

template<typename T>
void inverseTester(const int m, const int n, const int k, double eps)
{
    if (noDoubleTests<double>()) return;
    af::array A  = af::randu(m, n, (af::dtype)af::dtype_traits<T>::af_type);
    af::array IA = inverse(A);

    af::array I = af::identity(m, n, (af::dtype)af::dtype_traits<T>::af_type);
    af::array I2 = af::matmul(A, IA);

    ASSERT_NEAR(0, af::max<double>(af::abs(real(I - I2))), eps);
    ASSERT_NEAR(0, af::max<double>(af::abs(imag(I - I2))), eps);
}

#define INVERSE_TESTS(T, eps)                   \
    TEST(INVERSE, T##Square)                    \
    {                                           \
        inverseTester<T>(1000, 1000, 100, eps); \
    }                                           \
    TEST(INVERSE, T##SquareMultiple)            \
    {                                           \
        inverseTester<T>(2048, 2048, 512, eps); \
    }                                           \

INVERSE_TESTS(float, 0.01)
INVERSE_TESTS(double, 1E-5)
INVERSE_TESTS(cfloat, 0.01)
INVERSE_TESTS(cdouble, 1E-5)
