#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QWidget>
#include <QString>
#include <QLabel>
#include <QListWidget>
#include <QMouseEvent>

namespace Ui {
class ListWidget;
}

class ListWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListWidget(QWidget *parent = nullptr, const QString& username = "", const QString& email = "");
    ~ListWidget();

private:
    Ui::ListWidget *ui;
    QLabel *m_usernameLabel;
    QLabel *m_emailLabel;
public:
    QString username;
    QString email;

protected:
    // 重写鼠标按下事件：点击Widget时选中对应的QListWidgetItem
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // LISTWIDGET_H
