#ifndef TIMERBUTTON_H
#define TIMERBUTTON_H

#include <QPushButton>
#include <QTimer>

class TimerButton : public QPushButton
{
public:
    TimerButton(QWidget *parent = nullptr);
    ~TimerButton();
    void mouseReleaseEvent(QMouseEvent *e) override;
private:
    QTimer* timer_ = nullptr;
    int counter_ = 10;
};

#endif // TIMERBUTTON_H
