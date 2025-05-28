#pragma once

#include <QMainWindow>

class cDrawWidget;

template <class T>
T *CreateBlackControl(QString const &name)
{
    T *p = new T(name);
    p->setStyleSheet("color: navy;");
    return p;
}

class cMainWindow : public QMainWindow
{
    Q_OBJECT

private:
    enum LayerType : uint8_t
    {
        TRANSIT = 0,
        ISOLINES,
        OUTDOORS,
    };
    Q_ENUM(LayerType)

    enum RouteMarkType : uint8_t
    {
        Start = 0,
        Intermediate,
        Finish
    };
    Q_ENUM(RouteMarkType)

    enum SelectionMode
    {
        Features = 0,
        CityBoundaries,
        CityRoads,
        CrossMwmSegments,
        MWMBorders,

        MwmsBordersByPolyFiles,
        MwmsBordersWithVerticesByPolyFiles,

        MwmsBordersByPackedPolygon,
        MwmsBordersWithVerticesByPackedPolygon,

        BoundingBoxByPolyFiles,
        BoundingBoxByPackedPolygon,

        Cancelled,
    };
    Q_ENUM(SelectionMode)

public:
    explicit cMainWindow(QWidget *parent = nullptr);
    ~cMainWindow();

public Q_SLOTS:
    void ShowAll();
    void ChoosePositionModeDisable();
    void OnLayerEnabled(LayerType layer);
    void OnBookmarksAction();
    void OnRoutePointSelected(RouteMarkType type);
    void OnFollowRoute();
    void OnClearRoute();
    void OnRoutingSettings();
    void OnCreateFeatureClicked();
    void OnSwitchSelectionMode(SelectionMode mode);
    void OnSwitchMwmsBordersSelectionMode();
    void OnClearSelection();
    void OnSearchButtonClicked();
    void OnRulerEnabled();
    void OnMyPosition();
    void OnBuildStyle();
    void OnRecalculateGeomIndex();
    void OnDebugStyle();
    void OnGetStatistics();
    void OnRunTests();
    void OnBuildPhonePackage();
    void ShowUpdateDialog();
    void OnLoginMenuItem();
    void OnUploadEditsMenuItem();
    void OnPreferences();
    void OnAbout();
    void OnDownloadClicked();
    void OnRetryDownloadClicked();

private:
    void createDrawWidget();
    void createMenuBar();
    void createToolBar();
    void createDownloadButtons();

private:
    cDrawWidget *m_pDrawWidget;
};
