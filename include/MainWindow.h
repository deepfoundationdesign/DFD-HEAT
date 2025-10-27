#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>

QT_BEGIN_NAMESPACE
class QAction;
class QMenu;
class QToolBar;
class QDockWidget;
class QTreeWidget;
class QTableWidget;
class QTextEdit;
QT_END_NAMESPACE

class Viewport3D;
class AuthManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void newProject();
    void openProject();
    void saveProject();
    void saveProjectAs();
    void showAbout();
    void showAuthDialog();
    void onAuthStatusChanged(bool authenticated);

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createDockWindows();
    void createStatusBar();

    // Central widget
    Viewport3D *m_viewport3D;

    // Dock widgets
    QDockWidget *m_projectDock;
    QDockWidget *m_propertiesDock;
    QDockWidget *m_materialsDock;
    QDockWidget *m_boundaryDock;
    QDockWidget *m_consoleDock;

    // Dock contents
    QTreeWidget *m_projectTree;
    QTableWidget *m_propertiesTable;
    QTreeWidget *m_materialsTree;
    QTableWidget *m_boundaryTable;
    QTextEdit *m_consoleOutput;

    // Menus
    QMenu *m_fileMenu;
    QMenu *m_editMenu;
    QMenu *m_viewMenu;
    QMenu *m_modelMenu;
    QMenu *m_meshMenu;
    QMenu *m_solveMenu;
    QMenu *m_resultsMenu;
    QMenu *m_helpMenu;

    // Toolbars
    QToolBar *m_fileToolBar;
    QToolBar *m_modelToolBar;
    QToolBar *m_viewToolBar;
    QToolBar *m_solveToolBar;

    // Actions
    QAction *m_newAction;
    QAction *m_openAction;
    QAction *m_saveAction;
    QAction *m_saveAsAction;
    QAction *m_exitAction;
    QAction *m_aboutAction;
    QAction *m_authAction;

    // Auth
    std::unique_ptr<AuthManager> m_authManager;

    QString m_currentProjectPath;
};

#endif // MAINWINDOW_H