#include "infrastructure.h"

#include <Infrastructure/IODevice/hwkeyboardshandler.h>

namespace qt_iio_cc {
namespace infrastructure {

struct Infrastructure::Private {
    HwKeyboardsHandler hwKeyboardsHandler;
};

Infrastructure &Infrastructure::getInstance()
{
    static Infrastructure inst;
    return inst;
}

bool Infrastructure::initialize()
{
    //@TODO: Allow library user to specify the keyboards somehow
    m_p->hwKeyboardsHandler.addHwKeyboard("/dev/input/event4");
    return true;
}

Infrastructure::Infrastructure():
    m_p(new Private)
{

}


} // namespace infrastructure
} // namespace qt_iio_cc
