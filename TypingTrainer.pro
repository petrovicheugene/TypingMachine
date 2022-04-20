#-------------------------------------------------
#
# Project created by QtCreator 2019-04-16T17:06:36
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TypingTrainer

#PRO VARS
RC_ICONS = ""

#Application version
VER_MAJ=0
VER_MIN=0
VER_PAT=0
VER_BUILD=b

PRODUCT_DISPLAY_NAME="Typing Trainer"
PRODUCT_FILE_BASE_NAME="typingtrainer"
QMAKE_TARGET_PRODUCT="TypingTrainer"
QMAKE_TARGET_DESCRIPTION="Typing trainer"
QMAKE_TARGET_COMPANY="MySoft"
QMAKE_TARGET_COPYRIGHT="Copyright © $${QMAKE_TARGET_COMPANY} Ltd. 2022.  All rights reserved."
COMPANY_URL=www.typingtrainer.com

#-------------------------------------------------
# in common.pri will be defined VERSION, TARGET, DEBUG SETTINGS
#  global APP DEFINES
#-------------------------------------------------
#include( ./common.pri )
#include( ./app.pri )

#END

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11
CONFIG += c++14
CONFIG += c++17


#Define the preprocessor macro to get the application version in the application.
DEFINES += APP_DISPLAY_NAME=\"\\\"$${PRODUCT_DISPLAY_NAME}\\\"\"
DEFINES += APP_PRODUCT=\"\\\"$${QMAKE_TARGET_PRODUCT}\\\"\"
DEFINES += APP_VERSION=\"\\\"$${VERSION}.$${VER_RELEASE}\\\"\"
DEFINES += APP_COMPANY=\"\\\"$${QMAKE_TARGET_COMPANY}\\\"\"
DEFINES += APP_COMPANY_URL=\"\\\"$${COMPANY_URL}\\\"\"
DEFINES += APP_COPYRIGHT=\"\\\"$${QMAKE_TARGET_COPYRIGHT}\\\"\"
DEFINES += APP_ICON=\"\\\"$${RC_ICONS}\\\"\"

#DEBUG SETTINGS
CONFIG(release, debug|release):DEFINES += QT_NO_DEBUG_OUTPUT
#by default defined: in Debug mode QT_DEBUG, in Release mode QT_NO_DEBUG

QMAKE_CXXFLAGS_WARN_ON += -Wno-unused-parameter


SOURCES += \
    MainWindow.cpp \
    ZAbstractLineController.cpp \
    ZClickableLabel.cpp \
    ZColorButton.cpp \
    ZDataSourceManager.cpp \
    ZLineControllerCreator.cpp \
    ZNewUserWidget.cpp \
    ZRandomLineController.cpp \
    ZSettingsDialog.cpp \
    ZStatisticsWidget.cpp \
    ZSuccessivelyLineController.cpp \
    ZTask.cpp \
    ZTaskContentWidget.cpp \
    ZTaskListWidget.cpp \
    ZTaskSource.cpp \
    ZTaskWidget.cpp \
    ZTrainingManager.cpp \
    ZTrainingWidget.cpp \
    ZTranslatorManager.cpp \
    ZTypingSpeedLineController.cpp \
    ZUserSelectionDialog.cpp \
    ZWorkController.cpp \
        main.cpp


HEADERS += \
    ZAbstractLineController.h \
    ZClickableLabel.h \
    ZColorButton.h \
    ZDataSourceManager.h \
    ZLineControllerCreator.h \
    ZNewUserWidget.h \
    ZRandomLineController.h \
    ZSettingsDialog.h \
    ZSqlTableStatements.h \
    ZStatisticsWidget.h \
    ZSuccessivelyLineController.h \
    ZTask.h \
    ZTaskSource.h \
    ZTrainingManager.h \
    ZTranslatorManager.h \
    MainWindow.h \
    ZTaskContentWidget.h \
    ZTaskListWidget.h \
    ZTaskWidget.h \
    ZTrainingWidget.h \
    ZTypingSpeedLineController.h \
    ZUserSelectionDialog.h \
    ZWorkController.h

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    typing_trainer.sql

RESOURCES += \
    resources.qrc
