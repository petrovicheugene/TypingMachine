#-------------------------------------------------
#
# Project created by QtCreator 2019-04-16T17:06:36
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = TypingMachine

#PRO VARS
RC_ICONS = ""

#Application version
VER_MAJ=0
VER_MIN=0
VER_PAT=0
VER_BUILD=b

PRODUCT_DISPLAY_NAME="Typing Machine"
PRODUCT_FILE_BASE_NAME="typingmachine"
QMAKE_TARGET_PRODUCT="TypingMachine"
QMAKE_TARGET_DESCRIPTION="Typing machine"
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

CONFIG(debug, debug|release) {
    TARGET=$${PRODUCT_FILE_BASE_NAME}-$${VERSION}.$${BUILD_FLAG}
#    DESTDIR=$${PWD}\..\bin\
} else {
    TARGET=$${PRODUCT_FILE_BASE_NAME}
    DESTDIR=$${PWD}\..\bin\
}


SOURCES += \
    MainWindow.cpp \
    X_AbstractLineController.cpp \
    X_AbstractStatisticsSource.cpp \
    X_AbstractTaskSource.cpp \
    X_ClickableLabel.cpp \
    X_ColorButton.cpp \
    X_DataSourceManager.cpp \
    X_LineControllerCreator.cpp \
    X_NewUserWidget.cpp \
    X_RandomLineController.cpp \
    X_SessionStatisticsManager.cpp \
    X_SettingsDialog.cpp \
    X_StatisticsWidget.cpp \
    X_SuccessivelyLineController.cpp \
    X_Task.cpp \
    X_TaskContentWidget.cpp \
    X_TaskListWidget.cpp \
    X_TaskWidget.cpp \
    X_TrainingManager.cpp \
    X_TrainingWidget.cpp \
    X_TranslatorManager.cpp \
    X_TypingSpeedLineController.cpp \
    X_UserSelectionDialog.cpp \
    X_WorkController.cpp \
        main.cpp \


HEADERS += \
    X_AbstractLineController.h \
    X_AbstractStatisticsSource.h \
    X_AbstractTaskSource.h \
    X_ClickableLabel.h \
    X_ColorButton.h \
    X_DataSourceManager.h \
    X_LineControllerCreator.h \
    X_NewUserWidget.h \
    X_RandomLineController.h \
    X_SessionStatisticsManager.h \
    X_SettingsDialog.h \
    X_SqlTableStatements.h \
    X_StatisticsWidget.h \
    X_SuccessivelyLineController.h \
    X_Task.h \
    X_TaskContentWidget.h \
    X_TaskListWidget.h \
    X_TaskWidget.h \
    X_TrainingManager.h \
    X_TrainingWidget.h \
    X_TranslatorManager.h \
    X_TypingSpeedLineController.h \
    X_UserSelectionDialog.h \
    X_WordStatistics.h \
    X_WorkController.h \
    MainWindow.h \

# Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    typing_machine.sql

RESOURCES += \
    resources.qrc

CONFIG(release, debug|release) {
    QMAKE_POST_LINK="C:\Qt\6.4.0\mingw_64\bin\windeployqt.exe "$${DESTDIR} $${DESTDIR}
}
