#pragma once

#include "cMapWidget.h"

class cDrawWidget : public cMapWidget
{
    Q_OBJECT

public:
    explicit cDrawWidget(QWidget *parent = nullptr);
    ~cDrawWidget() override;
};
