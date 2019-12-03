#include "hwmousehandler.h"

#include <QDebug>
#include <QFileInfo>
#include <QMouseDriverFactory>
#include <QWSMouseHandler>
#include <QWSServer>
#include <QString>

namespace qt_iio_cc {
namespace infrastructure {
namespace iodevice {

HwMouseHandler::HwMouseHandler(const QString &eventFilePath, QObject *parent):
    HwInputDevice(eventFilePath, parent)
{
}

void HwMouseHandler::closeAll()
{
    QWSServer* qwsServer = QWSServer::instance();
    qwsServer->closeMouse();
}

void HwMouseHandler::setImpl()
{
    QWSMouseHandler *mouseHandler =
            QMouseDriverFactory::create("LinuxInput", m_eventFilePath);
    QWSServer* qwsServer = QWSServer::instance();
    qwsServer->setMouseHandler(mouseHandler);
    m_isPresent = true;
    qDebug() << "Mouse at \"" << m_eventFilePath << "\" set";
}

} // namespace iodevice
} // namespace infrastructure
} // namespace qt_iio_cc
