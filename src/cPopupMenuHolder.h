#pragma once

#include <QObject>
#include <QAction>
#include <vector>

class QToolButton;

class cPopupMenuHolder : public QObject
{
    Q_OBJECT

public:
    explicit cPopupMenuHolder(QObject *parent = nullptr);
    ~cPopupMenuHolder();
    QToolButton *create();
    void setChecked(size_t idx, bool checked);
    QIcon getIcon(size_t idx);

    template <class SlotType>
    QAction *addAction(QIcon const &icon, QString const &text,
                       SlotType slot, bool checkable)
    {
        QAction *action = addActionImpl(icon, text, checkable);
        connect(action, &QAction::triggered, std::move(slot));
        return action;
    }

    QAction *addAction(QIcon const &icon, QString const &text,
                       QObject const *receiver, char const *member, bool checkable)
    {
        QAction *p = addActionImpl(icon, text, checkable);
        connect(p, SIGNAL(triggered()), receiver, member);
        return p;
    }

private:
    QAction *addActionImpl(QIcon const &icon, QString const &text, bool checkable);

private:
    std::vector<QAction *> m_actions;
};
