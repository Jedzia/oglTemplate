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
#include "return_type_trait.h"
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

namespace core {
namespace util {
class PropertyBase {
public:

    virtual ~PropertyBase() {}

    virtual bool HasChanged() = 0;
};

template<typename TFunctor>
class Property final : public PropertyBase {
public:

    typedef return_type_t<TFunctor> StorageType;
    Property(TFunctor updater) : m_updater(updater) {
        m_value = updater();
        /*std::cout << "+++ Constructor " << __PRETTY_FUNCTION__ << " -> " <<
            ": " << m_value << " called. +++" << std::endl;*/
    }

    ~Property() {
        //std::cout << "+++ Destructor  " << __PRETTY_FUNCTION__ << " called. +++" << std::endl;
    }

    Property(const Property &) = delete;  // non construction-copyable
    Property &operator=(const Property &) = delete;  // non copyable

    [[nodiscard]] bool HasChanged() override {
        auto newValue = m_updater();
        std::cout << "newValue: " << newValue << std::endl;
        bool result = newValue != m_value;
        m_value = newValue;
        return result;
    }

    [[nodiscard]] const StorageType &Get() const {
        return m_value;
    }

private:

    StorageType m_value;
    TFunctor m_updater;
};

//template<typename T>
class PropertyList final {
public:

    typedef std::shared_ptr<PropertyBase> PropertyType;
    void Add(PropertyType property) {
        //std::cout << "Add(Property<T>&) typeid(T): " << typeid(property).name() << std::endl;
        m_storage.push_back(property);
    }

    template<typename TFunctor>
    void AddProp(TFunctor func) {
        //std::cout << "AddProp(TFunctor func) typeid(T): " << typeid(func).name() << std::endl;
        Add(std::make_shared<core::util::Property<std::function<return_type_t<TFunctor>(void)>>>(func));
    }

    [[nodiscard]] bool HasChanged() {
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
