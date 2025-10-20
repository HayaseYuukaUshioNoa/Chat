#include "listwidget.h"
#include "ui_listwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

ListWidget::ListWidget(QWidget *parent, const QString& uname, const QString& mail)
    : QWidget(parent)
    , ui(new Ui::ListWidget), username(uname), email(mail)
{
    // 设置布局（水平排列）
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 5, 10, 5); // 边距
    layout->setSpacing(15);                  // 控件间距

    // 用户名标签（加粗显示）
    m_usernameLabel = new QLabel(username, this);
    QFont usernameFont = m_usernameLabel->font();
    usernameFont.setBold(true);
    m_usernameLabel->setFont(usernameFont);
    m_usernameLabel->setStyleSheet("color: #333;"); // 文字颜色

    // 邮箱标签（灰色小字）
    m_emailLabel = new QLabel(email, this);
    QFont emailFont = m_emailLabel->font();
    emailFont.setPointSize(10); // 字号小一些
    m_emailLabel->setFont(emailFont);
    m_emailLabel->setStyleSheet("color: #666;");

    // 添加到布局
    layout->addWidget(m_usernameLabel);
    layout->addWidget(m_emailLabel);
    layout->addStretch(); // 右侧留白
}

ListWidget::~ListWidget()
{
    delete ui;
}

void ListWidget::mousePressEvent(QMouseEvent *event)
{
    // 让父类处理事件（确保可能的子控件能响应）
    QWidget::mousePressEvent(event);

    // 点击左键时触发选中
    if (event->button() == Qt::LeftButton) {
        // 获取父级QListWidget
        QListWidget *listWidget = qobject_cast<QListWidget*>(parentWidget());
        if (listWidget) {
            // 计算当前Widget在ListWidget中的位置
            QPoint posInList = mapTo(listWidget, QPoint(0, 0));
            // 找到对应的Item并选中
            QListWidgetItem *item = listWidget->itemAt(posInList);
            if (item) {
                listWidget->setCurrentItem(item);
            }
        }
    }
}
