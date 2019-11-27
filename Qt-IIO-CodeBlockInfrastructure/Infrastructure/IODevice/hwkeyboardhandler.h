#ifndef HWKEYBOARDHANDLER_H
#define HWKEYBOARDHANDLER_H

#include <QObject>
#include <QString>

class HwKeyboardHandler: public QObject
{
    Q_OBJECT
public:
    explicit HwKeyboardHandler(const QString &eventFilePath, QObject *parent = 0);

private slots:
    void onDirectoryChanged(const QString &path);

private:
    void setKeyboard();
    void closeKeyboard();

private:
    QString m_eventFilePath;
    bool m_keyboardIsPresent;
};

#endif // HWKEYBOARDHANDLER_H
