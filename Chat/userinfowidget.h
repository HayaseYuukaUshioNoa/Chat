#ifndef USERINFOWIDGET_H
#define USERINFOWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>

// 好友 Widget：显示用户名、邮箱和好友状态
class UserInfoWidget : public QWidget {
    Q_OBJECT
public:
    // 好友状态枚举
    enum FriendStatus {
        NotFriend = 0,    // 非好友
        AlreadyFriend = 1 // 已成为好友
    };

    explicit UserInfoWidget(const QString& username, const QString& email, FriendStatus status, QWidget *parent = nullptr);

    // 更新好友状态
    void setStatus(FriendStatus status);
    QString username_;
    QString email_;
    FriendStatus status_;
protected:
    // 重写鼠标事件：点击时选中对应的QListWidgetItem
    void mousePressEvent(QMouseEvent *event) override;

private:
    QLabel *m_usernameLabel; // 用户名
    QLabel *m_emailLabel;    // 邮箱
    QLabel *m_statusLabel;   // 好友状态
};

#endif // USERINFOWIDGET_H
