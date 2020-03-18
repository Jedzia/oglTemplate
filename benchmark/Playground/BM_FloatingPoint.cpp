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
//
// Created by Jedzia on 03.11.2018.
//

#include <SFML/System/Vector3.hpp>
#include <benchmark/benchmark.h>

constexpr unsigned int ITERATIONS = 1000;

// Define another benchmark
static void BM_DoubleCreation(benchmark::State& state) {
    for(auto _ : state)
    {
        volatile double empty_double;
        static_cast<void>(empty_double);
    }
}

// Register the function as a benchmark
BENCHMARK(BM_DoubleCreation);

// Define another benchmark
static void BM_Vector3F_CreateDefault(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < 1000; ++i) {
            volatile sf::Vector3<float> result;
            static_cast<void>(result);
        }
    }
}

// Register the function as a benchmark
BENCHMARK(BM_Vector3F_CreateDefault);

// Define another benchmark
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

// Register the function as a benchmark
BENCHMARK(BM_Vector3F_CopyDefault);

// Define another benchmark
static void BM_Vector3F_Copy123(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < ITERATIONS; ++i) {
            sf::Vector3<float> vector_v3f1(1,2,3);
            volatile sf::Vector3<float> result(vector_v3f1);
            static_cast<void>(result);
        }
    }
}

// Register the function as a benchmark
BENCHMARK(BM_Vector3F_Copy123);

// Define another benchmark
static void BM_Vector3F_Add(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < ITERATIONS; ++i) {
            sf::Vector3<float> vector_v3f1(1,2,3);
            sf::Vector3<float> vector_v3f2(1,2,3);
            sf::Vector3<float> vector_v3f3(1,2,3);
            vector_v3f3 = vector_v3f1 + vector_v3f2;
            volatile sf::Vector3<float> result(vector_v3f3);
            static_cast<void>(result);
        }
    }
}

// Register the function as a benchmark
BENCHMARK(BM_Vector3F_Add);

// Define another benchmark
static void BM_Vector3F_Mul(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < ITERATIONS; ++i) {
            sf::Vector3<float> vector_v3f1(1,2,3);
            sf::Vector3<float> vector_v3f2(1,2,3);
            sf::Vector3<float> vector_v3f3(1,2,3);
            vector_v3f3 = vector_v3f1 * vector_v3f2.x;
            volatile sf::Vector3<float> result(vector_v3f3);
            static_cast<void>(result);
        }
    }
}

// Register the function as a benchmark
BENCHMARK(BM_Vector3F_Mul);

// Define another benchmark
static void BM_Vector3D_Add(benchmark::State& state) {
    for(auto _ : state)
    {
        for(int i = 0; i < ITERATIONS; ++i) {
            sf::Vector3<double> vector_v3d1(1,2,3);
            sf::Vector3<double> vector_v3d2(1,2,3);
            sf::Vector3<double> vector_v3d3(1,2,3);
            vector_v3d3 = vector_v3d1 + vector_v3d2;
            volatile sf::Vector3<double> result(vector_v3d3);
            static_cast<void>(result);
        }
    }
}

// Register the function as a benchmark
BENCHMARK(BM_Vector3D_Add);

// Define another benchmark
static void BM_Vector3FCopy(benchmark::State& state) {
    sf::Vector3<float> x(0, 0, 0);

    for(auto _ : state) {
        sf::Vector3<float> copy(x);
    }
}

BENCHMARK(BM_Vector3FCopy);

// Define another benchmark
static void BM_StringCopy(benchmark::State& state) {
    std::string x = "hello";

    for(auto _ : state) {
        std::string copy(x);
    }
}

BENCHMARK(BM_StringCopy);

BENCHMARK_MAIN();

/*#include <iostream>
   int main()
   {
    std::cout << "Fuck You!" << std::endl;
    return 0;
   }*/
#pragma clang diagnostic pop
