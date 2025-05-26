#pragma once

#include <QOpenGLWidget>

class cMapWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    explicit cMapWidget(QWidget *parent = nullptr);
    ~cMapWidget() override;
};
