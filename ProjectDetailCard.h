#pragma once

#include "FluLabel.h"
#include "FluLineEdit.h"
#include "FluStyleButton.h"
#include <QVBoxLayout>
#include <QWidget>

class ProjectDetailCard : public QWidget
{
    Q_OBJECT

  public:
    ProjectDetailCard(QWidget *parent = nullptr);
    ~ProjectDetailCard();

    QString getUserOrOrganizationName()
    {
        return m_userOrOrganizationNameLineEdit->text();
    }

    QString getRepositoryName()
    {
        return m_repositoryNameLineEdit->text();
    }

    // void paintEvent(QPaintEvent *event);
  signals:
    void clickedShowReleaseBtn();

  protected:
    QVBoxLayout *m_vMainLayout;

    FluLabel *m_titleLabel;
    FluLineEdit *m_userOrOrganizationNameLineEdit;
    FluLineEdit *m_repositoryNameLineEdit;
    FluStyleButton *m_showReleaseBtn;
};