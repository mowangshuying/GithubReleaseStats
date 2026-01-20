#pragma once

#include "FluVScrollView.h"
#include "ProjectDetailCard.h"
#include <FluAction.h>
#include <FluFrameLessWidget.h>
#include <FluHNavigationView.h>
#include <FluMenu.h>
#include <FluStackedLayout.h>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QVBoxLayout>

class StatsWindow : public FluFrameLessWidget
{
    Q_OBJECT
  public:
    StatsWindow(QWidget *parent = nullptr);

  public slots:
    void onClickedShowReleaseBtn();
    void onThemeChanged();
    void onNetworkReply(QNetworkReply *reply);

  protected:
    QString APIRoot;
    ProjectDetailCard *m_projectDetailCard;
    QNetworkAccessManager *m_networkManager;
    // QVBoxLayout* m_vContentLayout;

    FluVScrollView *m_scrollView;
};
