#ifndef HWKEYBOARDSHANDLER_H
#define HWKEYBOARDSHANDLER_H

#include <QObject>

class QFileSystemWatcher;

class HwKeyboardsHandler : public QObject
{
    Q_OBJECT
public:
    explicit HwKeyboardsHandler(QObject *parent = 0);

public slots:
    void addHwKeyboard(const QString &inputEventFilePath);
private:
    QFileSystemWatcher *m_fsWatcher;
};

#endif // HWKEYBOARDSHANDLER_H
