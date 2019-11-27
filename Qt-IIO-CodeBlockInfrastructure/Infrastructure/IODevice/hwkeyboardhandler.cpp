#include "hwkeyboardhandler.h"

#include <QDebug>
#include <QFileInfo>
#include <QKbdDriverFactory>
#include <QWSKeyboardHandler>
#include <QWSServer>
#include <QString>

HwKeyboardHandler::HwKeyboardHandler(const QString &eventFilePath, QObject *parent):
    QObject(parent),
    m_eventFilePath(eventFilePath),
    m_keyboardIsPresent(false)
{
    // First initialization
    closeKeyboard();
    onDirectoryChanged(QString());
}

void HwKeyboardHandler::onDirectoryChanged(const QString &path)
{
    Q_UNUSED(path);

    QFileInfo eventFilePathInfo(m_eventFilePath);
    if (!m_keyboardIsPresent && eventFilePathInfo.exists()) {
        setKeyboard();
        qDebug() << "Keyboard at " + m_eventFilePath << " set";
    } else if (m_keyboardIsPresent && !eventFilePathInfo.exists()) {
        closeKeyboard();
        qDebug() << "Keyboard at " + m_eventFilePath << " closed";
    }
}

void HwKeyboardHandler::setKeyboard()
{
    QWSKeyboardHandler *pKeyboardHandler =
            QKbdDriverFactory::create("LinuxInput", m_eventFilePath);
    QWSServer* pQwsServer = QWSServer::instance();
    pQwsServer->setKeyboardHandler(pKeyboardHandler);
    m_keyboardIsPresent = true;
}

void HwKeyboardHandler::closeKeyboard()
{
    QWSServer* pQwsServer = QWSServer::instance();
    pQwsServer->closeKeyboard();
    m_keyboardIsPresent = false;
}
