#include "addgroup.h"
#include "ui_addgroup.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

AddGroup::AddGroup(SelfInfo selfInfo, TcpClient* tcp, QWidget *parent)
    : QWidget(parent), selfInfo(selfInfo), tcp(tcp),
    ui(new Ui::addgroup)
{
    ui->setupUi(this);

    // 调试输出，确认控件都不是nullptr
    qDebug() << "lineEdit:" << ui->lineEdit;
    qDebug() << "listWidget:" << ui->listWidget;
    qDebug() << "pushButton_create:" << ui->pushButton_create;
    qDebug() << "pushButton_cancel:" << ui->pushButton_cancel;
    qDebug() << "textEdit:" << ui->textEdit;

    ui->listWidget->setSelectionMode(QAbstractItemView::MultiSelection);

    // 连接信号槽
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &AddGroup::onInputChanged);
    connect(ui->listWidget, &QListWidget::itemSelectionChanged, this, &AddGroup::onInputChanged);
    connect(ui->pushButton_create, &QPushButton::clicked, this, &AddGroup::onCreateClicked);
    connect(ui->pushButton_cancel, &QPushButton::clicked, this, &QWidget::close);

    // 连接 TcpClient 信号
    connect(tcp, &TcpClient::CallClient, this, &AddGroup::onFriendListReceived);

    updateCreateButtonState();

    // 请求好友列表
    requestFriendList();
}

AddGroup::~AddGroup()
{
    delete ui;
}

void AddGroup::requestFriendList()
{
    QJsonObject msg;
    msg["cmd"] = cmd_friend_list;
    msg["account"] = selfInfo.account;
    tcp->SendMsg(msg);
}

void AddGroup::onFriendListReceived(json msg)
{
    qDebug() << "onFriendListReceived called, msg:" << msg;

    // 只处理好友列表返回
    if (msg["cmd"].toInt() != cmd_friend_list) return;

    ui->listWidget->clear();
    QJsonArray arr = msg["msglist"].toArray();
    qDebug() << "friends array size:" << arr.size();
    for (const auto& item : arr) {
        QString name = item.toObject().value("name").toString();
        int account = item.toObject().value("account").toInt();
         qDebug() << "friend:" << name << account;
        QListWidgetItem* listItem = new QListWidgetItem(name, ui->listWidget);
        listItem->setData(Qt::UserRole, account);
    }
    updateCreateButtonState();
}

void AddGroup::onInputChanged()
{
    updateCreateButtonState();
}

void AddGroup::updateCreateButtonState()
{
    bool hasName = !ui->lineEdit->text().trimmed().isEmpty();
    bool hasSelection = !ui->listWidget->selectedItems().isEmpty();
    ui->pushButton_create->setEnabled(hasName && hasSelection);
}

void AddGroup::onCreateClicked()
{
    QString groupName = ui->lineEdit->text().trimmed();
    QList<QListWidgetItem*> selected = ui->listWidget->selectedItems();
    if (groupName.isEmpty() || selected.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入群聊名称并选择至少一个好友！");
        return;
    }

    // 构造成员列表
    QJsonArray members;
    for (auto* item : selected) {
        members.append(item->data(Qt::UserRole).toInt());
    }
    // 也可以把自己加进去
    members.append(selfInfo.account);

    // 构造消息
    QJsonObject msg;
    msg["cmd"] = cmd_group_create;
    msg["account"] = selfInfo.account;
    msg["groupName"] = groupName;
    msg["members"] = members;

    tcp->SendMsg(msg);

    QMessageBox::information(this, "提示", "群聊创建请求已发送！");
    this->close();
}
