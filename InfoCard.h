#include <QWidget>
#include "Info.h"
#include <QStyleOption>
#include <QPainter>

class InfoCard : public QWidget
{
    Q_OBJECT

public:
    InfoCard(Info info, QWidget *parent = nullptr);
    ~InfoCard();
    void paintEvent(QPaintEvent* event)
    {
        QStyleOption opt;
        opt.initFrom(this);
        QPainter painter(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
    }
public slots:
    // void onClickedShowReleaseBtn();
    void onThemeChanged();
private:
    Info m_info;
};