#include "addfriend.h"
#include "ui_addfriend.h"
#include <QGraphicsDropShadowEffect>

#include "addgroup.h"

AddFriend::AddFriend(SelfInfo _info,TcpClient* fd,QWidget *parent, const QString& defaultText) :
     QWidget(parent),
    ui(new Ui::AddFriend)
{
    ui->setupUi(this);
    Init();
     t=fd;
     info = _info;
     m_type = false; // 默认查找好友，防止未初始化崩溃
     qDebug() << "AddFriend 构造，this=" << this << " t=" << t;
     bool ok = connect(t, &TcpClient::CallAddFriend, this, &AddFriend::CmdHandler);
     qDebug() << "CallAddFriend 信号连接结果:" << ok;
     qDebug() << info.name;
     qDebug() << info.account;
     qDebug() << info.sig;
     ui->lineEdit->setText(defaultText); // 设置B框内容
     connect(ui->radioButton_friend,&QRadioButton::toggled,this,&AddFriend::on_radioButton_toggled);

     connect(ui->pushButton_create, &QPushButton::clicked, this, &AddFriend::on_pushButton_create_clicked);
    // 新增：设置关闭时自动销毁
    this->setAttribute(Qt::WA_DeleteOnClose, true);
}

AddFriend::~AddFriend()
{
    qDebug() << "AddFriend 析构，this=" << this;
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
    qDebug() << "on_pushButton_search_clicked called";
    if (!ui) {
        qDebug() << "ui 未初始化";
        return;
    }
    if (!ui->lineEdit) {
        qDebug() << "lineEdit 未初始化";
        return;
    }
    QString search = ui->lineEdit->text();
    qDebug() << "search text:" << search;
    if (!t) {
        qDebug() << "TcpClient t 未初始化";
        return;
    }
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
        // 立即弹窗
        QMessageBox::information(this, "提示", "添加请求已发出，请等待对方验证！");
    }
}

void AddFriend::on_radioButton_toggled(bool isChecked)
{
    m_type = !isChecked;
}

void AddFriend::CmdHandler(json msg)
{
    qDebug() << "AddFriend::CmdHandler 被调用, this=" << this << " msg=" << msg;
    qDebug() << "=== CmdHandler Start ===";
    int cmd = msg["cmd"].toInt();
    if(msg.isEmpty()) {
        qDebug() << "Empty message received, returning";
        return;
    }

    qDebug() << "Processing cmd =" << cmd;
    qDebug() << "Full message content:" << msg;

    if(cmd == cmd_friend_search || cmd == cmd_group_search)
    {
        qDebug() << "=== Search Response Processing ===";
        list.clear();
        ui->listWidget->clear();
        qDebug() << "List and listWidget cleared";
        
        QJsonArray arr = msg["msglist"].toArray();
        int count = msg["count"].toInt();
        qDebug() << "msglist array size:" << arr.size() << ", count field:" << count;
        
        try {
            for(int i = 0; i < count; i++)
            {
                qDebug() << "Processing item" << i << "of" << count;
                QJsonObject obj = arr[i].toObject();
                qDebug() << "Item" << i << "content:" << obj;
                
                QString account = obj.value("account").toString();
                QString name = obj["name"].toString();
                qDebug() << "Extracted account:" << account << "name:" << name;
                
                list.push_back(account);
                list.push_back(name);
                qDebug() << "Item" << i << "added to list";
            }
            
            qDebug() << "Final list size:" << list.size();
            for(int i = 0; i < list.size()-1; i += 2)
            {
                qDebug() << "Adding to listWidget - index:" << i;
                qDebug() << "Account:" << list[i] << "Name:" << list[i+1];
                QString itemText = QString("[%1] [%2]").arg(list[i], list[i+1]);
                qDebug() << "Item text:" << itemText;
                ui->listWidget->addItem(itemText);
                qDebug() << "Item added to listWidget successfully";
            }
        } catch (const std::exception& e) {
            qDebug() << "Exception caught:" << e.what();
        } catch (...) {
            qDebug() << "Unknown exception caught";
        }
        qDebug() << "=== Search Response Processing Complete ===";
    }

    if (cmd == cmd_group_create) {
        qDebug() << "=== Processing Group Create Response ===";
        QString res = msg["res"].toString();
        qDebug() << "Group create response:" << res;
        if (res == "yes") {
            QMessageBox::information(this, "提示", "群聊创建成功！");
            this->hide();
            this->deleteLater();
        }
        qDebug() << "=== Group Create Response Processing Complete ===";
    }

    if (cmd == cmd_add_friend_response) {
        qDebug() << "=== Processing Add Friend Response ===";
        QString res = msg["res"].toString();
        qDebug() << "Add friend response:" << res;
        if (res == "yes") {
            QMessageBox::information(this, "提示", "添加好友成功！");
            this->close();
        } else if (res == "offline") {
            QMessageBox::warning(this, "提示", "对方不在线，发送失败！");
        }
        qDebug() << "=== Add Friend Response Processing Complete ===";
    }
    
    qDebug() << "=== CmdHandler End ===";
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
