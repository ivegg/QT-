#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include "tcpclient.h"
#include <QVector>

#include "ui_addgroup.h"

class AddGroup : public QWidget
{
    Q_OBJECT

public:
    explicit AddGroup(SelfInfo selfInfo, TcpClient* tcp, QWidget *parent = nullptr);
    ~AddGroup();

private slots:
    void onInputChanged();
    void onCreateClicked();
    void onFriendListReceived(json msg); // 处理好友列表

private:
    void updateCreateButtonState();
    void requestFriendList(); // 请求好友列表

    Ui::addgroup *ui;

    QLineEdit* lineEdit;           // 群聊名称输入框
    QListWidget* listWidget;       // 好友列表
    QPushButton* pushButton_create;// 创建按钮
    QPushButton* pushButton_cancel;// 取消按钮
    QTextEdit* textEdit;           // 备注或验证信息（可选）

    SelfInfo selfInfo;
    TcpClient* tcp;
    QVector<FriendInfo> friends;
};

#endif // ADDGROUP_H
