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

FRAMELESSHELPER_USE_NAMESPACE
StatsWindow::StatsWindow(QWidget* parent /*= nullptr*/) : FluFrameLessWidget(parent)
{
    setWindowTitle("Github Release Stats Dev");
#ifndef _DEBUG
    setWindowTitle("Github Release Stats");
#endif

    setWindowIcon(QIcon("../res/Tiles/GalleryIcon.ico"));
#ifdef USE_QRC
    setWindowIcon(QIcon(":/res/Tiles/GalleryIcon.ico"));
#endif


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

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
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
}
