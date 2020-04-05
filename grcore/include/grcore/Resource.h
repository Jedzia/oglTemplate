/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the resource.h class.
 * \file       resource.h
 * \date       2020-03-25
 * \author     Jedzia.
 *
 * modified    2020-04-05, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef OPENGLTEMPLATE_E425AE61B7064A80B6F46CA476262B60_RESOURCE_H
#define OPENGLTEMPLATE_E425AE61B7064A80B6F46CA476262B60_RESOURCE_H

#include <tuple>

namespace grcore {
/** @class Resource: Interface to embedded resources.
 *  Provides access to embedded resources.
 */
class Resource final {
public:

    /**
     * @brief Create a resource proxy by resource-id.
     *
     * Currently only the resource type "BINARY" is used.
     * @param The resource-id as specified in the .rc file.
     * @example
     * @code
     * #define IDR_MYFONT  129
     * IDR_MYFONT BINARY "@CURRENT_RESOURCE_DIR@/FiraCode-Regular.ttf"
     * @endcode
     *
     * @code
     *  const int fontId = 129;
     *  grcore::Resource res(fontId);
     *  auto [data, size, error] = res.Get();
     * @endcode
     */
    Resource(int resourceName);

    ~Resource();

    /** Through Resource, Get you can access the underlying data.
     *
     *  The underlying resource data is retrieved via FindResourceW. For this to
	 *  work this has to be in a dynamic loadable module. Here the handle is retrieved
	 *  via DllMain or as fallback ::GetModuleHandleW(L"libGrCore.dll").
     *  @return a tuple with the elements <tt>data</tt> pointing to the resource,
	 *  <tt>size</tt> which indicates the size of the resource and 
	 *  <tt>error</tt> containing an error number or zero if the operation was
	 *  successful.
     *  @example
     *  @code
     *  const int fontId = 129;
     *  grcore::Resource res(fontId);
     *  auto [data, size, error] = res.Get();
     *  @endcode
     */
    [[nodiscard]] std::tuple<const void *, size_t, int> Get();

private:

    int m_id = 0;
};
}// namespace core

#endif//OPENGLTEMPLATE_E425AE61B7064A80B6F46CA476262B60_RESOURCE_H
