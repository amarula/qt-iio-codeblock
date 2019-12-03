#ifndef HWIODEVICE_H
#define HWIODEVICE_H

#include <QObject>

namespace qt_iio_cc {
namespace infrastructure {
namespace iodevice {

class HwInputDevice : public QObject
{
    Q_OBJECT
public:
    explicit HwInputDevice(const QString &eventFilePath,
                           QObject *parent = 0);
    void set();
    void close();
    bool connected();
    bool disconnected();
protected:
    QString m_eventFilePath;
    bool m_isPresent;
private:
    virtual void setImpl() = 0;
};

} // namespace iodevice
} // namespace infrastructure
} // namespace qt_iio_cc

#endif // HWIODEVICE_H
