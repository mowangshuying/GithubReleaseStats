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

    m_titleBar->chromePalette()->setTitleBarActiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarInactiveBackgroundColor(Qt::transparent);
    m_titleBar->chromePalette()->setTitleBarActiveForegroundColor(Qt::black);
    m_titleBar->chromePalette()->setTitleBarInactiveForegroundColor(Qt::black);
    m_titleBar->setFixedHeight(36);

    m_titleBar->setObjectName("titleBar");

    m_contextMenu = new FluMenu;
    auto lightAction = new FluAction;
    lightAction->setText("light");

    auto darkAction = new FluAction;
    darkAction->setText("dark");

    // auto atomOneDarkAction = new FluAction;
    // atomOneDarkAction->setText("atomOneDark");

    m_contextMenu->addAction(lightAction);
    m_contextMenu->addAction(darkAction);
    // m_contextMenu->addAction(atomOneDarkAction);

    connect(lightAction, &FluAction::triggered, this, [=]() { FluThemeUtils::getUtils()->setTheme(FluTheme::Light); });

    connect(darkAction, &FluAction::triggered, this, [=]() { FluThemeUtils::getUtils()->setTheme(FluTheme::Dark); });

    // connect(atomOneDarkAction, &FluAction::triggered, this, [=]() { FluThemeUtils::getUtils()->setTheme(FluTheme::AtomOneDark); });

    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, [=](FluTheme theme) { onThemeChanged(); });
    // onThemeChanged();
}

void StatsWindow::contextMenuEvent(QContextMenuEvent* event)
{
    m_contextMenu->exec(event->globalPos());
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
