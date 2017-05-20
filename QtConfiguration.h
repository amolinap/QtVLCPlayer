/**
 * @file
 *   @brief Definition of Configuration file
 *
 *   @author Alejandro Molina Pulido <am.alex09@gmail.com>
 */
#ifndef QTCONFIGURATION_H
#define QTCONFIGURATION_H

#include <QObject>
#include <QDateTime>
#include <QThread>

/**
 * @brief The configuration file
 *
 * This file represents the configuration to Application
 * The namespace QtConfiguration identifies to App configuration
 */
namespace QtConfiguration
{
#define APP_NAME "Administrador de Video"
#define APP_COMPANYNAME "SEMAR"
#define APP_LICENSE "Derechos Reservados"
#define APP_VERSION "1.0"
#define APP_BUILT_ON "MAYO 2017"
}
#endif // QTCONFIGURATION_H
