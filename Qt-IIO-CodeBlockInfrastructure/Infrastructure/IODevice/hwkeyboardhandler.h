#ifndef HWKEYBOARDHANDLER_H
#define HWKEYBOARDHANDLER_H

#include <Infrastructure/IODevice/hwinputdevice.h>
#include <QString>

namespace qt_iio_cc {
namespace infrastructure {
namespace iodevice {

class HwKeyboardHandler: public HwInputDevice
{
    Q_OBJECT
public:
    explicit HwKeyboardHandler(const QString &eventFilePath, QObject *parent = 0);
    static void closeAll();

private:
    void setImpl();
};

} // iodevice
} // infrastructure
} // qt_iio_cc

#endif // HWKEYBOARDHANDLER_H
