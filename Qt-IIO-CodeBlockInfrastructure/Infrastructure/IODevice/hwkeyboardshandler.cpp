#include "hwkeyboardshandler.h"

#include "hwkeyboardhandler.h"
#include <QFileInfo>
#include <QFileSystemWatcher>

HwKeyboardsHandler::HwKeyboardsHandler(QObject *parent): QObject(parent),
    m_fsWatcher(new QFileSystemWatcher(this))
{

}

void HwKeyboardsHandler::addHwKeyboard(const QString &inputEventFilePath)
{
    m_fsWatcher->addPath(QFileInfo(inputEventFilePath).path());
    HwKeyboardHandler *hwKeyboardHandler = new HwKeyboardHandler(inputEventFilePath, this);
    connect(m_fsWatcher, SIGNAL(directoryChanged(QString)),
            hwKeyboardHandler, SLOT(onDirectoryChanged(QString)));
}
