#include "hwkeyboardhandler.h"

#include <QDebug>
#include <QFileInfo>
#include <QKbdDriverFactory>
#include <QWSKeyboardHandler>
#include <QWSServer>
#include <QString>

namespace qt_iio_cc {
namespace infrastructure {
namespace iodevice {

HwKeyboardHandler::HwKeyboardHandler(const QString &eventFilePath, QObject *parent):
    HwInputDevice(eventFilePath, parent)
{
}

void HwKeyboardHandler::closeAll()
{
    QWSServer* qwsServer = QWSServer::instance();
    qwsServer->closeKeyboard();
}

void HwKeyboardHandler::setImpl()
{
    QWSKeyboardHandler *keyboardHandler =
            QKbdDriverFactory::create("LinuxInput", m_eventFilePath);
    QWSServer* qwsServer = QWSServer::instance();
    qwsServer->setKeyboardHandler(keyboardHandler);
    qDebug() << "Keyboard at \"" << m_eventFilePath << "\" set";
}

} // iodevice
} // infrastructure
} // qt_iio_cc
