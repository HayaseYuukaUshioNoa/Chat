#include "timerbutton.h"
#include <QMouseEvent>


TimerButton::TimerButton(QWidget *parent): QPushButton(parent) {
    timer_ = new QTimer(this);
    connect(timer_, &QTimer::timeout, this, [this](){
        --counter_;
        if(counter_ <= 0){
            timer_->stop();
            counter_ = 10;
            this->setEnabled(true);
            this->setText("获取");
        }else{
            this->setText(QString::number(counter_));
        }
    });
}

TimerButton::~TimerButton()
{
    if(timer_){
        timer_->stop();
    }
}

void TimerButton::mouseReleaseEvent(QMouseEvent *e)
{
    // 鼠标左键
    if(e->button() == Qt::LeftButton){
        this->setEnabled(false);
        this->setText(QString::number(counter_));
        timer_->start(1000);
        emit this->clicked();
    }
    QPushButton::mouseMoveEvent(e);
}
