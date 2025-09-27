#pragma once

#include <FluFrameLessWidget.h>
#include <FluStackedLayout.h>
#include <FluHNavigationView.h>
#include <QVBoxLayout>
#include <FluMenu.h>
#include <FluAction.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include "ProjectDetailCard.h"
#include "FluVScrollView.h"

class StatsWindow : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    StatsWindow(QWidget* parent = nullptr);

  public slots:
    void onClickedShowReleaseBtn();
    void onThemeChanged();
    void onNetworkReply(QNetworkReply* reply);

protected:
  QString APIRoot;
  ProjectDetailCard* m_projectDetailCard;
  QNetworkAccessManager* m_networkManager;
  // QVBoxLayout* m_vContentLayout;

  FluVScrollView* m_scrollView;
};
