#pragma once

#include <FluWidget.h>
#include <FluFrameLessWidget.h>
#include <FluStackedLayout.h>
#include <FluHNavigationView.h>
#include <QVBoxLayout>
#include <FluMenu.h>
#include <FluAction.h>

class StatsWindow : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    StatsWindow(QWidget* parent = nullptr);

    void contextMenuEvent(QContextMenuEvent* event);

  public slots:
    void onThemeChanged();

  protected:
    FluMenu* m_contextMenu;
};
