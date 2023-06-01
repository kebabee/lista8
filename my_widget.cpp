#include "my_widget.h"

#include <QPainter>

MyWidget::MyWidget(QWidget* parent)  //
    : QWidget(parent), timer(this)
{
    timer.start(timer_interval);
    connect(&timer, SIGNAL(timeout()), this, SLOT(on_timer()));
}

void MyWidget::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    painter.setBrush(QBrush(QColor(Qt::magenta)));
    painter.translate(rect().width() / 2.0, rect().height() / 2.0);
    auto side = std::min(rect().width(), rect().height());
    painter.scale(side / 200.0, side / 200.0);
    painter.setPen(Qt::NoPen);
    for (int i = 0; i < num_disks; i++)
    {
        if (i != hidden)
        {
            QRadialGradient gradient(QPointF(-7, 73), 13); // gradient(współrzędne środka koła, promień)
            gradient.setColorAt(0, Qt::magenta);
            gradient.setColorAt(1, Qt::transparent);
            painter.setBrush(gradient);
            painter.drawEllipse(-20, 60, 26, 26);
        }
        painter.rotate(360.0 / num_disks);
    }
    painter.setBrush(QBrush(QColor(Qt::black)));
    painter.drawRect(-1, -7, 1, 13);
    painter.drawRect(-7, -1, 13, 1);
}

void MyWidget::on_timer()
{
    hidden = (hidden + 1) % num_disks;
    update();
}

void MyWidget::toggle_animation()
{
    if (timer.isActive())
        timer.stop();
    else
        timer.start(timer_interval);
}
