#ifndef HWINPUTDEVICESSCANNER_H
#define HWINPUTDEVICESSCANNER_H

#include <QList>
#include <QPair>

#include <Infrastructure/IODevice/hwiodevicetypes.h>

namespace qt_iio_cc {
namespace infrastructure {
namespace iodevice {

class HwInputDevicesScanner
{
public:
    static QList<QPair<HwIODeviceType, QString> > scanFolders(const QStringList &paths);
};

} // iodevice
} // infrastructure
} // qt_iio_cc


#endif // HWINPUTDEVICESSCANNER_H
