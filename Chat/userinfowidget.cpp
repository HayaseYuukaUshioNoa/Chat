#include "userinfowidget.h"
#include "ui_userinfowidget.h"
#include <QListWidget>

UserInfoWidget::UserInfoWidget(const QString& username, const QString& email, FriendStatus status, QWidget *parent)
    : QWidget(parent)
{
    username_ = username;
    email_ = email;
    status_ = status;
    // 主布局：水平布局（从左到右排列所有元素）
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(15, 10, 15, 10); // 外边距
    mainLayout->setSpacing(10);                    // 元素间距

    // 1. 用户名标签（加粗显示）
    m_usernameLabel = new QLabel(username, this);
    QFont usernameFont = m_usernameLabel->font();
    usernameFont.setBold(true);
    usernameFont.setPointSize(12);
    m_usernameLabel->setFont(usernameFont);
    m_usernameLabel->setStyleSheet("color: #222"); // 固定最小宽度

    // 2. 邮箱标签（灰色小字）
    m_emailLabel = new QLabel(email, this);
    QFont emailFont = m_emailLabel->font();
    emailFont.setPointSize(10);
    m_emailLabel->setFont(emailFont);
    m_emailLabel->setStyleSheet("color: #666"); // 固定最小宽度

    // 3. 好友状态标签（带颜色区分）
    m_statusLabel = new QLabel(this);
    setStatus(status); // 设置状态文本和样式
    m_statusLabel->setAlignment(Qt::AlignCenter);     // 文本居中

    // 添加所有元素到水平布局
    mainLayout->addWidget(m_usernameLabel);
    mainLayout->addWidget(m_emailLabel);
    mainLayout->addWidget(m_statusLabel);
    mainLayout->addStretch(); // 右侧留白，确保元素左对齐

    // 设置Widget样式（背景和边框）
    setStyleSheet("background: white; border-bottom: 1px solid #f0f0f0;");
}

void UserInfoWidget::setStatus(FriendStatus status)
{
    switch (status) {
    case NotFriend:
        m_statusLabel->setText("非好友");
        m_statusLabel->setStyleSheet("color: #f44336; font-size: 10px;"); // 红色
        break;
    case AlreadyFriend:
        m_statusLabel->setText("已好友");
        m_statusLabel->setStyleSheet("color: #4caf50; font-size: 10px;"); // 绿色
        break;
    }
}

void UserInfoWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event); // 确保子控件能响应事件

    if (event->button() == Qt::LeftButton) {
        // 找到父级QListWidget并选中当前Item
        if (QListWidget *listWidget = qobject_cast<QListWidget*>(parentWidget())) {
            QPoint posInList = mapTo(listWidget, QPoint(0, 0));
            if (QListWidgetItem *item = listWidget->itemAt(posInList)) {
                listWidget->setCurrentItem(item);
            }
        }
    }
}
