#include "hwinputdevicesscanner.h"

#include <errno.h>
#include <fcntl.h>
#include <libinput.h>
#include <QDir>
#include <QFileInfo>
#include <unistd.h>

namespace qt_iio_cc {
namespace infrastructure {
namespace iodevice {

namespace {
    int open_restricted(const char *path, int flags, void *)
    {
        int fd = open(path, flags);
        return fd < 0 ? -errno : fd;
    }

    void close_restricted(int fd, void *)
    {
        close(fd);
    }

    const static struct libinput_interface interface =
    {
            .open_restricted = open_restricted,
            .close_restricted = close_restricted,
    };

    bool getIODeviceType(struct libinput *libInput, const QString &file, HwIODeviceType &type)
    {
        bool succeed = false;
        struct libinput_device *device =
                libinput_path_add_device(libInput, file.toLatin1().constData());
        if (device) {
            libinput_device_ref(device);
            if (libinput_device_has_capability(device, LIBINPUT_DEVICE_CAP_KEYBOARD)) {
                type = HwIODeviceType_Keyboard;
                succeed = true;
            }
            if (libinput_device_has_capability(device, LIBINPUT_DEVICE_CAP_POINTER)) {
                type = HwIODeviceType_Mouse;
                succeed = true;
            }
            libinput_path_remove_device(device);
            libinput_device_unref(device);
        }
        return succeed;
    }
}

QList<QPair<HwIODeviceType, QString> > HwInputDevicesScanner::scanFolders(const QStringList &paths)
{
    QList<QPair<HwIODeviceType, QString> > retVal;
    struct libinput *libInput = libinput_path_create_context(&interface, NULL);
    if (libInput) {
        libinput_ref(libInput);
        for (int i = 0; i < paths.size(); ++i) {
            const QString &path = paths[i];
            QFileInfoList files = QDir(path).entryInfoList(QDir::System | QDir::Files);
            for (int j = 0; j < files.size(); ++j) {
                QString absoluteFilePath = files[j].absoluteFilePath();
                HwIODeviceType type;
                if (getIODeviceType(libInput, absoluteFilePath, type)) {
                    retVal << QPair<HwIODeviceType,QString>(type, absoluteFilePath);
                }
            }
        }
        libinput_unref(libInput);
    }
    return retVal;
}

} // iodevice
} // infrastructure
} // qt_iio_cc
