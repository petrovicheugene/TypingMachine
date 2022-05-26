//===================================================
#include "MainWindow.h"
#include <QApplication>

#include "X_TranslatorManager.h"

//===================================================

//===================================================
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // create qApp properties and set .pro defines into them
#ifdef APP_DISPLAY_NAME
    QApplication::setApplicationDisplayName(APP_DISPLAY_NAME);
#endif

#ifdef APP_PRODUCT
    QApplication::setApplicationName(APP_PRODUCT);
#endif

#ifdef APP_VERSION
    QApplication::setApplicationVersion(APP_VERSION);
#endif

#ifdef APP_COMPANY
    QApplication::setOrganizationName(APP_COMPANY);
#endif

#ifdef APP_COMPANY_URL
    QApplication::setOrganizationDomain(APP_COMPANY_URL);
#endif

#ifdef APP_COPYRIGHT
    qApp->setProperty("appCopyright", QString(APP_COPYRIGHT));
#endif

#ifdef APP_ICON
    qApp->setProperty("appIcon", QString(APP_ICON));
#endif

    X_TranslatorManager languageManager;
    languageManager.xp_installTranslatorsToApplication();

    MainWindow w;
    w.show();

    return a.exec();
}
//===================================================


