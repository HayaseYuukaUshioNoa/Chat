#include "chatdialog.h"
#include "ui_chatdialog.h"
#include <QListWidgetItem>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QThread>
#include <QJsonObject>
#include "tcpmgr.h"
#include "listwidget.h"
#include <QJsonArray>
#include <userinfowidget.h>

ChatDialog::ChatDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
    show_chat_user_list();
    // 禁用编辑
    ui->chat_data_list->setEditTriggers(QAbstractItemView::NoEditTriggers);

    add_chat_user();

    connect(this, &ChatDialog::sig_show_dialog, this, &ChatDialog::slot_show_dialog);

    connect(ui->chat_user_list, &ChatUserList::sig_loading_chat_user, this, &ChatDialog::slot_loading_chat_user);
    connect(ui->send_btn, &QPushButton::clicked, this, &ChatDialog::slot_send_message);
    connect(ui->recv_btn, &QPushButton::clicked, this, &ChatDialog::slot_recv_message);
    connect(ui->search_list, &QListWidget::itemClicked, this, &ChatDialog::slot_show_adduser_dialog);
    connect(ui->new_friend_list, &QListWidget::itemClicked, this, &ChatDialog::slot_friend_verify_dialog);
    connect(ui->contact_person_list, &QListWidget::itemClicked, this, &ChatDialog::slot_show_messages);

    connect(TcpMgr::instance().get(), &TcpMgr::sig_find_success, this, &ChatDialog::slot_find_success);
    connect(TcpMgr::instance().get(), &TcpMgr::sig_find_failed, this, &ChatDialog::slot_find_failed);
    connect(TcpMgr::instance().get(), &TcpMgr::sig_friend_req_failed, this, &ChatDialog::slot_friend_req_failed);
    connect(TcpMgr::instance().get(), &TcpMgr::sig_friend_req_success, this, &ChatDialog::slot_friend_req_success);
    connect(TcpMgr::instance().get(), &TcpMgr::sig_show_friend_req, this, &ChatDialog::slot_show_friend_req);
    connect(TcpMgr::instance().get(), &TcpMgr::sig_friend_response, this, &ChatDialog::slot_friend_response);
    connect(TcpMgr::instance().get(), &TcpMgr::sig_show_contact, this, &ChatDialog::slot_show_contact);
    connect(TcpMgr::instance().get(), &TcpMgr::sig_show_messages, this, &ChatDialog::tcp_slot_show_messages);
    connect(TcpMgr::instance().get(), &TcpMgr::sig_send_message, this, &ChatDialog::tcp_slot_send_message);
    connect(TcpMgr::instance().get(), &TcpMgr::sig_recv_message, this, &ChatDialog::tcp_slot_recv_message);
}

ChatDialog::~ChatDialog()
{
    qDebug() << "free ChatDialog";
    delete ui;
}

void ChatDialog::add_chat_user()
{
    for(int i = 0; i < 10; ++i){
        auto item = new QListWidgetItem(ui->chat_user_list);
        auto widget = new QWidget();
        auto vbox = new QVBoxLayout();
        auto username = new QLabel();
        username->setText(QString("用户名: %1").arg(i));
        vbox->addWidget(username);
        auto email = new QLabel();
        email->setText(QString("邮箱: %1").arg("www.example.com"));
        vbox->addWidget(email);
        // 设置高度
        widget->setLayout(vbox);
        item->setSizeHint(widget->sizeHint());
        ui->chat_user_list->setItemWidget(item, widget);
    }
}

void ChatDialog::add_search_item(const QString& username, const QString& email)
{
    auto item = new QListWidgetItem(ui->search_list);
    auto widget = new ListWidget(ui->search_list, username, email);
    item->setSizeHint(widget->sizeHint());
    ui->search_list->setItemWidget(item, widget);
}

void ChatDialog::add_contact_person(const QString &username, const QString &email)
{
    auto item = new QListWidgetItem(ui->contact_person_list);
    auto widget = new ListWidget(ui->contact_person_list, username, email);
    item->setSizeHint(widget->sizeHint());
    ui->contact_person_list->setItemWidget(item, widget);
}

void ChatDialog::add_new_friend(const QString &username, const QString &email, int status)
{
    auto item = new QListWidgetItem(ui->new_friend_list);
    auto widget = new UserInfoWidget(username, email, static_cast<UserInfoWidget::FriendStatus>(status), ui->new_friend_list);
    item->setSizeHint(widget->sizeHint());
    ui->new_friend_list->setItemWidget(item, widget);
}

QWidget *ChatDialog::create_chat_item(const QString& uname, const QString &text, bool is_me)
{
    auto widget = new QWidget();
    auto hbox = new QHBoxLayout();
    if(!is_me){
        // 他人消息左对齐
        hbox->setAlignment(Qt::AlignLeft);
        QString content = "用户名:" + uname + "\n";
        content += text;
        auto message = new QLabel(content);
        // 灰色
        message->setStyleSheet(R"(
            background-color: #f0f0f0;
            border-radius: 8px;
            padding: 8px;
            max-width: 200px;
        )");
        // 设置自动换行
        message->setWordWrap(true);
        hbox->addWidget(message);
    }else{
        hbox->setAlignment(Qt::AlignRight);
        QString content = "用户名:" + uname + "\n";
        content += text;
        auto message = new QLabel(content);
        // 蓝色
        message->setStyleSheet(R"(
            background-color: #99ccff;
            border-radius: 8px;
            padding: 8px;
            max-width: 200px;
        )");
        // 设置自动换行
        message->setWordWrap(true);
        hbox->addWidget(message);
    }
    widget->setLayout(hbox);
    return widget;
}

void ChatDialog::show_chat_user_list()
{
    ui->chat_user_list->show();
    ui->search_list->hide();
    ui->contact_person_list->hide();
    ui->new_friend_list->hide();
}

void ChatDialog::show_search_list()
{
    ui->chat_user_list->hide();
    ui->search_list->show();
    ui->contact_person_list->hide();
    ui->new_friend_list->hide();
}

void ChatDialog::show_contact_person_list()
{
    ui->chat_user_list->hide();
    ui->search_list->hide();
    ui->new_friend_list->hide();
    QJsonObject json;
    json["uid"] = info.uid;
    emit TcpMgr::instance()->sig_send_msg(info.uid, MsgType::MSG_SHOW_CONTACT, json);
    ui->contact_person_list->show();
}

void ChatDialog::show_new_friend_list()
{
    ui->chat_user_list->hide();
    ui->search_list->hide();
    ui->contact_person_list->hide();
    QJsonObject json;
    json["uid"] = info.uid;
    emit TcpMgr::instance()->sig_send_msg(info.uid, MsgType::MSG_SHOW_FRIEND_REQ, json);
    ui->new_friend_list->show();
}

void ChatDialog::slot_loading_chat_user()
{
    if(loading_){
        return;
    }

    loading_ = true;
    loading_dialog_ = new LoadingDialog(this);
    loading_dialog_->show();
    add_chat_user();
    loading_dialog_->deleteLater();
    loading_ = false;
}

void ChatDialog::slot_send_message()
{
    QString text = ui->textEdit->toPlainText();
    if(text.isEmpty()){
        return;
    }
    QJsonObject json;
    json["sender_id"] = info.uid;
    json["sender_name"] = info.username;
    json["content"] = text;
    json["receiver_name"] = this->receiver_username;
    emit TcpMgr::instance()->sig_send_msg(info.uid, MsgType::MSG_SEND_MESSAGE, json);
    auto chat_widget = create_chat_item(info.username, text, true);
    QListWidgetItem* item = new QListWidgetItem(ui->chat_data_list);
    item->setSizeHint(chat_widget->sizeHint() + QSize(0, 10));
    ui->chat_data_list->setItemWidget(item, chat_widget);
    // 滚动到底部
    ui->chat_data_list->scrollToBottom();
    ui->textEdit->clear();
}

void ChatDialog::slot_recv_message()
{
    QString text = ui->textEdit->toPlainText();
    if(text.isEmpty()){
        return;
    }
    QListWidgetItem* item = new QListWidgetItem(ui->chat_data_list);
    auto chat_widget = create_chat_item("jack", text, false);
    item->setSizeHint(chat_widget->sizeHint() + QSize(0, 10));
    ui->chat_data_list->setItemWidget(item, chat_widget);
    // 滚动到底部
    ui->chat_data_list->scrollToBottom();
    ui->textEdit->clear();
}

void ChatDialog::slot_find_failed()
{
    find_failed_dialog_ = new FindFailedDialog(this);
    find_failed_dialog_->show();
}

void ChatDialog::slot_find_success(const QJsonObject &json)
{
    QString username = json["username"].toString();
    QString email = json["email"].toString();
    qDebug() << "username: " << username << ", email: " << email;
    add_search_item(username, email);
    // qDebug() << "slot_find_success";
}

void ChatDialog::slot_friend_req_failed()
{
    friend_req_dialog_ = new FriendRequestDialog(this);
    friend_req_dialog_->show();
}

void ChatDialog::slot_friend_req_success(const QJsonObject &json)
{
    QString from_username = json["from_username"].toString();
    QString from_email = json["from_email"].toString();
    qDebug() << "from_username: " << from_username << ", from_email: " << from_email;
    // qDebug() << "slot_friend_req_success";
}

void ChatDialog::slot_show_friend_req(const QJsonObject &json, bool success)
{
    ui->new_friend_list->clear();
    if(success){
        QJsonArray array = json["user_infos"].toArray();
        for(int i = 0; i < array.size(); ++i){
            QJsonObject info = array[i].toObject();
            QString username = info["username"].toString();
            QString email = info["email"].toString();
            int status = info["status"].toInt();
            qDebug() << username << ", " << email << ", " << status;
            add_new_friend(username, email, status);
        }
        // qDebug() << "slot_show_friend_req success";
    }else{
        qDebug() << "slot_show_friend_req failed";
    }
}

void ChatDialog::slot_friend_response(const QJsonObject &json, bool success)
{
    if(success){
        qDebug() << "slot_friend_response success";
    }else{
        qDebug() << "slot_friend_response failed";
    }
}

void ChatDialog::slot_show_contact(const QJsonObject &json, bool success)
{
    ui->contact_person_list->clear();
    if(success){
        QJsonArray array = json["user_infos"].toArray();
        for(int i = 0; i < array.size(); ++i){
            QJsonObject info = array[i].toObject();
            QString username = info["username"].toString();
            QString email = info["email"].toString();
            qDebug() << username << ", " << email;
            add_contact_person(username, email);
        }
    }else{
        qDebug() << "slot_show_contact failed";
    }
}

void ChatDialog::tcp_slot_show_messages(const QJsonObject &json, bool success)
{
    ui->chat_data_list->clear();
    if(success){
        QJsonArray array = json["messages"].toArray();
        for(int i = 0; i < array.size(); ++i){
            QJsonObject msg = array[i].toObject();
            QString sender_name = msg["sender_name"].toString();
            QString receiver_name = msg["receiver_name"].toString();
            int sender_id = msg["sender_id"].toInt();
            int receiver_id = msg["receiver_id"].toInt();
            QString content = msg["content"].toString();
            qDebug() << "sender_name: " << sender_name << ", receiver_name" << receiver_name;
            QWidget* chat_widget = nullptr;
            if(info.uid == sender_id){
               chat_widget = create_chat_item(sender_name, content, true);
            }else{
                chat_widget = create_chat_item(sender_name, content, false);
            }
            QListWidgetItem* item = new QListWidgetItem(ui->chat_data_list);
            item->setSizeHint(chat_widget->sizeHint() + QSize(0, 10));
            ui->chat_data_list->setItemWidget(item, chat_widget);
        }
        qDebug() << "tcp_slot_show_messages success";
    }else{
        qDebug() << "tcp_slot_show_messages failed";
    }
}

void ChatDialog::tcp_slot_send_message(const QJsonObject &json, bool success)
{
    if(success){
        qDebug() << "tcp_slot_send_message success";
    }else{
        qDebug() << "tcp_slot_send_message failed";
    }
}

void ChatDialog::tcp_slot_recv_message(const QJsonObject &json, bool success)
{
    if(success){
        qDebug() << "tcp_slot_recv_message success";
        QString sender_name = json["sender_name"].toString();
        int sender_id = json["sender_id"].toInt();
        QString content = json["content"].toString();
        qDebug() << "sender_name: " << sender_name << ", sender_id" << sender_id;
        qDebug() << "content: " << content;
        auto chat_widget = create_chat_item(sender_name, content, false);
        QListWidgetItem* item = new QListWidgetItem(ui->chat_data_list);
        item->setSizeHint(chat_widget->sizeHint() + QSize(0, 10));
        ui->chat_data_list->setItemWidget(item, chat_widget);
        // 滚动到底部
        ui->chat_data_list->scrollToBottom();
        ui->textEdit->clear();
    }else{
        qDebug() << "tcp_slot_recv_message failed";
    }
}

void ChatDialog::on_pushButton_clicked()
{
    show_chat_user_list();
}


void ChatDialog::on_pushButton_2_clicked()
{
    show_contact_person_list();
}


void ChatDialog::on_search_edit_textChanged(const QString &arg1)
{
    if(arg1.isEmpty()){
        show_chat_user_list();
        return;
    }
    show_search_list();
}

// 查找用户
void ChatDialog::on_search_btn_clicked()
{
    ui->search_list->clear();
    QString username = ui->search_edit->text();
    // 向服务器发送请求查找用户
    QJsonObject json;
    json["username"] = username;
    qDebug() << "uid: " << info.uid;
    emit TcpMgr::instance()->sig_send_msg(info.uid, MsgType::MSG_FIND, json);
}


void ChatDialog::on_search_edit_returnPressed()
{

}

void ChatDialog::slot_show_adduser_dialog(QListWidgetItem *item)
{
    if(friend_req_dialog_ == nullptr){
        find_user_dialog_ = new FindUserDialog(this);
    }
    find_user_dialog_->info = info;
    auto widget = ui->search_list->itemWidget(item);
    auto list_widget = qobject_cast<ListWidget*>(widget);
    QString find_username = list_widget->username;
    QString find_useremail = list_widget->email;
    emit find_user_dialog_->sig_show_adduser_dialog(find_username, find_useremail);
}

void ChatDialog::slot_friend_verify_dialog(QListWidgetItem *item)
{
    if(friend_verify_dialog_ == nullptr){
        friend_verify_dialog_ = new FriendVerifyDialog(this);
    }
    friend_verify_dialog_->info = info;
    auto widget = ui->new_friend_list->itemWidget(item);
    auto user_info_widget = qobject_cast<UserInfoWidget*>(widget);
    QString from_username = user_info_widget->username_;
    QString from_useremail = user_info_widget->email_;
    emit friend_verify_dialog_->sig_show_verify_dialog(from_username, from_useremail);
}

void ChatDialog::slot_show_messages(QListWidgetItem *item)
{
    auto widget = ui->contact_person_list->itemWidget(item);
    auto list_widget = qobject_cast<ListWidget*>(widget);
    QString receiver_name = list_widget->username;
    QString receiver_username = receiver_name;
    QString receiver_email = list_widget->email;
    quint16 sender_uid = info.uid;
    QJsonObject json;
    this->receiver_username = receiver_name;
    json["sender_uid"] = sender_uid;
    json["receiver_name"] = receiver_name;
    json["receiver_email"] = receiver_email;
    emit TcpMgr::instance()->sig_send_msg(info.uid, MsgType::MSG_SHOW_MESSAGES, json);
}

void ChatDialog::on_pushButton_3_clicked()
{
    show_new_friend_list();
}

void ChatDialog::slot_show_dialog()
{
    ui->username->setText(info.username);
    this->show();
}

