#ifndef QT_IIO_CC_INFRASTRUCTURE_INFRASTRUCTURE_H
#define QT_IIO_CC_INFRASTRUCTURE_INFRASTRUCTURE_H


#include <QScopedPointer>
#include <QtGlobal>

namespace qt_iio_cc {
namespace infrastructure {

class Infrastructure
{
public:
    static Infrastructure& getInstance();
    bool initialize();
private:
    Infrastructure();
    struct Private;
    QScopedPointer<Private> m_p;
    Q_DISABLE_COPY(Infrastructure)
};


} // namespace infrastructure
} // namespace qt_iio_cc

#endif // QT_IIO_CC_INFRASTRUCTURE_INFRASTRUCTURE_H
