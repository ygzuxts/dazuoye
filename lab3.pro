QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    doctoreditview.cpp \
    doctorview.cpp \
    editpassword.cpp \
    idatabase.cpp \
    loginview.cpp \
    main.cpp \
    masterview.cpp \
    medicineeditview.cpp \
    medicineview.cpp \
    patienteditview.cpp \
    patientview.cpp \
    record.cpp \
    recordeditview.cpp \
    welcomeview.cpp

HEADERS += \
    doctoreditview.h \
    doctorview.h \
    editpassword.h \
    idatabase.h \
    loginview.h \
    masterview.h \
    medicineeditview.h \
    medicineview.h \
    patienteditview.h \
    patientview.h \
    record.h \
    recordeditview.h \
    welcomeview.h

FORMS += \
    doctoreditview.ui \
    doctorview.ui \
    editpassword.ui \
    loginview.ui \
    masterview.ui \
    medicineeditview.ui \
    medicineview.ui \
    patienteditview.ui \
    patientview.ui \
    record.ui \
    recordeditview.ui \
    welcomeview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    lab3.qrc
