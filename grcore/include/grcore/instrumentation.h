/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the instrumentation.h class.
 * \file       instrumentation.h
 * \date       2020-03-25
 * \author     Jedzia.
 *
 * modified    2020-03-25, Jedzia
 */
/*---------------------------------------------------------*/

// Usage: include this header file somewhere in your code (eg. precompiled header), and then use
// like:
//
// Instrumentor::Get().BeginSession("Session Name");        // Begin session
// {
//     InstrumentationTimer timer("Profiled Scope Name");   // Place code like this in scopes you'd
// like to include in profiling
//     // Code
// }
// Instrumentor::Get().EndSession();                        // End Session
//
// You will probably want to macro-fy this, to switch on/off easily and use things like __FUNCSIG__
// for the profile name.
// Jedzia, comment :
// https://gist.github.com/TheCherno/31f135eea6ee729ab5f26a6908eb3a5e#gistcomment-3227113

#ifndef OPENGLTEMPLATE_609F3B0194144707BCFEE246D8A15CB2_INSTRUMENTATION_H
#define OPENGLTEMPLATE_609F3B0194144707BCFEE246D8A15CB2_INSTRUMENTATION_H

#include <algorithm>
#include <chrono>
#include <fstream>
#include <mutex>
#include <string>
#include <thread>

#define PROFILING 1
#ifdef PROFILING
#  define PROFILE_SCOPE(name) InstrumentationTimer timer ## __LINE__(name)
#  define PROFILE_FUNCTION()  PROFILE_SCOPE(__FUNCTION__)
#else
#  define PROFILE_SCOPE(name)
#endif

struct ProfileResult
{
    const std::string name;
    long long start, end;
#if 1 // M64_Bit
    std::thread::id threadID;
#else
    uint32_t threadID;
#endif
};

class Instrumentor {
    std::string m_sessionName = "None";
    std::ofstream m_outputStream;
    int m_profileCount = 0;
    std::mutex m_lock;
    bool m_activeSession = false;

    Instrumentor() { }

public:

    static Instrumentor &Instance() {
        static Instrumentor instance;
        return instance;
    }

    ~Instrumentor() {
        endSession();
    }

    void beginSession(const std::string &name, const std::string &filepath = "results.json") {
        if(m_activeSession) { endSession(); }

        m_activeSession = true;
        m_outputStream.open(filepath);
        writeHeader();
        m_sessionName = name;
    }

    void endSession() {
        if(!m_activeSession) { return; }

        m_activeSession = false;
        writeFooter();
        m_outputStream.close();
        m_profileCount = 0;
    }

    void writeProfile(const ProfileResult &result) {
        std::lock_guard<std::mutex> lock(m_lock);

        if(m_profileCount++ > 0) { m_outputStream << ","; }

        std::string name = result.name;
        std::replace(name.begin(), name.end(), '"', '\'');

        m_outputStream << "{";
        m_outputStream << "\"cat\":\"function\",";
        m_outputStream << "\"dur\":" << (result.end - result.start) << ',';
        m_outputStream << "\"name\":\"" << name << "\",";
        m_outputStream << "\"ph\":\"X\",";
        m_outputStream << "\"pid\":0,";
        m_outputStream << "\"tid\":" << result.threadID << ",";
        m_outputStream << "\"ts\":" << result.start;
        m_outputStream << "}";
    } // writeProfile

    void writeHeader() {
        m_outputStream << "{\"otherData\": {},\"traceEvents\":[";
    }

    void writeFooter() {
        m_outputStream << "]}";
    }
};

class InstrumentationTimer {
#if 1 // MinGW, see https://github.com/msys2/MINGW-packages/issues/5086#issuecomment-476499828
    typedef std::chrono::steady_clock clock;
#else
    typedef std::chrono::high_resolution_clock clock;
#endif
    ProfileResult m_result;

    std::chrono::time_point<clock> m_startTimepoint;
    bool m_stopped;

public:

    InstrumentationTimer(const std::string &name) : m_result({ name, 0, 0, {}
                }),
        m_stopped(false)
    {
        m_startTimepoint = clock::now();
    }

    ~InstrumentationTimer() {
        if(!m_stopped) { stop(); }
    }

    void stop() {
        auto endTimepoint = clock::now();

        m_result.start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint).time_since_epoch().count();
        m_result.end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();
/*#pragma clang diagnostic push
   #pragma clang diagnostic ignored "-Wunused-variable"
        auto timeS = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTimepoint);
        auto timeE = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint);
        auto diff = timeE - timeS;
 #pragma clang diagnostic pop*/
        //m_result.threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
        m_result.threadID = std::this_thread::get_id(); // is typedef unsigned __int64 uintptr_t
        Instrumentor::Instance().writeProfile(m_result);

        m_stopped = true;
    }
};

#endif//OPENGLTEMPLATE_609F3B0194144707BCFEE246D8A15CB2_INSTRUMENTATION_H
