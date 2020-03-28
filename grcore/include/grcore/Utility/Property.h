/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Property.h class.
 * \file       Property.h
 * \date       2020-03-28
 * \author     Jedzia.
 *
 * modified    2020-03-28, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_E43883E2425644289F6B9D667ED895C3_PROPERTY_H
#define OPENGLTEMPLATE_E43883E2425644289F6B9D667ED895C3_PROPERTY_H
#include <any>
#include <functional>
#include <iostream>
namespace core {
namespace util {
template<typename T>
class Property {
public:

    Property(std::function<T(void)> &updater);
    bool Update();

private:

    std::any m_value;
    std::function<T(void)> &m_updater;
};

template<typename T>
Property<T>::Property(std::function<T(void)> &updater) :  m_updater(updater) {
    m_value = updater();
    std::cout << "+++ Constructor " << __PRETTY_FUNCTION__ << " -> " << m_value.type().name() << ": " << std::any_cast<T>(m_value) <<
        " called. +++" << std::endl;
}

template<typename T>
bool Property<T>::Update() {
    auto newValue = m_updater();
    bool result = newValue != std::any_cast<T>(m_value);
    m_value = newValue;
    return result;
}
}
}
#endif//OPENGLTEMPLATE_E43883E2425644289F6B9D667ED895C3_PROPERTY_H
