/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the console.h class.
 * \file       console.h
 * \date       2020-03-26
 * \author     Jedzia.
 *
 * modified    2020-03-26, Jedzia
 */
/*---------------------------------------------------------*/
//
// Created by Jedzia on 27.03.2020.
//

#ifndef OPENGLTEMPLATE_AEE9CED07DB246BA94D682680063898C_CONSOLE_H
#define OPENGLTEMPLATE_AEE9CED07DB246BA94D682680063898C_CONSOLE_H
namespace core {
enum ConsoleCheckResult {
    Windows = -1,
    None = 0,
    MSys = 1
};

[[nodiscard]]  ConsoleCheckResult checkConsole();
}
#endif//OPENGLTEMPLATE_AEE9CED07DB246BA94D682680063898C_CONSOLE_H
