#include "cMainWindow.h"
#include "cPopupMenuHolder.h"
#include "cDrawWidget.h"
#include <QToolBar>
#include <QToolButton>
#include <QMenu>
#include <QMenuBar>
#include <functional>
#include <windows.h>

struct Hotkey
{
    Hotkey() = default;
    Hotkey(QKeySequence const &key, char const *slot) : m_key(key), m_slot(slot) {}

    QKeySequence m_key = 0;
    char const *m_slot = nullptr;
};

cMainWindow::cMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("ReadyGPS | Système de navigation par GPS");
    setWindowIcon(QIcon(":/ui/logo.png"));
    resize(400, 300);
    createToolBar();
    m_pDrawWidget = new cDrawWidget(this);
    setCentralWidget(m_pDrawWidget);

#ifndef OMIM_OS_WINDOWS
    QMenu *helpMenu = new QMenu(tr("Help"), this);
    menuBar()->addMenu(helpMenu);
    helpMenu->addAction(tr("OpenStreetMap Login"), QKeySequence(Qt::CTRL | Qt::Key_O), this, SLOT(OnLoginMenuItem()));
    helpMenu->addAction(tr("Upload Edits"), QKeySequence(Qt::CTRL | Qt::Key_U), this, SLOT(OnUploadEditsMenuItem()));
    helpMenu->addAction(tr("Preferences"), QKeySequence(Qt::CTRL | Qt::Key_P), this, SLOT(OnPreferences()));
    helpMenu->addAction(tr("About"), QKeySequence(Qt::Key_F1), this, SLOT(OnAbout()));
    helpMenu->addAction(tr("Exit"), QKeySequence(Qt::CTRL | Qt::Key_Q), this, SLOT(close()));
#endif
}

cMainWindow::~cMainWindow()
{
}

void cMainWindow::createToolBar()
{
    QToolBar *pToolBar = new QToolBar(tr("Navigation Bar"), this);
    pToolBar->setOrientation(Qt::Vertical);
    pToolBar->setIconSize(QSize(32, 32));

    Hotkey const hotkeys[] = {{Qt::Key_A, SLOT(ShowAll())},
                              {Qt::Key_Escape, SLOT(ChoosePositionModeDisable())}};

    for (auto const &hotkey : hotkeys)
    {
        QAction *pAct = new QAction(this);
        pAct->setShortcut(QKeySequence(hotkey.m_key));
        connect(pAct, SIGNAL(triggered()), this, hotkey.m_slot);
        addAction(pAct);
    }

    cPopupMenuHolder *layers = new cPopupMenuHolder(this);
    layers->addAction(QIcon(":/navig64/subway.png"), tr("Public transport"),
                      std::bind(&cMainWindow::OnLayerEnabled, this, LayerType::TRANSIT), true);
    layers->setChecked(LayerType::TRANSIT, true);

    layers->addAction(QIcon(":/navig64/isolines.png"), tr("Isolines"),
                      std::bind(&cMainWindow::OnLayerEnabled, this, LayerType::ISOLINES), true);
    layers->setChecked(LayerType::ISOLINES, false);

    layers->addAction(QIcon(":/navig64/isolines.png"), tr("Outdoors"),
                      std::bind(&cMainWindow::OnLayerEnabled, this, LayerType::OUTDOORS), true);
    layers->setChecked(LayerType::OUTDOORS, false);

    QToolButton *layerBtn = layers->create();
    layerBtn->setIcon(QIcon(":/navig64/layers.png"));
    pToolBar->addWidget(layerBtn);
    pToolBar->addSeparator();

    pToolBar->addAction(QIcon(":/navig64/bookmark.png"),
                        tr("Show bookmarks and tracks; use ALT + RMB to add a bookmark"), this,
                        SLOT(OnBookmarksAction()));
    pToolBar->addSeparator();

#ifndef BUILD_DESIGNER
    cPopupMenuHolder *routing = new cPopupMenuHolder(this);

    routing->addAction(QIcon(":/navig64/point-start.png"), tr("Start point"),
                       std::bind(&cMainWindow::OnRoutePointSelected, this, RouteMarkType::Start), false);
    routing->addAction(QIcon(":/navig64/point-intermediate.png"), tr("Intermediate point"),
                       std::bind(&cMainWindow::OnRoutePointSelected, this, RouteMarkType::Intermediate), false);
    routing->addAction(QIcon(":/navig64/point-finish.png"), tr("Finish point"),
                       std::bind(&cMainWindow::OnRoutePointSelected, this, RouteMarkType::Finish), false);

    QToolButton *routingBtn = routing->create();
    routingBtn->setToolTip(tr("Select mode and use SHIFT + LMB to set point"));
    pToolBar->addWidget(routingBtn);
    routingBtn->setIcon(routing->getIcon(RouteMarkType::Start));

    QAction *followRoutBtn = pToolBar->addAction(QIcon(":/navig64/routing.png"), tr("Follow route"), this,
                                                 SLOT(OnFollowRoute()));
    followRoutBtn->setToolTip(tr("Build route and use ALT + LMB to emulate current position"));

    pToolBar->addAction(QIcon(":/navig64/clear-route.png"), tr("Clear route"), this,
                        SLOT(OnClearRoute()));
    pToolBar->addAction(QIcon(":/navig64/settings-routing.png"), tr("Routing settings"), this,
                        SLOT(OnRoutingSettings()));

    pToolBar->addSeparator();

    QAction *selectBtn = pToolBar->addAction(QIcon(":/navig64/select.png"), tr("Create Feature"), this,
                                             SLOT(OnCreateFeatureClicked()));
    selectBtn->setCheckable(true);
    selectBtn->setToolTip(tr("Push to select position, next push to create Feature"));
    selectBtn->setShortcut(QKeySequence::New);

    cPopupMenuHolder *selectionMode = new cPopupMenuHolder(this);

    selectionMode->addAction(QIcon(":/navig64/selectmode.png"), tr("Roads selection mode"),
                             std::bind(&cMainWindow::OnSwitchSelectionMode, this, SelectionMode::Features), true);
    selectionMode->addAction(QIcon(":/navig64/city-boundaries.png"), tr("City boundaries selection mode"),
                             std::bind(&cMainWindow::OnSwitchSelectionMode, this, SelectionMode::CityBoundaries), true);
    selectionMode->addAction(QIcon(":/navig64/city-roads.png"), tr("City roads selection mode"),
                             std::bind(&cMainWindow::OnSwitchSelectionMode, this, SelectionMode::CityRoads), true);
    selectionMode->addAction(QIcon(":/navig64/test.png"), tr("Cross MWM segments selection mode"),
                             std::bind(&cMainWindow::OnSwitchSelectionMode, this, SelectionMode::CrossMwmSegments), true);
    selectionMode->addAction(QIcon(":/navig64/borders-selection.png"), tr("MWMs borders selection mode"), this,
                             SLOT(OnSwitchMwmsBordersSelectionMode()), true);

    QToolButton *selectionModeBtn = selectionMode->create();
    selectionModeBtn->setToolTip(tr("Select mode and use RMB to define selection box"));
    selectionModeBtn->setIcon(selectionMode->getIcon(SelectionMode::Features));
    pToolBar->addWidget(selectionModeBtn);

    pToolBar->addAction(QIcon(":/navig64/clear.png"), tr("Clear selection"), this,
                        SLOT(OnClearSelection()));

    pToolBar->addSeparator();

    pToolBar->addSeparator();
#endif

    QAction *searchAction = pToolBar->addAction(QIcon(":/navig64/search.png"), tr("Offline Search"), this,
                                                SLOT(OnSearchButtonClicked()));
    searchAction->setCheckable(true);
    searchAction->setShortcut(QKeySequence::Find);

    QAction *rulerAction = pToolBar->addAction(QIcon(":/navig64/ruler.png"), tr("Ruler"), this,
                                               SLOT(OnRulerEnabled()));
    rulerAction->setToolTip(tr("Check this button and use ALT + LMB to set points"));
    rulerAction->setCheckable(true);
    rulerAction->setChecked(false);

    pToolBar->addSeparator();

    QAction *location = pToolBar->addAction(QIcon(":/navig64/location.png"), tr("My Position"), this,
                                            SLOT(OnMyPosition()));
    location->setCheckable(true);

#ifdef BUILD_DESIGNER
    bool isMapcssFilePath = true;
    if (isMapcssFilePath)
    {
        QAction *buildStyleAction = pToolBar->addAction(QIcon(":/navig64/run.png"), tr("Build style"), this,
                                                        SLOT(OnBuildStyle()));
        buildStyleAction->setCheckable(false);
        buildStyleAction->setToolTip(tr("Build style"));

        QAction *recalculateGeomIndex = pToolBar->addAction(QIcon(":/navig64/geom.png"), tr("Recalculate geometry index"), this,
                                                            SLOT(OnRecalculateGeomIndex()));
        recalculateGeomIndex->setCheckable(false);
        recalculateGeomIndex->setToolTip(tr("Recalculate geometry index"));
    }

    QAction *drawDebugRectAction = pToolBar->addAction(QIcon(":/navig64/bug.png"), tr("Debug style"), this,
                                                       SLOT(OnDebugStyle()));
    drawDebugRectAction->setCheckable(true);
    drawDebugRectAction->setChecked(false);
    drawDebugRectAction->setToolTip(tr("Debug style"));

    QAction *getStatisticsAction = pToolBar->addAction(QIcon(":/navig64/chart.png"), tr("Get statistics"), this,
                                                       SLOT(OnGetStatistics()));
    getStatisticsAction->setCheckable(false);
    getStatisticsAction->setToolTip(tr("Get statistics"));

    QAction *runTestsAction = pToolBar->addAction(QIcon(":/navig64/test.png"), tr("Run tests"), this,
                                                  SLOT(OnRunTests()));
    runTestsAction->setCheckable(false);
    runTestsAction->setToolTip(tr("Run tests"));

    QAction *buildPhonePackAction = pToolBar->addAction(QIcon(":/navig64/phonepack.png"), tr("Build phone package"), this,
                                                        SLOT(OnBuildPhonePackage()));
    buildPhonePackAction->setCheckable(false);
    buildPhonePackAction->setToolTip(tr("Build phone package"));
#endif

#ifndef NO_DOWNLOADER
    pToolBar->addSeparator();
    pToolBar->addAction(QIcon(":/navig64/download.png"), tr("Download Maps"), this,
                        SLOT(ShowUpdateDialog()));
#endif

    bool isScreenshotMode = false;

    if (isScreenshotMode)
        pToolBar->setVisible(false);

    addToolBar(Qt::RightToolBarArea, pToolBar);
}

void cMainWindow::ShowAll()
{
    qDebug() << "ShowAll triggered";
}

void cMainWindow::ChoosePositionModeDisable()
{
    qDebug() << "ChoosePositionModeDisable triggered";
}

void cMainWindow::OnLayerEnabled(LayerType layer)
{
    qDebug() << "Layer enabled:" << layer;
}

void cMainWindow::OnBookmarksAction()
{
    qDebug() << "Bookmarks action triggered";
}

void cMainWindow::OnRoutePointSelected(RouteMarkType type)
{
    qDebug() << "Route point selected:" << type;
}

void cMainWindow::OnFollowRoute()
{
    qDebug() << "Follow route triggered";
}
void cMainWindow::OnClearRoute()
{
    qDebug() << "Clear route triggered";
}

void cMainWindow::OnRoutingSettings()
{
    qDebug() << "Routing settings triggered";
}

void cMainWindow::OnCreateFeatureClicked()
{
    qDebug() << "Create Feature clicked";
}

void cMainWindow::OnSwitchSelectionMode(SelectionMode mode)
{
    qDebug() << "Switch selection mode to:" << mode;
}

void cMainWindow::OnSwitchMwmsBordersSelectionMode()
{
    qDebug() << "Switch to MWMs borders selection mode";
}

void cMainWindow::OnClearSelection()
{
    qDebug() << "Clear selection triggered";
}

void cMainWindow::OnSearchButtonClicked()
{
    qDebug() << "Search button clicked";
}

void cMainWindow::OnRulerEnabled()
{
    qDebug() << "Ruler enabled";
}

void cMainWindow::OnMyPosition()
{
    qDebug() << "My position triggered";
}

void cMainWindow::OnBuildStyle()
{
    qDebug() << "Build style triggered";
}

void cMainWindow::OnRecalculateGeomIndex()
{
    qDebug() << "Recalculate geometry index triggered";
}

void cMainWindow::OnDebugStyle()
{
    qDebug() << "Debug style triggered";
}

void cMainWindow::OnGetStatistics()
{
    qDebug() << "Get statistics triggered";
}

void cMainWindow::OnRunTests()
{
    qDebug() << "Run tests triggered";
}

void cMainWindow::OnBuildPhonePackage()
{
    qDebug() << "Build phone package triggered";
}

void cMainWindow::ShowUpdateDialog()
{
    qDebug() << "Show update dialog triggered";
}

void cMainWindow::OnLoginMenuItem()
{
    qDebug() << "Login menu item triggered";
}

void cMainWindow::OnUploadEditsMenuItem()
{
    qDebug() << "Upload edits menu item triggered";
}

void cMainWindow::OnPreferences()
{
    qDebug() << "Preferences triggered";
}

void cMainWindow::OnAbout()
{
    qDebug() << "About triggered";
}
