#ifndef HWINPUTDEVICESHANDLER_H
#define HWINPUTDEVICESHANDLER_H

#include <Infrastructure/IODevice/hwiodevicetypes.h>
#include <QMap>
#include <QObject>
#include <QSet>
#include <QString>
#include <QStringList>

class QFileSystemWatcher;

namespace qt_iio_cc {
namespace infrastructure {
namespace iodevice {

class HwKeyboardHandler;
class HwMouseHandler;

class HwInputDevicesHandler : public QObject
{
    Q_OBJECT
public:
    explicit HwInputDevicesHandler(QObject *parent = 0);
    void start(const QStringList &paths);
public slots:
    void addHwIODevice(HwIODeviceType type, const QString &inputEventFilePath);
private slots:
    void onDirectoryChanged(const QString &path);
private:
    void checkKeyboards();
    void reloadKeyboards();
    void checkMice();
    void reloadMice();
    void scanForNewDevices();
    QFileSystemWatcher *m_fsWatcher;
    QMap<QString, HwKeyboardHandler*> m_keyboards;
    QMap<QString, HwMouseHandler*> m_mice;
    QStringList m_paths;
};

} // iodevice
} // infrastructure
} // qt_iio_cc

#endif // HWINPUTDEVICESHANDLER_H
