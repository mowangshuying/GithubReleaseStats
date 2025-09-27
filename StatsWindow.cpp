#include "StatsWindow.h"

#include <FramelessHelper/Core/framelessmanager.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FramelessHelper/Widgets/standardsystembutton.h>
#include <FramelessHelper/Widgets/standardtitlebar.h>
#include <FluUtils.h>
#include <FluHNavigationIconTextItem.h>
#include <FluHNavigationSearchItem.h>
#include <FluHNavigationSettingsItem.h>
#include <QContextMenuEvent>
#include <FluThemeButton.h>
#include <FramelessHelper/Widgets/framelesswidgetshelper.h>
#include <FluLogUtils.h>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QMessageBox>
#include "Info.h"
#include "InfoCard.h"
// #include "ProjectDetailCard.h"

FRAMELESSHELPER_USE_NAMESPACE
StatsWindow::StatsWindow(QWidget* parent /*= nullptr*/) : FluFrameLessWidget(parent)
{
    APIRoot = "https://api.github.com/";
    m_networkManager = new QNetworkAccessManager(this);

    setWindowTitle("Github Release Stats Dev");
#ifndef _DEBUG
    setWindowTitle("Github Release Stats");
#endif

    setWindowIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Library, FluThemeUtils::getUtils()->getTheme()));
// #ifdef USE_QRC
    // setWindowIcon(QIcon(":/res/Tiles/GalleryIcon.ico"));
// #endif


#if !defined USE_WINDOWKIT_WIDGET
    m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
    m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
    m_titleBar->setFixedHeight(36);

#ifndef Q_OS_MACOS
    auto hLayout = (QHBoxLayout *)m_titleBar->layout();
    auto vLayout = (QVBoxLayout *)hLayout->itemAt(1)->layout();
    auto hButtonLayout = (QHBoxLayout *)vLayout->itemAt(0)->layout();
    auto themeButton = new FluThemeButton;
    hButtonLayout->insertWidget(0, themeButton);
    FramelessWidgetsHelper::get(this)->setHitTestVisible(themeButton);

    //connect(themeButton, &FluThemeButton::clickedThemeButton, this, [=]() {
        // auto settingsPages = (FluSettingPage *)m_sLayout->getWidget("SettingPage");
        // settingsPages->updateThemeSelectBox();
    //});
#endif

#endif

    m_titleBar->setObjectName("titleBar");

    // m_vContentLayout = new QVBoxLayout;
    // m_vContentLayout->setAlignment(Qt::AlignTop);
    // m_contentLayout->addLayout(m_vContentLayout);
    m_scrollView = new FluVScrollView;
    m_scrollView->getMainLayout()->setAlignment(Qt::AlignTop);
    m_contentLayout->addWidget(m_scrollView, 1);


    m_projectDetailCard = new ProjectDetailCard;
    connect(m_projectDetailCard, &ProjectDetailCard::clickedShowReleaseBtn, this, &StatsWindow::onClickedShowReleaseBtn);
    m_scrollView->getMainLayout()->addWidget(m_projectDetailCard, 0, Qt::AlignTop | Qt::AlignHCenter);

    // 连接网络响应信号
    connect(m_networkManager, &QNetworkAccessManager::finished, this, &StatsWindow::onNetworkReply);

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
}


void StatsWindow::onClickedShowReleaseBtn()
{
        // 移除除了第一个窗口的其他窗口
    while (m_scrollView->getMainLayout()->count() > 1) {
        auto widget = m_scrollView->getMainLayout()->itemAt(1)->widget();
        m_scrollView->getMainLayout()->takeAt(1);
        // widget->deleteLater();
        delete widget;
    }

    // 向远端发送http请求获取仓库信息
    QString userOrOrganizationName = m_projectDetailCard->getUserOrOrganizationName();
    QString repositoryName = m_projectDetailCard->getRepositoryName();
    // LOG_DEBUG << "userOrOrganizationName:" << userOrOrganizationName << " repositoryName:" << repositoryName;

    QString url = APIRoot + "repos/" + userOrOrganizationName + "/" + repositoryName + "/releases";
    
    // 发送GET请求
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    request.setRawHeader("User-Agent", "GithubReleaseStats/1.0");
    request.setRawHeader("Accept", "application/vnd.github.v3+json");
    m_networkManager->get(request);
}

void StatsWindow::onNetworkReply(QNetworkReply* reply)
{
    // 检查网络响应是否有错误
    if (reply->error() != QNetworkReply::NoError) {
        QMessageBox::warning(this, "Network Error", 
                             QString("Network error occurred: %1").arg(reply->errorString()));
        reply->deleteLater();
        return;
    }

    // 获取响应数据
    QByteArray responseData = reply->readAll();
    
    // 解析JSON数据
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isArray()) {
        QMessageBox::warning(this, "Data Error", 
                             "Invalid data received from server");
        reply->deleteLater();
        return;
    }

    // // 移除除了第一个窗口的其他窗口
    // while (m_scrollView->getMainLayout()->count() > 1) {
    //     m_scrollView->getMainLayout()->removeWidget(m_scrollView->getMainLayout()->itemAt(1)->widget());
    // }

    QJsonArray releaseInfos = jsonDoc.array();

    // 遍历releasesInfos数组，并获取每个发布信息
    for (const QJsonValue& releaseInfo : releaseInfos) {

        // Info info();
        // ReleaseInfo releaseInfo(,);


        QJsonObject releaseInfoObj = releaseInfo.toObject();
        
        QString tagName = releaseInfoObj["tag_name"].toString();
        // "author" "login"
        // QString authorLogin = releaseInfoObj["author"]["login"].toString();
        
        QString author = releaseInfoObj["author"].toObject()["login"].toString();
        QString publishAt = releaseInfoObj["published_at"].toString();
        

        // ReleaseInfo releaseInfo(publishAt, author, );
        // LOG_DEBUG << "Published on:" << publishAt;
        // LOG_DEBUG << "Release Author:" << author;
        // LOG_DEBUG << "Downloads:" << nDownloadCounts;

        int nDownloadCounts = 0;

        QList<DownloadInfo> downloadInfos;
        for (const QJsonValue& asset : releaseInfoObj["assets"].toArray()) {
            QJsonObject assetObj = asset.toObject();
            QString name = assetObj["name"].toString();
            QString browserDownloadUrl = assetObj["browser_download_url"].toString();

            QString updateAt = assetObj["updated_at"].toString();
            int size = assetObj["size"].toInt() / (1024 * 1024); // size转换为MB
            QString sizeStr = QString::number(size) + "MB";

            int downloadCount = assetObj["download_count"].toInt();


            DownloadInfo downloadInfo(name, sizeStr, updateAt, downloadCount, browserDownloadUrl);
            downloadInfos.append(downloadInfo);

            // LOG_DEBUG << "Asset Name:" << name << " Downloads:" << downloadCount << " UpdateAt:" << updateAt;

            nDownloadCounts += downloadCount;
        }

        ReleaseInfo releaseInfo(publishAt, author, nDownloadCounts);
        Info info(tagName, releaseInfo, downloadInfos);

        auto infoCard = new InfoCard(info);
        m_scrollView->getMainLayout()->addWidget(infoCard, 0, Qt::AlignTop | Qt::AlignHCenter);
    }

    
    
    
    // TODO: 处理获取到的发布信息，显示在UI上
    // 这里应该处理releases数组中的数据，并更新UI
    
    reply->deleteLater();
}

void StatsWindow::onThemeChanged()
{
    if (FluThemeUtils::isLightTheme())
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
#ifndef Q_OS_MACOS
        m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::black);
        m_titleBar->closeButton()->setActiveForegroundColor(Qt::black);
        m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::black);
#endif
        m_titleBar->show();
    }
    else if(FluThemeUtils::isDarkTheme () || FluThemeUtils::isAtomOneDarkTheme())
    {
        m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
        m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::white);
        m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::white);
#ifndef Q_OS_MACOS
        m_titleBar->minimizeButton()->setActiveForegroundColor(Qt::white);
        m_titleBar->closeButton()->setActiveForegroundColor(Qt::white);
        m_titleBar->maximizeButton()->setActiveForegroundColor(Qt::white);
#endif
        m_titleBar->show();
    }

    // just do stylesheet;
    FluStyleSheetUitls::setQssByFileName("StatsWindow.qss", this, FluThemeUtils::getUtils()->getTheme());
    setWindowIcon(FluIconUtils::getFluentIcon(FluAwesomeType::Library, FluThemeUtils::getUtils()->getTheme()));    
}