#include "hwinputdevice.h"

#include <QDebug>
#include <QFileInfo>

namespace qt_iio_cc {
namespace infrastructure {
namespace iodevice {

HwInputDevice::HwInputDevice(const QString &eventFilePath,
                             QObject *parent) :
    QObject(parent),
    m_eventFilePath(eventFilePath),
    m_isPresent(false)
{

}

void HwInputDevice::set()
{
    if (connected()) {
        setImpl();
        m_isPresent = true;
    }
}

void HwInputDevice::close()
{
    m_isPresent = false;
}

bool HwInputDevice::connected()
{
    return !m_isPresent && QFileInfo(m_eventFilePath).exists();
}

bool HwInputDevice::disconnected()
{
    return m_isPresent && !QFileInfo(m_eventFilePath).exists();
}

} // namespace iodevice
} // namespace infrastructure
} // namespace qt_iio_cc
