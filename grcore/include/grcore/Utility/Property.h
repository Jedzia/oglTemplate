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

/// @ref

#ifndef OPENGLTEMPLATE_E43883E2425644289F6B9D667ED895C3_PROPERTY_H
#define OPENGLTEMPLATE_E43883E2425644289F6B9D667ED895C3_PROPERTY_H
#include "return_type_trait.h"
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

namespace grcore {
namespace util {
/** @class PropertyBase
 *  @brief Basic interface for util::PropertyList to store util::Property instances.
 */
struct PropertyBase {
    virtual ~PropertyBase() {}

    /** @brief Check if the monitored property has changed.
     *
     *  Calls the stored update-function and compares the new value against the stored backup.
     *  The new value becomes the stored backup for later comparissons.
     *  @return <b>true</b> if the property has changed; otherwise <b>false</b>.
     */
    virtual bool HasChanged() = 0;
};

/** @class Property
 *  @brief Stores a property and its update mechanism.
 *
 *  The underlying type of the storage item can be retrieved via <tt>Property::StorageType</tt>.
 *  @tparam TFunctor Specifies the type of the functor object providing the property data.
 */
template<typename TFunctor>
class Property final : public PropertyBase {
public:

    /** @brief Storage type of the property.
     *
     *  Defines the type which is produced by the TFunctor updateFunc.
     *  @code
     *  int a = 7;
     *  auto p1 = grcore::util::Property([&a]() { return a; });
     *  @endcode
     *  Here the StorageType becomes <tt>int</tt>.
     */
    typedef return_type_t<TFunctor> StorageType;

    /** @brief Construct the Property from an updater.
     *
     *  Entangle the watched property via a lambda or function to this instance.
     *  @param updateFunc Function or lambda to retrieve the value of the monitored property.
     */
    Property(TFunctor updateFunc) : m_updater(updateFunc) {
        m_value = updateFunc();
        /*std::cout << "+++ Constructor " << __PRETTY_FUNCTION__ << " -> " <<
        ": " << m_value <<" type: " << typeid(StorageType).name() << " called. +++" << std::endl;*/
    }

    ~Property() {
        //std::cout << "+++ Destructor  " << __PRETTY_FUNCTION__ << " called. +++" << std::endl;
    }

    Property(const Property &) = delete;  // non construction-copyable
    Property &operator=(const Property &) = delete;  // non copyable

    [[nodiscard]] bool HasChanged() override {
        auto newValue = m_updater();
        //std::cout << "newValue: " << newValue << std::endl;
        bool result = newValue != m_value;
        m_value = newValue;
        return result;
    }

    /** @brief Get the stored property value.
     *  @return the stored value since construction or the last HasChanged() call.
     */
    [[nodiscard]] const StorageType &Get() const {
        return m_value;
    }

private:

    StorageType m_value;
    TFunctor m_updater;
    //unsigned long long m_counter; // a possible counter to track most uses and sort them on top of
    // the m_storage list.
};

/** @class PropertyList
 *  @brief A Container for Property items.
 *  @tparam TFunctor Specifies the type of the functor object providing the property data.
 */
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
        Add(std::make_shared<grcore::util::Property<std::function<return_type_t<TFunctor>(void)>>>(func));
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
