#include "verificationitem.h"
#include "ui_verificationitem.h"
#include <QDebug>

VerificationItem::VerificationItem(VerifyInfo _info,TcpClient* _socket, int _type,QWidget *parent) :
    QWidget(parent),ui(new Ui::VerificationItem),info(_info),socket(_socket)
{
    type = _type;
    ui->setupUi(this);
    ui->label_name->setText(info.name);
    if (type == 1) {
        ui->label_name_msg->setText(QString("申请加入：%1（%2）").arg(info.groupName).arg(info.account));
    } else {
    ui->label_name_msg->setText(info.msg);
    }
    ui->label_icon->SetIcon(info.icon);
    connect(ui->comboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &VerificationItem::on_comboBox_currentIndexChanged);
}

VerificationItem::~VerificationItem()
{
    delete ui;
}

void VerificationItem::on_comboBox_currentIndexChanged(int index)
{
    QString text = ui->comboBox->itemText(index);
    qDebug() << "comboBox changed, currentIndex:" << index << ", text:" << text;
    ui->pushButton->setText(text);
    qDebug() << "pushButton text after sync:" << ui->pushButton->text();
}

void VerificationItem::on_pushButton_clicked()
{
    qDebug() << "pushButton clicked, text:" << ui->pushButton->text() << ", comboBox currentIndex:" << ui->comboBox->currentIndex() << ", comboBox text:" << ui->comboBox->currentText();
    json msg = {{"cmd",     cmd_add_friend_response},
                {"name",    info.name},
                {"msg",     info.msg,},
                {"account", info.account},
                {"sender",  info.sender},
                {"reply",   "yes"}};
    if (type)
    {
        msg["cmd"] = cmd_group_join_response;
        msg["groupName"] = info.groupName;
    }
    if(ui->comboBox->currentIndex())
    {
        ui->pushButton->setText("已拒绝");
        msg["reply"] = "no";
    }
    else
        ui->pushButton->setText("已同意");
    ui->pushButton->setEnabled(false);
    socket->SendMsg(msg);
}
