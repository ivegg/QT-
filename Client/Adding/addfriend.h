#ifndef ADDFRIEND_H
#define ADDFRIEND_H

#include <QWidget>
#include <QVector>
#include "tcpclient.h"

#include "addgroup.h" // 新增：包含群聊窗口头文件

namespace Ui {
class AddFriend;
}

class AddFriend : public QWidget
{
    Q_OBJECT

public:
    explicit AddFriend(SelfInfo _info,TcpClient* fd,QWidget *parent = nullptr);
    ~AddFriend();

    void Init();

private slots:
    void on_pushButton_search_clicked();

    void  on_radioButton_toggled(bool isChecked);

    void  CmdHandler(json msg);

    void on_pushButton_add_clicked();

    void on_pushButton_create_clicked(); // 新增：创建群聊按钮槽

private:
    Ui::AddFriend *ui;
    QVector<QString> list;
    TcpClient* t;
    //0 friend 1 group
    int m_type = 0;
    SelfInfo info;

    AddGroup* addGroupWin = nullptr;
};

#endif // ADDFRIEND_H
