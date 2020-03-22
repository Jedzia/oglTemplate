/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the create_window.cpp class.
 * \file       create_window.cpp
 * \date       2020-01-23
 * \author     Jedzia.
 *
 * modified    2020-01-23, Jedzia
 */
/*---------------------------------------------------------*/

#include <fmt/printf.h>
#include <grcore/wgl_common.h>
#include <iostream>
#include <afsm/fsm.hpp>
//
#include <winuser.h>

using namespace std;

// see https://github.com/zmij/afsm/tree/c++17/examples
// Events
struct start {
    template <typename Event, typename FSM>
    void
    operator()(Event const&, FSM& fsm) const
    {
        cout << "OPERATOR reload" << endl;
        root_machine(fsm).reload();
    }
};
struct stop {
    void operator()() const
    {
        cout << "OPERATOR stop" << endl;
    }
};

void p(const std::string& msg) {
    cout << "" << msg << "" << endl;
}

// Actions
struct do_start{
    template < typename Event, typename FSM, typename SourceState, typename TargetState >
    void
    operator()(Event const&, FSM& fsm, SourceState&, TargetState&) const
    {
        p("do start");
        root_machine(fsm).doSomething();
    }
};
struct do_stop {
    template < typename Event, typename FSM, typename SourceState, typename TargetState >
    void
    operator()(Event const&, FSM&, SourceState&, TargetState&) const
    {
        p("do stop");
    }
};


// State machine definition
struct minimal_def : ::afsm::def::state_machine<minimal_def> {
    //@{
    /** @name States */
    struct initial      : state<initial> {  };
    struct running      : state<running> {
        template < typename Event, typename FSM >
        void
        on_enter(Event&& /*evt*/, FSM& /*fsm*/)
        {
            ::std::cout << "state<running> enter" << ::std::endl;
        }
        template < typename Event, typename FSM >
        void
        on_exit(Event const& /*evt*/, FSM& /*fsm*/)
        {
            ::std::cout << "state<running> exit" << ::std::endl;
        }
    };
    struct terminated   : terminal_state<terminated> {};
    //@}

    using initial_state = initial;
    using transitions   = transition_table<
    /*  State       Event       Next          Action  */
    tr< initial,    start,      running,     do_start     >,
    tr< running,    stop,       terminated,  do_stop      >
    >;

    static void doSomething() {
        cout << "doSomething()" << endl;
    }
};

// State machine object
using minimal = ::afsm::state_machine<minimal_def>;

void use()
{
    //int x = 5;
    minimal fsm{};
    fsm.process_event(start{});
    fsm.process_event(stop{});
}

/** Program Entry Function, main
 *  The designated start of the program.
 *  @return program exit code.
 */
int main(){ // the main code portion of a C++ program
    cout << "Hello cheesy World" << endl;  //print Hello World on the screen
    //make_window_and_test(test_function);
    /* UNREACHED */
    use();
    return 0;
}
