#include "InfoCard.h"
#include "FluHyperLinkButton.h"
#include "FluLabel.h"
#include "FluUtils.h"
#include "FluVSplitLine.h"
#include <QVBoxLayout>
InfoCard::InfoCard(Info info, QWidget *parent) : QWidget(parent), m_info(info)
{
    auto vMainLayout = new QVBoxLayout(this);
    setLayout(vMainLayout);

    auto tagNameLabel = new FluLabel;
    tagNameLabel->setText(m_info.getTagName());
    auto splitLine = new FluVSplitLine;
    vMainLayout->addWidget(tagNameLabel, 0, Qt::AlignHCenter);
    vMainLayout->addWidget(splitLine);

    // Release Info
    auto releaseInfoLabel = new FluLabel;
    releaseInfoLabel->setText("Release Info:");
    vMainLayout->addWidget(releaseInfoLabel);

    auto publishedOnLabel = new FluLabel;
    auto releaseAuthorLabel = new FluLabel;
    auto downloadsLabel = new FluLabel;

    publishedOnLabel->setText("Published On: " + m_info.getReleaseInfo().getPublishedOn());
    releaseAuthorLabel->setText("Release Author: " + m_info.getReleaseInfo().getReleaseAuthor());
    downloadsLabel->setText("Downloads: " + QString::number(m_info.getReleaseInfo().getDownloads()));

    vMainLayout->addWidget(publishedOnLabel);
    vMainLayout->addWidget(releaseAuthorLabel);
    vMainLayout->addWidget(downloadsLabel);

    // downloadinfos
    auto downloadInfosLabel = new FluLabel;
    downloadInfosLabel->setText("Download Infos:");
    vMainLayout->addWidget(downloadInfosLabel);
    for (auto downloadInfo : m_info.getDownloadInfos())
    {
        auto linkBtn = new FluHyperLinkButton(downloadInfo.getBrowserDownloadUrl());
        // linkBtn->setAlign(FluLabel::AlignLeft);
        linkBtn->setText(downloadInfo.getName() + "(" + downloadInfo.getSize() + ")");
        vMainLayout->addWidget(linkBtn);

        auto label = new FluLabel;

        QString text = "Last Updated: " + downloadInfo.getLastUpdated() + " Download Count: " + QString::number(downloadInfo.getDownloadCount());
        label->setText(text);
        vMainLayout->addWidget(label);
    }

    setFixedWidth(438);
    onThemeChanged();
    connect(FluThemeUtils::getUtils(), &FluThemeUtils::themeChanged, this, [=]() { onThemeChanged(); });
}

InfoCard::~InfoCard()
{
}

void InfoCard::onThemeChanged()
{
    FluStyleSheetUitls::setQssByFileName("InfoCard.qss", this, FluThemeUtils::getUtils()->getTheme());
}
