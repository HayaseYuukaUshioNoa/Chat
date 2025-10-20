#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include "loadingdialog.h"
#include <QListWidget>
#include <finduserdialog.h>
#include <global.h>
#include <findfaileddialog.h>
#include <friendrequestdialog.h>
#include <friendverifydialog.h>

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = nullptr);
    ~ChatDialog();

    void add_chat_user();
    void add_search_item(const QString& username, const QString& email);
    void add_contact_person(const QString& username, const QString& email);
    void add_new_friend(const QString& username, const QString& email, int status);
private:
    QWidget* create_chat_item(const QString& uname, const QString& text, bool is_me);
    void show_chat_user_list();
    void show_search_list();
    void show_contact_person_list();
    void show_new_friend_list();
private:
    Ui::ChatDialog *ui;
    LoadingDialog* loading_dialog_ = nullptr;
    FindUserDialog* find_user_dialog_ = nullptr;
    FindFailedDialog* find_failed_dialog_ = nullptr;
    FriendRequestDialog* friend_req_dialog_ = nullptr;
    FriendVerifyDialog* friend_verify_dialog_ = nullptr;
    bool loading_ = false;
public:
    ServerInfo info;
    QString receiver_username;
signals:
    void sig_show_dialog();
private slots:
    void slot_loading_chat_user();
    void slot_send_message();
    void slot_recv_message();
    void slot_find_failed();
    void slot_find_success(const QJsonObject& json);
    void slot_friend_req_failed();
    void slot_friend_req_success(const QJsonObject& json);
    void slot_show_friend_req(const QJsonObject& json, bool success);
    void slot_friend_response(const QJsonObject& json, bool success);
    void slot_show_contact(const QJsonObject& json, bool success);
    void tcp_slot_show_messages(const QJsonObject& json, bool success);
    void tcp_slot_send_message(const QJsonObject& json, bool success);
    void tcp_slot_recv_message(const QJsonObject& json, bool success);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_search_edit_textChanged(const QString &arg1);
    void on_search_btn_clicked();
    void on_search_edit_returnPressed();
    void slot_show_adduser_dialog(QListWidgetItem *item);
    void slot_friend_verify_dialog(QListWidgetItem *item);
    void slot_show_messages(QListWidgetItem *item);
    void on_pushButton_3_clicked();
    void slot_show_dialog();
};

#endif // CHATDIALOG_H
