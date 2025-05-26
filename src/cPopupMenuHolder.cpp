#include "cPopupMenuHolder.h"
#include <QMenu>
#include <QToolButton>

struct Hotkey
{
    Hotkey() = default;
    Hotkey(QKeySequence const &key, char const *slot) : m_key(key), m_slot(slot) {}

    QKeySequence m_key = 0;
    char const *m_slot = nullptr;
};

cPopupMenuHolder::cPopupMenuHolder(QObject *parent)
    : QObject(parent)
{
}

cPopupMenuHolder::~cPopupMenuHolder()
{
}

QAction *cPopupMenuHolder::addActionImpl(QIcon const &icon, QString const &text, bool checkable)
{
    QAction *action = new QAction(icon, text, this);
    action->setCheckable(checkable);
    m_actions.push_back(action);
    return action;
}

QToolButton *cPopupMenuHolder::create()
{
    QMenu *menu = new QMenu();
    for (auto *action : m_actions)
    {
        menu->addAction(action);
    }

    QToolButton *toolButton = new QToolButton;
    toolButton->setPopupMode(QToolButton::MenuButtonPopup);
    toolButton->setMenu(menu);
    return toolButton;
}

void cPopupMenuHolder::setChecked(size_t idx, bool checked)
{
    m_actions[idx]->setChecked(checked);
}

QIcon cPopupMenuHolder::getIcon(size_t idx)
{
    return m_actions[idx]->icon();
}
