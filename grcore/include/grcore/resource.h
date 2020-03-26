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
 * modified    2020-03-25, Jedzia
 */
/*---------------------------------------------------------*/
//
// Created by Jedzia on 26.03.2020.
//

#ifndef OPENGLTEMPLATE_184BD536C24F498D954956C919487BF7_RESOURCE_H
#define OPENGLTEMPLATE_184BD536C24F498D954956C919487BF7_RESOURCE_H

namespace core {
class Resource {
  public:
    Resource(int mId);

    void Get();
  private:
int m_id=0;
};
}// namespace core

#endif//OPENGLTEMPLATE_184BD536C24F498D954956C919487BF7_RESOURCE_H
