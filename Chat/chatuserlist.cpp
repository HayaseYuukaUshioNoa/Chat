#include "chatuserlist.h"
#include <QScrollBar>
#include <QEvent>
#include <QWheelEvent>

ChatUserList::ChatUserList(QWidget* parent): QListWidget(parent) {
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 视口安装事件过滤器
    this->viewport()->installEventFilter(this);
}

bool ChatUserList::eventFilter(QObject *obj, QEvent *event)
{
    // 检查事件是否是鼠标悬浮进入或离开
    if (obj == this->viewport()) {
        if (event->type() == QEvent::Enter) {
            // 鼠标进入，显示滚动条
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        } else if (event->type() == QEvent::Leave) {
            // 鼠标离开，隐藏滚动条
            this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        }
    }

    // 检查事件是否是鼠标滚轮事件
    if (obj == this->viewport() && event->type() == QEvent::Wheel) {
        QWheelEvent *wheelEvent = static_cast<QWheelEvent*>(event);
        int numDegrees = wheelEvent->angleDelta().y() / 8;
        int numSteps = numDegrees / 15; // 计算滚动步数

        // 设置滚动幅度
        this->verticalScrollBar()->setValue(this->verticalScrollBar()->value() - numSteps);

        // 检查是否滚动到底部
        QScrollBar *scrollBar = this->verticalScrollBar();
        int maxScrollValue = scrollBar->maximum();
        int currentValue = scrollBar->value();
        //int pageSize = 10; // 每页加载的联系人数量

        if (maxScrollValue - currentValue <= 0) {
            // 滚动到底部，加载新的联系人
            qDebug()<< "loading more chat user";
            //发送信号通知聊天界面加载更多聊天内容
            emit sig_loading_chat_user();
        }

        return true; // 停止事件传递
    }

    return QListWidget::eventFilter(obj, event);
}
