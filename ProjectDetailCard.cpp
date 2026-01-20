#include "ProjectDetailCard.h"

ProjectDetailCard::ProjectDetailCard(QWidget *parent)
{
    m_vMainLayout = new QVBoxLayout(this);
    setLayout(m_vMainLayout);

    m_titleLabel = new FluLabel(this);
    m_titleLabel->setLabelStyle(FluLabelStyle::TitleLargeTextBlockStyle);
    m_titleLabel->setText("Enter Project Detail...");

    m_userOrOrganizationNameLineEdit = new FluLineEdit(this);
    m_repositoryNameLineEdit = new FluLineEdit(this);

    m_userOrOrganizationNameLineEdit->setPlaceholderText("User or Organization Name");
    m_repositoryNameLineEdit->setPlaceholderText("Repository Name");

    m_userOrOrganizationNameLineEdit->setFixedHeight(30);
    m_repositoryNameLineEdit->setFixedHeight(30);

    m_showReleaseBtn = new FluStyleButton(this);
    m_showReleaseBtn->setText("Show releases statistics!");

    m_vMainLayout->addWidget(m_titleLabel);
    m_vMainLayout->addWidget(m_userOrOrganizationNameLineEdit);
    m_vMainLayout->addWidget(m_repositoryNameLineEdit);
    m_vMainLayout->addWidget(m_showReleaseBtn, 0, Qt::AlignHCenter);

    connect(m_showReleaseBtn, &FluStyleButton::clicked, this, [=]() { emit clickedShowReleaseBtn(); });
}

ProjectDetailCard::~ProjectDetailCard()
{
}
