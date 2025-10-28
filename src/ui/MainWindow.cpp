#include "ui/MainWindow.h"
#include "viewport/Viewport3D.h"
#include "auth/AuthManager.h"
#include "ui/PropertiesPanel.h"
#include "ui/SceneHierarchyPanel.h"
#include "scene/SelectionManager.h"
#include "scene/SceneObject.h"
#include "scene/ObjectManager.h"

#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QDockWidget>
#include <QTreeWidget>
#include <QTableWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_authManager(std::make_unique<AuthManager>(this))
{
    setWindowTitle("DFD-HEAT - 3D FEM Thermal Analysis");
    resize(1400, 900);

    // Create 3D viewport as central widget
    m_viewport3D = new Viewport3D(this);
    setCentralWidget(m_viewport3D);

    // Setup UI
    createActions();
    createMenus();
    createToolBars();
    createDockWindows();
    createStatusBar();

    // Setup authentication
    connect(m_authManager.get(), &AuthManager::authenticationChanged,
            this, &MainWindow::onAuthStatusChanged);

    // Configure auth (these would come from config file)
    m_authManager->setKeycloakConfig("dfd-heat", "desktop-client", "https://auth.dfd-heat.com");
    m_authManager->setStripeConfig("pk_live_xxxxx");
}

MainWindow::~MainWindow() = default;

void MainWindow::createActions()
{
    // File actions
    m_newAction = new QAction(QIcon(":/icons/new.png"), tr("&New Project"), this);
    m_newAction->setShortcuts(QKeySequence::New);
    m_newAction->setStatusTip(tr("Create a new project"));
    connect(m_newAction, &QAction::triggered, this, &MainWindow::newProject);

    m_openAction = new QAction(QIcon(":/icons/open.png"), tr("&Open Project..."), this);
    m_openAction->setShortcuts(QKeySequence::Open);
    m_openAction->setStatusTip(tr("Open an existing project"));
    connect(m_openAction, &QAction::triggered, this, &MainWindow::openProject);

    m_saveAction = new QAction(QIcon(":/icons/save.png"), tr("&Save Project"), this);
    m_saveAction->setShortcuts(QKeySequence::Save);
    m_saveAction->setStatusTip(tr("Save the current project"));
    connect(m_saveAction, &QAction::triggered, this, &MainWindow::saveProject);

    m_saveAsAction = new QAction(tr("Save &As..."), this);
    m_saveAsAction->setShortcuts(QKeySequence::SaveAs);
    m_saveAsAction->setStatusTip(tr("Save the project with a new name"));
    connect(m_saveAsAction, &QAction::triggered, this, &MainWindow::saveProjectAs);

    m_exitAction = new QAction(tr("E&xit"), this);
    m_exitAction->setShortcuts(QKeySequence::Quit);
    m_exitAction->setStatusTip(tr("Exit the application"));
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);

    // Help actions
    m_aboutAction = new QAction(tr("&About"), this);
    m_aboutAction->setStatusTip(tr("Show information about DFD-HEAT"));
    connect(m_aboutAction, &QAction::triggered, this, &MainWindow::showAbout);

    m_authAction = new QAction(tr("&Account"), this);
    m_authAction->setStatusTip(tr("Manage your account and subscription"));
    connect(m_authAction, &QAction::triggered, this, &MainWindow::showAuthDialog);
}

void MainWindow::createMenus()
{
    // File menu
    m_fileMenu = menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_newAction);
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addAction(m_saveAction);
    m_fileMenu->addAction(m_saveAsAction);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    // Edit menu
    m_editMenu = menuBar()->addMenu(tr("&Edit"));
    m_editMenu->addAction(tr("&Undo"));
    m_editMenu->addAction(tr("&Redo"));
    m_editMenu->addSeparator();
    m_editMenu->addAction(tr("&Copy"));
    m_editMenu->addAction(tr("&Paste"));
    m_editMenu->addAction(tr("&Delete"));

    // View menu
    m_viewMenu = menuBar()->addMenu(tr("&View"));
    m_viewMenu->addAction(tr("&Zoom In"));
    m_viewMenu->addAction(tr("&Zoom Out"));
    m_viewMenu->addAction(tr("&Fit All"));
    m_viewMenu->addSeparator();
    m_viewMenu->addAction(tr("&Wireframe"));
    m_viewMenu->addAction(tr("&Shaded"));
    m_viewMenu->addAction(tr("&Rendered"));

    // Model menu
    m_modelMenu = menuBar()->addMenu(tr("&Model"));
    m_modelMenu->addAction(tr("Add &Wall"));
    m_modelMenu->addAction(tr("Add &Floor"));
    m_modelMenu->addAction(tr("Add &Roof"));
    m_modelMenu->addAction(tr("Add &Window"));
    m_modelMenu->addAction(tr("Add &Door"));

    // Mesh menu
    m_meshMenu = menuBar()->addMenu(tr("&Mesh"));
    m_meshMenu->addAction(tr("&Generate Mesh"));
    m_meshMenu->addAction(tr("&Refine Mesh"));
    m_meshMenu->addAction(tr("&Mesh Settings..."));

    // Solve menu
    m_solveMenu = menuBar()->addMenu(tr("&Solve"));
    m_solveMenu->addAction(tr("&Steady State"));
    m_solveMenu->addAction(tr("&Transient"));
    m_solveMenu->addSeparator();
    m_solveMenu->addAction(tr("&Solver Settings..."));

    // Results menu
    m_resultsMenu = menuBar()->addMenu(tr("&Results"));
    m_resultsMenu->addAction(tr("&Temperature Field"));
    m_resultsMenu->addAction(tr("&Heat Flux"));
    m_resultsMenu->addAction(tr("&Export Results..."));

    // Help menu
    m_helpMenu = menuBar()->addMenu(tr("&Help"));
    m_helpMenu->addAction(m_authAction);
    m_helpMenu->addSeparator();
    m_helpMenu->addAction(m_aboutAction);
}

void MainWindow::createToolBars()
{
    m_fileToolBar = addToolBar(tr("File"));
    m_fileToolBar->addAction(m_newAction);
    m_fileToolBar->addAction(m_openAction);
    m_fileToolBar->addAction(m_saveAction);

    m_modelToolBar = addToolBar(tr("Model"));
    m_modelToolBar->addAction(tr("Select"));
    m_modelToolBar->addAction(tr("Move"));
    m_modelToolBar->addAction(tr("Rotate"));
    m_modelToolBar->addAction(tr("Scale"));
    m_modelToolBar->addSeparator();
    m_modelToolBar->addAction(tr("Wall"));
    m_modelToolBar->addAction(tr("Box"));

    m_viewToolBar = addToolBar(tr("View"));
    m_viewToolBar->addAction(tr("Orbit"));
    m_viewToolBar->addAction(tr("Pan"));
    m_viewToolBar->addAction(tr("Zoom"));
    m_viewToolBar->addAction(tr("Fit"));

    m_solveToolBar = addToolBar(tr("Solve"));
    m_solveToolBar->addAction(tr("Mesh"));
    m_solveToolBar->addAction(tr("Solve"));
    m_solveToolBar->addAction(tr("Results"));
}

void MainWindow::createDockWindows()
{
    // Project tree dock
    m_projectDock = new QDockWidget(tr("Project"), this);
    m_projectTree = new QTreeWidget();
    m_projectTree->setHeaderLabel(tr("Project Structure"));
    m_projectDock->setWidget(m_projectTree);
    addDockWidget(Qt::LeftDockWidgetArea, m_projectDock);

    // Properties dock
    m_propertiesDock = new QDockWidget(tr("Properties"), this);
    m_propertiesPanel = new PropertiesPanel();
    m_propertiesDock->setWidget(m_propertiesPanel);
    addDockWidget(Qt::RightDockWidgetArea, m_propertiesDock);

    // Connect selection changes to properties panel
    connect(m_viewport3D->selectionManager(), &SelectionManager::selectionChanged,
            this, [this]() {
        SceneObject* selected = m_viewport3D->selectionManager()->activeObject();
        if (selected) {
            m_propertiesPanel->setObject(selected);
        } else {
            m_propertiesPanel->clearObject();
        }
    });

    // Materials dock
    m_materialsDock = new QDockWidget(tr("Materials"), this);
    m_materialsTree = new QTreeWidget();
    m_materialsTree->setHeaderLabel(tr("Material Library"));

    // Add some sample materials
    auto concrete = new QTreeWidgetItem(m_materialsTree, QStringList() << "Concrete (λ=1.7 W/mK)");
    auto brick = new QTreeWidgetItem(m_materialsTree, QStringList() << "Brick (λ=0.8 W/mK)");
    auto insulation = new QTreeWidgetItem(m_materialsTree, QStringList() << "Insulation (λ=0.04 W/mK)");

    m_materialsDock->setWidget(m_materialsTree);
    addDockWidget(Qt::RightDockWidgetArea, m_materialsDock);

    // Scene Hierarchy dock (replaces Boundary Conditions)
    m_sceneHierarchyDock = new QDockWidget(tr("Scene Hierarchy"), this);
    m_sceneHierarchyPanel = new SceneHierarchyPanel(
        m_viewport3D->objectManager(),
        m_viewport3D->selectionManager(),
        this
    );
    m_sceneHierarchyDock->setWidget(m_sceneHierarchyPanel);
    addDockWidget(Qt::LeftDockWidgetArea, m_sceneHierarchyDock);

    // Console dock
    m_consoleDock = new QDockWidget(tr("Console"), this);
    m_consoleOutput = new QTextEdit();
    m_consoleOutput->setReadOnly(true);
    m_consoleDock->setWidget(m_consoleOutput);
    addDockWidget(Qt::BottomDockWidgetArea, m_consoleDock);

    // Tabify some docks
    tabifyDockWidget(m_projectDock, m_sceneHierarchyDock);
    tabifyDockWidget(m_propertiesDock, m_materialsDock);
}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage(tr("Ready"));

    // Add permanent widgets
    auto authLabel = new QLabel(tr("Free Version"));
    statusBar()->addPermanentWidget(authLabel);

    auto coordLabel = new QLabel(tr("X: 0.00 Y: 0.00 Z: 0.00"));
    statusBar()->addPermanentWidget(coordLabel);
}

void MainWindow::newProject()
{
    m_consoleOutput->append("Creating new project...");
    m_currentProjectPath.clear();
    statusBar()->showMessage(tr("New project created"), 2000);
}

void MainWindow::openProject()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open Project"), "", tr("DFD-HEAT Project (*.dfdheat)"));

    if (!fileName.isEmpty()) {
        m_currentProjectPath = fileName;
        m_consoleOutput->append(QString("Opening project: %1").arg(fileName));
        statusBar()->showMessage(tr("Project opened"), 2000);
    }
}

void MainWindow::saveProject()
{
    if (m_currentProjectPath.isEmpty()) {
        saveProjectAs();
    } else {
        m_consoleOutput->append(QString("Saving project: %1").arg(m_currentProjectPath));
        statusBar()->showMessage(tr("Project saved"), 2000);
    }
}

void MainWindow::saveProjectAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Project"), "", tr("DFD-HEAT Project (*.dfdheat)"));

    if (!fileName.isEmpty()) {
        m_currentProjectPath = fileName;
        saveProject();
    }
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, tr("About DFD-HEAT"),
        tr("<h2>DFD-HEAT v0.1.0</h2>"
           "<p>3D Finite Element Method Thermal Analysis Software</p>"
           "<p>Professional tool for building thermal simulation and energy analysis.</p>"
           "<p>Copyright 2024 DFD-Engineering</p>"));
}

void MainWindow::showAuthDialog()
{
    if (!m_authManager->isAuthenticated()) {
        m_authManager->authenticate();
    } else {
        QMessageBox::information(this, tr("Account"),
            tr("Email: %1\nLicense: Professional").arg(m_authManager->userEmail()));
    }
}

void MainWindow::onAuthStatusChanged(bool authenticated)
{
    if (authenticated) {
        m_consoleOutput->append("Authentication successful");
        statusBar()->showMessage(tr("Logged in"), 2000);
    } else {
        m_consoleOutput->append("Logged out");
        statusBar()->showMessage(tr("Logged out"), 2000);
    }
}