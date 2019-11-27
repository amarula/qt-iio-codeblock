QT_IIO_CODEBLOCK_ROOT=$$PWD

CONFIG(release, debug|release) {
    BUILD_SUB_DIR = release
    OBJECTS_DIR = release/.obj
    MOC_DIR = release/.moc
    RCC_DIR = release/.rcc
    UI_DIR = release/.ui

    QT_IIO_CODEBLOCK_BUILD_ROOT=$$PWD/../build-release
    !build_pass:message($$_PRO_FILE_PWD_ release build)
} else {
    BUILD_SUB_DIR = debug
    OBJECTS_DIR = debug/.obj
    MOC_DIR = debug/.moc
    RCC_DIR = debug/.rcc
    UI_DIR = debug/.ui

    QT_IIO_CODEBLOCK_BUILD_ROOT=$$PWD/../build-debug
    DEFINES += DEBUG

    QT += testlib

    !build_pass:message($$_PRO_FILE_PWD_ debug build)
}
