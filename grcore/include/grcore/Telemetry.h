/*---------------------------------------------------------*/
/*!
 * This file is part of OpenGLTemplate, R&D.
 * License details can be found in the file COPYING.
 * Copyright (c) 2020, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Telemetry.h class.
 * \file       Telemetry.h
 * \date       2020-04-04
 * \author     Jedzia.
 *
 * modified    2020-04-04, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef OPENGLTEMPLATE_387669B53EBE4EF893F0720652096DB8_TELEMETRY_H
#define OPENGLTEMPLATE_387669B53EBE4EF893F0720652096DB8_TELEMETRY_H

namespace grcore {
/** Send a double datum over the telemetry interface.
 *
 *  Uses grcore::util::TcpClient to send the specified data to the default telemetry endpoint. If
 *  an error occurs, all further sending is switched off and this routine returns false. This can
 *  occur when a connection is lost or no connection to the telemetry host can be made.
 *  @param data Double precision floating point data to transmit.
 *  @return <b>true</b> on success/transmit without error; otherwise <b>false</b>.
 */
bool writeData(const double &data);

/** @class Telemetry:
 *  Placeholder for later functionality.
 */
class Telemetry {};
}

#endif //OPENGLTEMPLATE_387669B53EBE4EF893F0720652096DB8_TELEMETRY_H
