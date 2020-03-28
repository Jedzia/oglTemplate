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
#include <functional>
#include <iostream>
#include <memory>
#include <vector>
namespace core {
namespace util {
template<typename T>
class Property final {
public:

    Property(std::function<T(void)> updater) : m_updater(updater) {
        m_value = updater();
        std::cout << "+++ Constructor " << __PRETTY_FUNCTION__ << " -> " <<
            ": " << m_value << " called. +++" << std::endl;
    }

    Property(const Property &) = delete;  // non construction-copyable
    Property &operator=(const Property &) = delete;  // non copyable

    bool HasChanged() {
        auto newValue = m_updater();
        std::cout << "newValue: " << newValue << std::endl;
        bool result = newValue != m_value;
        m_value = newValue;
        return result;
    }

    const T &Get() const {
        return m_value;
    }

private:

    T m_value;
    std::function<T(void)> m_updater;
};

template<typename T>
class PropertyList final {
public:

    typedef std::shared_ptr<Property<T>> PropertyType;
    void Add(PropertyType property) {
        //static_cast<void>(property);
        std::cout << "Add(Property<T>&) typeid(T): " << typeid(property).name() << std::endl;
        m_storage.push_back(property);
    }

    bool HasChanged() {
        for(auto item : m_storage) {
            //std::cout << "HasChanged() =" << item->Get() << std::endl;
            if(item->HasChanged()) {
                return true;
            }
        }
        return false;
    }

private:

    std::vector<PropertyType> m_storage;
};
}// namespace util
}// namespace core
#endif//OPENGLTEMPLATE_E43883E2425644289F6B9D667ED895C3_PROPERTY_H
