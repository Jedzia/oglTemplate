/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the BM_FloatingPoint.cpp class.
 * \file       BM_FloatingPoint.cpp
 * \date       2020-03-17
 * \author     Jedzia.
 *
 * modified    2020-03-17, Jedzia
 */
/*---------------------------------------------------------*/
#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"

#include <SFML/System/Vector3.hpp>
#include <benchmark/benchmark.h>
//#include "../gbenchmark/src/string_util.h"

constexpr unsigned int ITERATIONS = 1000;

//using namespace benchmark;

// benchmark float instantiation
static void BM_FloatCreation(benchmark::State& state) {
    //state.SetLabel(StrFormat("float:%.1f%%", 100.0));
    state.SetLabel("float bench");

    for(auto _ : state)
    {
        volatile float empty_double;
        static_cast<void>(empty_double);
    }
}

// Register the function as a benchmark
BENCHMARK(BM_FloatCreation);

// benchmark double instantiation
static void BM_DoubleCreation(benchmark::State& state) {
    for(auto _ : state)
    {
        volatile double empty_double;
        static_cast<void>(empty_double);
    }
}

BENCHMARK(BM_DoubleCreation);

// default float vector construction
static void BM_Vector3F_CreateDefault(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < 1000; ++i) {
            volatile sf::Vector3<float> result;
            static_cast<void>(result);
        }
    }
}

BENCHMARK(BM_Vector3F_CreateDefault);

// default double vector construction
static void BM_Vector3D_CreateDefault(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < 1000; ++i) {
            volatile sf::Vector3<double> result;
            static_cast<void>(result);
        }
    }
}

BENCHMARK(BM_Vector3D_CreateDefault);

// copy float vector
static void BM_Vector3F_CopyDefault(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < ITERATIONS; ++i) {
            sf::Vector3<float> vector_v3f1;
            volatile sf::Vector3<float> result(vector_v3f1);
            static_cast<void>(result);
        }
    }
}

BENCHMARK(BM_Vector3F_CopyDefault);

// copy initialized float vector
static void BM_Vector3F_Copy123(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < ITERATIONS; ++i) {
            sf::Vector3<float> vector_v3f1(1, 2, 3);
            volatile sf::Vector3<float> result(vector_v3f1);
            static_cast<void>(result);
        }
    }
}

BENCHMARK(BM_Vector3F_Copy123);

// add float vectors
static void BM_Vector3F_Add(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < ITERATIONS; ++i) {
            sf::Vector3<float> vector_v3f1(1, 2, 3);
            sf::Vector3<float> vector_v3f2(1, 2, 3);
            sf::Vector3<float> vector_v3f3(1, 2, 3);
            vector_v3f3 = vector_v3f1 + vector_v3f2;
            volatile sf::Vector3<float> result(vector_v3f3);
            static_cast<void>(result);
        }
    }
}

BENCHMARK(BM_Vector3F_Add);

// add double vectors
static void BM_Vector3D_Add(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < ITERATIONS; ++i) {
            sf::Vector3<double> vector_v3d1(1, 2, 3);
            sf::Vector3<double> vector_v3d2(1, 2, 3);
            sf::Vector3<double> vector_v3d3(1, 2, 3);
            vector_v3d3 = vector_v3d1 + vector_v3d2;
            volatile sf::Vector3<double> result(vector_v3d3);
            static_cast<void>(result);
        }
    }
}

BENCHMARK(BM_Vector3D_Add);

// multiply float vectors
static void BM_Vector3F_Mul(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < ITERATIONS; ++i) {
            sf::Vector3<float> vector_v3f1(1, 2, 3);
            sf::Vector3<float> vector_v3f2(1, 2, 3);
            sf::Vector3<float> vector_v3f3(1, 2, 3);
            vector_v3f3 = vector_v3f1 * vector_v3f2.x;
            volatile sf::Vector3<float> result(vector_v3f3);
            static_cast<void>(result);
        }
    }
}

BENCHMARK(BM_Vector3F_Mul);

// multiply double vectors
static void BM_Vector3D_Mul(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < ITERATIONS; ++i) {
            sf::Vector3<double> vector_v3f1(1, 2, 3);
            sf::Vector3<double> vector_v3f2(1, 2, 3);
            sf::Vector3<double> vector_v3f3(1, 2, 3);
            vector_v3f3 = vector_v3f1 * vector_v3f2.x;
            volatile sf::Vector3<double> result(vector_v3f3);
            static_cast<void>(result);
        }
    }
}

// Register the function as a benchmark
BENCHMARK(BM_Vector3D_Mul);

// copy float vector
static void BM_Vector3FCopy(benchmark::State& state) {
    sf::Vector3<float> x(0, 0, 0);

    for(auto _ : state) {
        volatile sf::Vector3<float> copy(x);
    }
}

BENCHMARK(BM_Vector3FCopy);

// copy double vector
static void BM_Vector3DCopy(benchmark::State& state) {
    sf::Vector3<double> x(0, 0, 0);

    for(auto _ : state) {
        volatile sf::Vector3<double> copy(x);
    }
}

BENCHMARK(BM_Vector3DCopy);

// compare float vectors
static void BM_Vector3F_Compare(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < ITERATIONS; ++i) {
            sf::Vector3<float> vector_v3f1(1, 2, 3);
            sf::Vector3<float> vector_v3f2(1, 2, 3);
            sf::Vector3<float> vector_v3f3(1, 2, 3);
            vector_v3f3 = vector_v3f1 + vector_v3f2;
            volatile sf::Vector3<float> result(vector_v3f3);
            static_cast<void>(result);
        }
    }
}

BENCHMARK(BM_Vector3F_Compare);

// compare double vectors
static void BM_Vector3D_Compare(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < ITERATIONS; ++i) {
            sf::Vector3<double> vector_v3f1(1, 2, 3);
            sf::Vector3<double> vector_v3f2(1, 2, 3);
            sf::Vector3<double> vector_v3f3(1, 2, 3);
            vector_v3f3 = vector_v3f1 + vector_v3f2;
            volatile sf::Vector3<double> result(vector_v3f3);
            static_cast<void>(result);
        }
    }
}

BENCHMARK(BM_Vector3D_Compare);

// basic example, copy std::string
static void BM_StringCopy(benchmark::State& state) {
    std::string x = "hello";

    for(auto _ : state) {
        std::string copy(x);
    }
}

BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();

#pragma clang diagnostic pop
