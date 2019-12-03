#include "hwinputdeviceshandler.h"

#include <Infrastructure/IODevice/hwinputdevicesscanner.h>
#include <Infrastructure/IODevice/hwkeyboardhandler.h>
#include <Infrastructure/IODevice/hwmousehandler.h>
#include <QFileInfo>
#include <QFileSystemWatcher>

namespace qt_iio_cc {
namespace infrastructure {
namespace iodevice {

HwInputDevicesHandler::HwInputDevicesHandler(QObject *parent): QObject(parent),
    m_fsWatcher(new QFileSystemWatcher(this))
{
    connect(m_fsWatcher, SIGNAL(directoryChanged(QString)),
            this, SLOT(onDirectoryChanged(QString)));
}

void HwInputDevicesHandler::start(const QStringList &paths)
{
    m_fsWatcher->removePaths(m_paths);
    m_paths = paths;
    m_fsWatcher->addPaths(m_paths);
    scanForNewDevices();
    reloadKeyboards();
    reloadMice();
}

void HwInputDevicesHandler::addHwIODevice(HwIODeviceType type, const QString &inputEventFilePath)
{
    if (type == HwIODeviceType_Keyboard) {
        if (!m_keyboards.keys().contains(inputEventFilePath)) {
            HwKeyboardHandler *keyboard = new HwKeyboardHandler(inputEventFilePath, this);
            m_keyboards.insert(inputEventFilePath, keyboard);
        }
    } else if (type == HwIODeviceType_Mouse) {
        if (!m_mice.keys().contains(inputEventFilePath)) {
            HwMouseHandler *mouse = new HwMouseHandler(inputEventFilePath, this);
            m_mice.insert(inputEventFilePath, mouse);
        }
    }
}

void HwInputDevicesHandler::onDirectoryChanged(const QString &path)
{
    Q_UNUSED(path);

    scanForNewDevices();
    checkKeyboards();
    checkMice();
}

void HwInputDevicesHandler::checkKeyboards()
{
    bool reload = false;
    QMapIterator<QString, HwKeyboardHandler*> iter(m_keyboards);
    while (iter.hasNext()) {
        iter.next();
        HwKeyboardHandler *keyboard = iter.value();
        if (keyboard->disconnected()) {
            reload = true;
            break;
        } else if (keyboard->connected()) {
            keyboard->set();
        }
    }
    if (reload) {
        reloadKeyboards();
    }
}

void HwInputDevicesHandler::reloadKeyboards()
{
    HwKeyboardHandler::closeAll();
    QMapIterator<QString, HwKeyboardHandler*> iter(m_keyboards);
    while (iter.hasNext()) {
        iter.next();
        HwKeyboardHandler *keyboard = iter.value();
        keyboard->close();
        keyboard->set();
    }
}

void HwInputDevicesHandler::checkMice()
{
    bool reload = false;
    QMapIterator<QString, HwMouseHandler*> iter(m_mice);
    while (iter.hasNext()) {
        iter.next();
        HwMouseHandler *mouse = iter.value();
        if (mouse->disconnected()) {
            reload = true;
            break;
        } else if (mouse->connected()) {
            mouse->set();
        }
    }
    if (reload) {
        reloadMice();
    }
}

void HwInputDevicesHandler::reloadMice()
{
    HwMouseHandler::closeAll();
    QMapIterator<QString, HwMouseHandler*> iter(m_mice);
    while (iter.hasNext()) {
        iter.next();
        HwMouseHandler *mouse = iter.value();
        mouse->close();
        mouse->set();
    }
}

void HwInputDevicesHandler::scanForNewDevices()
{
    QList<QPair<HwIODeviceType,QString> > hwDevices = HwInputDevicesScanner::scanFolders(m_paths);
    for (int i = 0; i < hwDevices.size(); ++i) {
        HwIODeviceType type = hwDevices[i].first;
        const QString &inputFilePath = hwDevices[i].second;
        if ((type == HwIODeviceType_Keyboard && !m_keyboards.contains(inputFilePath)) ||
                (type == HwIODeviceType_Mouse && !m_mice.contains(inputFilePath))) {
            addHwIODevice(type, inputFilePath);
        }
    }
}

} // iodevice
} // infrastructure
} // qt_iio_cc
