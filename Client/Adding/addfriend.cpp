#include "addfriend.h"
#include "ui_addfriend.h"
#include <QGraphicsDropShadowEffect>

#include "addgroup.h"

AddFriend::AddFriend(SelfInfo _info,TcpClient* fd,QWidget *parent) :
     QWidget(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
    Init();
     t=fd;
     info = _info;
     qDebug() << info.name;
     qDebug() << info.account;
     qDebug() << info.sig;
     connect(t,&TcpClient::CallAddFriend,this,&AddFriend::CmdHandler);
     connect(ui->radioButton_friend,&QRadioButton::toggled,this,&AddFriend::on_radioButton_toggled);

     connect(ui->pushButton_create, &QPushButton::clicked, this, &AddFriend::on_pushButton_create_clicked);
    // 新增：设置关闭时自动销毁
    this->setAttribute(Qt::WA_DeleteOnClose, true);
}

AddFriend::~AddFriend()
{
    delete ui;
}

void AddFriend::Init()
{
    //this->setWindowFlags(Qt::FramelessWindowHint);          //去掉标题栏无边框
    //this->setAttribute(Qt::WA_TranslucentBackground,true);
    //实例阴影shadow
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    //设置阴影距离
    shadow->setOffset(0, 0);
    //设置阴影颜色
    shadow->setColor(QColor(39,40,43,100));
    //设置阴影圆角
    shadow->setBlurRadius(10);
    ui->textEdit->setPlaceholderText("验证信息");
    setWindowTitle("查找");

}

void AddFriend::on_pushButton_search_clicked()
{
    QString search = ui->lineEdit->text();
    json msg ={{"cmd",cmd_friend_search},{"search-info",search}};
    if(m_type)
        msg["cmd"] = cmd_group_search;
    t->SendMsg(msg);      
}

void AddFriend::on_pushButton_add_clicked()
{
    int row = ui->listWidget->currentRow();
    if(row >= 0)
    {
        json msg = {{ "cmd",cmd_add_friend_request},{"sender",info.account},{"account",list[row*2].toInt()},{"msg",ui->textEdit->toPlainText()},
                {"name",info.name},{"sig",info.sig},{"icon",info.icon}};
        if(m_type)
        {
            msg["cmd"] = cmd_group_join_request;
            msg["groupName"] = list[row*2+1];
        }

        t->SendMsg(msg);
    }
}

void AddFriend::on_radioButton_toggled(bool isChecked)
{
    m_type = !isChecked;
}

void AddFriend::CmdHandler(json msg)
{
    int cmd = msg["cmd"].toInt();
    if(msg.isEmpty()) return;

    if(cmd == cmd_friend_search || cmd == cmd_group_search)
    {
        list.clear();
        ui->listWidget->clear();
        QJsonArray arr =  msg["msglist"].toArray();
        for(int i =0;i<msg["count"].toInt();i++)
        {
                 list.push_back(arr[i].toObject().value("account").toString());
                 list.push_back(arr[i].toObject()["name"].toString());
       }
        for(int i =0;i<list.size()-1;i+=2)
        {
            ui->listWidget->addItem(QString("[%1] [%2]").arg(list[i],list[i+1]));
        }
    }

    if (cmd == cmd_group_create) {
        QString res = msg["res"].toString();
        if (res == "yes") {
            QMessageBox::information(this, "提示", "群聊创建成功！");
            this->hide();
            this->deleteLater();
        }
    }
}

// 新增：创建群聊按钮槽函数
void AddFriend::on_pushButton_create_clicked()
{
    if (addGroupWin && addGroupWin->isVisible()) {
        addGroupWin->raise();
        addGroupWin->activateWindow();
        return;
    }
    addGroupWin = new AddGroup(info, t, nullptr);
    addGroupWin->setAttribute(Qt::WA_DeleteOnClose);
    connect(addGroupWin, &AddGroup::destroyed, [this]() { addGroupWin = nullptr; });
    addGroupWin->show();
    // 新增：点击创建后立即关闭查找窗口
    this->close();
}
