#ifndef HWMOUSEHANDLER_H
#define HWMOUSEHANDLER_H

#include <Infrastructure/IODevice/hwinputdevice.h>
#include <QString>

namespace qt_iio_cc {
namespace infrastructure {
namespace iodevice {

class HwMouseHandler : public HwInputDevice
{
    Q_OBJECT
public:
    HwMouseHandler(const QString &eventFilePath, QObject *parent = 0);
    static void closeAll();
private:
    void setImpl();
};

} // namespace iodevice
} // namespace infrastructure
} // namespace qt_iio_cc

#endif // HWMOUSEHANDLER_H
