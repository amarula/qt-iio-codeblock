#include "infrastructure.h"

#include <Infrastructure/IODevice/hwinputdeviceshandler.h>

namespace qt_iio_cc {
namespace infrastructure {

struct Infrastructure::Private {
    iodevice::HwInputDevicesHandler hwInputDevicesHandler;
    void initializeIODevices();
};

Infrastructure &Infrastructure::getInstance()
{
    static Infrastructure inst;
    return inst;
}

bool Infrastructure::initialize()
{
    m_p->initializeIODevices();
    return true;
}

Infrastructure::Infrastructure():
    m_p(new Private)
{

}

void Infrastructure::Private::initializeIODevices()
{
    hwInputDevicesHandler.start(QStringList() << "/dev/input/");
}


} // namespace infrastructure
} // namespace qt_iio_cc
