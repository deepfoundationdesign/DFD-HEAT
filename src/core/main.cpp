#include <QApplication>
#include <QSurfaceFormat>
#include "ui/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Set application metadata
    QCoreApplication::setOrganizationName("DFD-Engineering");
    QCoreApplication::setOrganizationDomain("dfd-heat.com");
    QCoreApplication::setApplicationName("DFD-HEAT");
    QCoreApplication::setApplicationVersion("0.1.0");

    // Set OpenGL format for Qt3D
    QSurfaceFormat format;
    format.setVersion(4, 3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setSamples(4);
    QSurfaceFormat::setDefaultFormat(format);

    MainWindow window;
    window.show();

    return app.exec();
}