#include "client.h" // 主窗口类头文件，定义了聊天主界面
#include "ui_client.h" // Qt UI自动生成头文件
#include <QGraphicsDropShadowEffect> // 阴影效果类
#include <QGuiApplication> // Qt应用程序相关
#include <QScreen> // 屏幕信息
#include <QMouseEvent> // 鼠标事件
#include <QDebug> // 调试输出
#include "addfriend.h" // 添加好友窗口
#include "frienditem.h" // 好友项控件
#include <QListWidget> // 列表控件
#include <QToolTip> // 工具提示
#include "stringtool.h" // 字符串工具类
#include <QShortcut> // 快捷键
#include <QTextBlock> // 文本块
#include <QFileDialog> // 文件对话框
#include "sendtextedit.h" // 自定义文本编辑器
#include "verificationitem.h" // 验证消息项
#include "IconSetting/iconselect.h" // 头像选择窗口
#include <QTimer> // 定时器
#include <QSizePolicy> // 尺寸策略
#include <QPushButton> // 添加 QPushButton 头文件
#include <QMessageBox> // 添加 QMessageBox 头文件
#include <QApplication>
#include <QRubberBand>
#include <QPainter>
#include <QClipboard>
#include <QBuffer>
#include "screenshotwidget.h"

// 构造函数，初始化主界面和各个控件
Client::Client(SelfInfo info ,TcpClient* tcp,QWidget *parent)
    : QWidget(parent), ui(new Ui::Client),selfInfo(info),t(tcp)
{
    ui->setupUi(this); // 设置UI界面
    InitUI(); // 初始化界面外观
    InitLayout(); // 初始化布局
    systemMsg = new SystemMessage(); // 系统消息窗口
    ui->label_icon->SetIcon(info.icon); // 设置头像
    messagesListWidget = new ChatListWidget(ItemType_Message); // 消息列表
    friendsListWidget = new ChatListWidget(ItemType_Friend); // 好友列表
    groupsListWidget = new ChatListWidget(ItemType_Group); // 群组列表
    m_emojiSelector = new EmojiSelector(); // 表情选择器
    m_emojiSelector->adjustSize();

    // 连接表情选择信号
    connect(m_emojiSelector, &EmojiSelector::emojiSelected, this, &Client::insertEmoji);
    // 连接TCP消息处理
    connect(t,&TcpClient::CallClient,this,&Client::ClientMsgHandler);
    // 发送消息快捷键
    connect(ui->textEdit_send,&SendTextEdit::keyPressEnter,this,&Client::on_pushBtn_send_clicked);
    // 好友列表双击
    connect(friendsListWidget,&ChatListWidget::itemDoubleClicked,this,&Client::on_listWidget_info_itemClicked);
    // 消息列表双击
    connect(messagesListWidget,&ChatListWidget::itemDoubleClicked,this,[&](QListWidgetItem *item){
        FriendItem* friendItem = qobject_cast<FriendItem*>(messagesListWidget->itemWidget(item));
        SetChatWindow(friendItem);
    });
    // 群组列表双击
    connect(groupsListWidget,&ChatListWidget::itemDoubleClicked,this,&Client::on_groupsListWidget_itemClicked);
    ui->pushBtn_refresh->setVisible(false); // 隐藏刷新按钮
    ui->stackedWidget_list->addWidget(messagesListWidget);
    ui->stackedWidget_list->addWidget(friendsListWidget);
    ui->stackedWidget_list->addWidget(groupsListWidget);
    RefreshFriendList(); // 刷新好友列表
    RefreshGroupList(); // 刷新群组列表
}

// 析构函数，释放UI资源
Client::~Client()
{
    delete ui;
}

// 发送请求刷新好友列表
void Client::RefreshFriendList()
{
    json msg;
    msg.insert("cmd",cmd_friend_list);
    msg.insert("account",selfInfo.account);
    t->SendMsg(msg);
}

// 发送请求刷新群组列表
void Client::RefreshGroupList()
{
    json msg;
    msg.insert("cmd",cmd_group_list);
    msg.insert("account",selfInfo.account);
    t->SendMsg(msg);
}

// 初始化界面外观
void Client::InitUI()
{
    this->setWindowTitle("WeChat"); // 设置窗口标题
    this->setWindowFlags(Qt::Window); // 使用标准系统窗口
    this->setMinimumSize(800, 600); // 设置最小尺寸

    // 创建阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0); // 阴影偏移
    shadow->setColor(QColor(39,40,43,100)); // 阴影颜色
    shadow->setBlurRadius(10); // 阴影模糊半径
    ui->centerWidget->setGraphicsEffect(shadow); // 应用阴影
    m_isFullScreen = false; // 全屏标志

    // ----------- 补充自适应布局代码 -----------
    ui->centerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->widget_side->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->widget_list->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->widget_chatting->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    if (!ui->centerWidget->layout()) {
        ui->centerWidget->setLayout(new QVBoxLayout);
    }
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

// 初始化主界面布局
void Client::InitLayout()
{
    QString style = QString("QSplitter {border: 1px solid grey}");

    mainSplitter = new QSplitter(Qt::Horizontal);
    mainSplitter->setStyleSheet(style);
    mainSplitter->setHandleWidth(5);

    // 添加子控件到 mainSplitter
    mainSplitter->addWidget(ui->widget_side);
    mainSplitter->addWidget(ui->widget_list);

    // 聊天区
    chatSplitter = new QSplitter(Qt::Vertical);
    chatSplitter->setHandleWidth(5);
    chatSplitter->addWidget(ui->widget_2);
    chatSplitter->addWidget(ui->widget_chatWindow);
    chatSplitter->addWidget(ui->widget_3);

    mainSplitter->addWidget(chatSplitter);

    // 清空旧布局并设置新的布局
    QLayout* oldLayout = ui->centerWidget->layout();
    if (oldLayout) {
        QLayoutItem* item;
        while ((item = oldLayout->takeAt(0)) != nullptr) {
            delete item;
        }
        delete oldLayout;
    }

    QVBoxLayout* layout = new QVBoxLayout(ui->centerWidget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(mainSplitter);

    // 设置扩展策略
    mainSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    chatSplitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->widget_side->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->widget_list->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    ui->widget_chatting->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}


// // 鼠标按下事件，记录鼠标相对窗口左上角的位置
// void Client::mousePressEvent(QMouseEvent *event)
// {
//     mouseWindowTopLeft = event->pos();
// }

// // 鼠标移动事件，实现窗口拖动
// void Client::mouseMoveEvent(QMouseEvent *event)
// {
//     if (event->buttons() & Qt::LeftButton)
//     {
//         mouseDeskTopLeft = event->globalPosition().toPoint();
//         windowDeskTopLeft = mouseDeskTopLeft - mouseWindowTopLeft;  // 计算新位置
//         this->move(windowDeskTopLeft);     // 移动窗口
//     }
// }

// // 处理窗口大小变化
// void Client::resizeEvent(QResizeEvent *event)
// {
//     QWidget::resizeEvent(event);

//     // 更新布局
//     if (mainSplitter && chatSplitter) {
//         QList<int> mainSizes = mainSplitter->sizes();
//         int totalWidth = mainSizes[0] + mainSizes[1] + mainSizes[2];
//         if (totalWidth > 0) {
//             // 保持比例
//             int sideWidth = mainSizes[0] * width() / totalWidth;
//             int listWidth = mainSizes[1] * width() / totalWidth;
//             int chatWidth = width() - sideWidth - listWidth;

//             mainSplitter->setSizes(QList<int>() << sideWidth << listWidth << chatWidth);
//         }
//     }
// }

// 添加窗口状态改变事件处理
void Client::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange) {
        if (windowState() & Qt::WindowMaximized) {
            m_isFullScreen = true;
            // 延迟处理布局更新
            QTimer::singleShot(100, this, [this]() {
                QList<int> mainSizes = mainSplitter->sizes();
                int totalWidth = mainSizes[0] + mainSizes[1] + mainSizes[2];
                if (totalWidth > 0) {
                    mainSplitter->setSizes(QList<int>() <<
                                           (mainSizes[0] * width() / totalWidth) <<
                                           (mainSizes[1] * width() / totalWidth) <<
                                           (mainSizes[2] * width() / totalWidth));
                }
            });
        } else {
            m_isFullScreen = false;
            // 延迟处理布局更新
            QTimer::singleShot(100, this, [this]() {
                mainSplitter->setSizes(QList<int>() << ui->widget_side->width() << ui->widget_list->width() << ui->widget_chatting->width());
                chatSplitter->setSizes(QList<int>() << ui->widget_2->height() << 400 << ui->widget_4->height() << 100 << ui->widget_3->height());
            });
        }
    }
    QWidget::changeEvent(event);
}

// //鼠标双击事件，切换全屏/还原
// void Client::mouseDoubleClickEvent(QMouseEvent *event)
// {
//     Q_UNUSED(event)
//     //on_pushBtn_max_clicked();
// }

// // 最大化/还原按钮槽函数
// void Client::on_pushBtn_max_clicked()
// {
//     if (isMaximized()) {
//         showNormal();
//     } else {
//         showMaximized();
//     }
// }

// // 关闭按钮槽函数，发送登出命令并关闭窗口
// void Client::on_pushBtn_close_clicked()
// {
//     json msg ={ {"cmd",cmd_logout}};
//     t->SendMsg(msg);
//     this->close();
// }

// // 最小化按钮槽函数
// void Client::on_pushBtn_hide_clicked()
// {
//     QWidget* pWindow = this->window();
//     if(pWindow->isWindow())
//         pWindow->showMinimized();
// }

// 添加好友按钮槽函数，弹出添加好友窗口
void Client::on_pushButton_addFriend_clicked()
{
    QString text = ui->lineEdit->text(); // 获取A框内容
    AddFriend *add = new AddFriend(selfInfo, t, nullptr, text);
    add->show();
}

// 刷新按钮槽函数，根据当前列表刷新好友或群组
void Client::on_pushBtn_refresh_clicked()
{
    switch(curListWidgetIndex) {
    case 0:break;
    case 1:RefreshFriendList();break;
    case 2:RefreshGroupList();break;
    default:
        break;
    }
}

// 处理服务器返回的各种消息
void Client::ClientMsgHandler(json msg)
{
    qDebug() << "ClientMsgHandler received:" << msg;
    int cmd = msg["cmd"].toInt();
    switch(cmd) {
    case cmd_add_friend_request:
    {
        VerifyInfo vinfo;
        vinfo.account = selfInfo.account;
        vinfo.name = msg["name"].toString();
        vinfo.msg = msg["sendmsg"].toString();
        vinfo.sender = msg["sender"].toInt();
        vinfo.icon = msg["icon"].toString();
        VerificationItem *item = new VerificationItem(vinfo,t);
        systemMsg->AddItem(item);
        break;
    }
    case cmd_add_friend_response:
    {
        QString res = msg["res"].toString();
        if(res == "yes")
            RefreshFriendList();
        t->CallAddFriend(msg);
        break;
    }
    case cmd_friend_list: {
        friendsListWidget->clear();
        friendMap.clear();
        friendItemMap.clear();
        QJsonArray list = msg["msglist"].toArray();
        for (int i = 0; i < list.size(); i++) {
            FriendInfo info;
            json obj = list[i].toObject();
            info.name = obj["name"].toString();
            info.account = obj["account"].toInt();
            info.sig = obj["sig"].toString();
            info.isOnline = obj["online"].toBool();
            info.icon = obj["icon"].toString();
            if (info.sig.isEmpty())
                info.sig = "这家伙很高冷，啥也不想说";
            FriendItem *item = new FriendItem(info);
            QListWidgetItem *listItem = new QListWidgetItem(friendsListWidget);
            listItem->setSizeHint(QSize(260, 85));
            friendsListWidget->addItem(listItem);
            friendsListWidget->setItemWidget(listItem, item);
            friendMap.insert(item->account(), info);
            friendItemMap.insert(info.account, item);
        }
        break;
    }
    case cmd_friend_chat: {
        int sender = msg["sender"].toInt();
        QString content = msg["msg"].toString();
        if (sender == 10000) {
            QMessageBox::information(this, "系统消息", content);
            return;
        }
        int account = msg["account"].toInt();
        QString friendKey = QString("f_%1").arg(account);
        FriendItem *item = nullptr;
        ChatWindow *chatWindow;
        if (chatMap.find(account) == chatMap.end())  //账号对应的聊天窗口不存在
        {
            if (friendMap.find(account) != friendMap.end()) {
                FriendInfo info = friendMap[account];
                chatWindow = new ChatWindow(info);

                ui->stackedWidget->addWidget(chatWindow);
                chatMap.insert(account, chatWindow);
            } else {
                //单向好友
                return;
            }
        } else {
            chatWindow = chatMap.value(account);
            // ui->stackedWidget->setCurrentWidget(chatMap.value(account));
        }

        if(messageItemMap.find(friendKey) == messageItemMap.end())//消息列表中没有该好友
        {
            FriendInfo info = friendMap[account];
            item = new FriendItem(info);
            QListWidgetItem *listItem = new QListWidgetItem(messagesListWidget);
            listItem->setSizeHint(QSize(260, 85));
            messagesListWidget->addItem(listItem);
            messagesListWidget->setItemWidget(listItem, item);
            messageItemMap.insert(friendKey, item);
        }
        else
        {
            item = messageItemMap.value(friendKey);
        }
        QString pushMsg = StringTool::MergeSendTimeMsg(currentDateTime, 1, "");
        chatWindow->pushMsg(pushMsg, 1);
        //push msg on chat window
        ContentType type = (ContentType)msg["type"].toInt();
        switch (type) {
        case ContentType::TextOnly: {
            chatWindow->sendMessage(msg["content"].toString(), 1);
            item->SetLastMsg(msg["content"].toString());
            break;
        }
        case ContentType::ImageOnly: {
            QString sendImage = msg["content"].toString();
            chatWindow->sendImages(StringTool::GetImagesFromHtml(sendImage), 1);
            item->SetLastMsg("[图片]");
            break;
        }
        case ContentType::MixedContent: {
            QString content = msg["content"].toString();
            chatWindow->sendContentFromInput(content, 1);
            item->SetLastMsg("[自定义消息]");
            break;
        }
        default:
            break;

        }
        if (account != curChatAccount)
            item->NewMsgPlusOne();
        else if(curChatType != 0)
            item->NewMsgPlusOne();
        break;
    }
    case cmd_group_join_request:
    {
        VerifyInfo vinfo;
        vinfo.name = msg["name"].toString();
        vinfo.msg = msg["msg"].toString();
        vinfo.sender = msg["sender"].toInt();
        vinfo.account = msg["groupAccount"].toInt();
        vinfo.groupName = msg["groupName"].toString();
        vinfo.icon = msg["icon"].toString();
        VerificationItem *item = new VerificationItem(vinfo,t,1);
        QString msg1 = "用户" + vinfo.name + "请求加入群" + vinfo.groupName + QString::number(vinfo.account);
        systemMsg->AddItem(item);

        break;
    }
    case cmd_group_join_response:
    {
        QString res = msg["res"].toString();
        QString info;
        if(res == "yes")
        {
            info = "群聊申请已通过";
            RefreshGroupList();
        }
        else
            info = "群聊申请被拒绝";
        break;
    }
    case cmd_group_list:{
        groupsListWidget->clear();
        groupItemMap.clear();
        QJsonArray list = msg["msglist"].toArray();
        for (int i = 0; i < list.size(); i++) {
            GroupInfo info;
            json obj = list[i].toObject();
            info.groupName= obj["name"].toString();
            info.groupAccount = obj["account"].toInt();

            FriendItem *item = new FriendItem(info);

            QListWidgetItem *listItem = new QListWidgetItem(groupsListWidget);
            listItem->setSizeHint(QSize(260, 85));
            groupsListWidget->addItem(listItem);
            groupsListWidget->setItemWidget(listItem, item);

            groupItemMap.insert(item->account(), item);
            groupMap.insert(info.groupAccount, info);
            json msg1 = {{"cmd",      cmd_group_member_list},
                         {"groupAccount", info.groupAccount}};
            t->SendMsg(msg1);
        }
        break;
    }
    case cmd_group_chat: {
        int sender = msg["sender"].toInt();
        int groupAccount = msg["account"].toInt();
        QString groupKey = QString("g_%1").arg(groupAccount);
        FriendItem *item;
        QString senderName;
        for(auto it:groupMap[groupAccount].memberList)
        {
            if(it.account == sender)
            {
                senderName = it.name;
                break;
            }
        }

        ChatWindow *chatWindow;
        if (groupChatMap.find(groupAccount) == groupChatMap.end())  //群聊账号对应的聊天窗口不存在
        {
            GroupInfo info = groupItemMap[groupAccount]->GetGroupInfo();
            chatWindow = new ChatWindow(info);

            ui->stackedWidget->addWidget(chatWindow);
            groupChatMap.insert(groupAccount, chatWindow);

        } else {
            chatWindow = groupChatMap.value(groupAccount);
            // ui->stackedWidget->setCurrentWidget(chatMap.value(account));
        }
        if(messageItemMap.find(groupKey) == messageItemMap.end())//消息列表中没有该群聊
        {
            GroupInfo info = groupMap[groupAccount];
            item = new FriendItem(info);
            QListWidgetItem *listItem = new QListWidgetItem(messagesListWidget);
            listItem->setSizeHint(QSize(260, 85));
            messagesListWidget->addItem(listItem);
            messagesListWidget->setItemWidget(listItem, item);
            messageItemMap.insert(groupKey, item);
        }
        else
        {
            item = messageItemMap.value(groupKey);
        }
        ContentType type = (ContentType)msg["type"].toInt();
        switch (type) {
        case ContentType::TextOnly: {
            QString content = msg["content"].toString();
            QString pushMsg = StringTool::MergeSendTimeMsg(currentDateTime, 1, "");
            chatWindow->pushMsg(pushMsg, 1);
            chatWindow->sendMessage(content, 1);
            item->SetLastMsg(content);
            break;
        }
        case ContentType::ImageOnly: {
            QString sendImage = msg["content"].toString();
            QString pushMsg = StringTool::MergeSendTimeMsg(currentDateTime, 1, "");
            chatWindow->pushMsg(pushMsg, 1);
            chatWindow->sendImages(StringTool::GetImagesFromHtml(sendImage), 0);
            item->SetLastMsg("[图片]");
            break;
        }
        case ContentType::MixedContent: {
            QString content = msg["content"].toString();
            //QList<QPair<QString, QImage>> contentList = StringTool::extractContent(content);
            QString pushMsg = StringTool::MergeSendTimeMsg(currentDateTime, 1, "");
            chatWindow->pushMsg(pushMsg, 1);
            //chatWindow->sendMixedContent(contentList, 1);
            chatWindow->sendContentFromInput(content, 1);
            item->SetLastMsg("[自定义消息]");
            break;
        }
        default:
            break;
        }
        if (groupAccount != curChatAccount) {
            item->NewMsgPlusOne();
        } else {
            if (curChatType != 1)
                item->NewMsgPlusOne();
        }
        break;
    }
    case cmd_group_member_list:{
        int groupAccount = msg["groupAccount"].toInt();
        if(groupMap.find(groupAccount) == groupMap.end())
            return;
        QJsonArray list = msg["msglist"].toArray();
        for (int i = 0; i < list.size(); i++) {
            MemberInfo info;
            json obj = list[i].toObject();
            info.account = obj["account"].toString().toInt();
            info.name = obj["name"].toString();
            groupMap[groupAccount].memberList.push_back(info);
        }
        break;
    }
    case cmd_file_transfer: {
        QString fileName = msg["file_name"].toString();
        QString fileData = msg["file_data"].toString();
        int sender_id = msg["sender"].toInt();
        if (msg.contains("is_group") && msg["is_group"].toInt() == 1) {
            int group_id = msg["account"].toInt();
            ChatWindow* chatWindow = groupChatMap.value(group_id, nullptr);
            if (!chatWindow) break;
            chatWindow->addFileMessage(fileName, fileData, false);
        } else {
            ChatWindow* chatWindow = chatMap.value(sender_id, nullptr);
            if (!chatWindow) {
                if (friendMap.contains(sender_id)) {
                    chatWindow = new ChatWindow(friendMap[sender_id]);
                    ui->stackedWidget->addWidget(chatWindow);
                    chatMap.insert(sender_id, chatWindow);
                } else {
                    break;
                }
            }
            chatWindow->addFileMessage(fileName, fileData, false);
        }
        break;
    }
    case cmd_get_history: {
        qDebug() << "收到历史消息:" << msg;
        int type = msg["type"].toInt();
        QJsonArray history = msg["history"].toArray();
        if (type == 0) { // 私聊
            if(history.isEmpty()) break;
            int peer_id = -1;
            // 取第一条消息的对方id
            QJsonObject firstMsg = history.first().toObject();
            int sender_id = firstMsg["sender_id"].toInt();
            int receiver_id = firstMsg["receiver_id"].toInt();
            peer_id = (sender_id == selfInfo.account) ? receiver_id : sender_id;
            if (peer_id == -1) break;
            ChatWindow* chatWindow = chatMap.value(peer_id, nullptr);
            qDebug() << "peer_id:" << peer_id << "chatWindow:" << chatWindow;
            if (!chatWindow) break;
            for (const QJsonValue& v : history) {
                QJsonObject m = v.toObject();
                int sender_id = m["sender_id"].toInt();
            QString content = m["content"].toString();
                int msg_type = m["msg_type"].toInt();
                QString send_time = m["send_time"].toString();
                chatWindow->pushMsg(send_time, sender_id == selfInfo.account ? 0 : 1);
                if (msg_type == TextOnly) {
                    chatWindow->sendMessage(content, sender_id == selfInfo.account ? 0 : 1);
                } else if (msg_type == ImageOnly) {
                    chatWindow->sendImages(StringTool::GetImagesFromHtml(content), sender_id == selfInfo.account ? 0 : 1);
                } else if (msg_type == MixedContent) {
                    chatWindow->sendContentFromInput(content, sender_id == selfInfo.account ? 0 : 1);
        }
            }
        } else if (type == 1) { // 群聊
            int group_id = msg["group_id"].toInt();
            qDebug() << "[历史消息响应] group_id=" << group_id;
            ChatWindow* chatWindow = groupChatMap.value(group_id, nullptr);
            qDebug() << "[历史消息] groupChatMap group_id=" << group_id << "窗口指针:" << chatWindow;
            if (!chatWindow) break;
            for (const QJsonValue& v : history) {
                QJsonObject m = v.toObject();
                int sender_id = m["sender_id"].toInt();
                QString content = m["content"].toString();
                int msg_type = m["msg_type"].toInt();
                QString send_time = m["send_time"].toString();
                // 查找 sender_id 对应的名字
                QString senderName;
                for (const MemberInfo& member : groupMap[group_id].memberList) {
                    if (member.account == sender_id) {
                        senderName = member.name;
        break;
    }
                }
                if (senderName.isEmpty()) senderName = QString::number(sender_id);
                // 在 pushMsg 里加上名字
                QString msgWithName = senderName + ": " + send_time;
                chatWindow->pushMsg(msgWithName, sender_id == selfInfo.account ? 0 : 1);
                if (msg_type == TextOnly) {
                    chatWindow->sendMessage(content, sender_id == selfInfo.account ? 0 : 1);
                } else if (msg_type == ImageOnly) {
                    chatWindow->sendImages(StringTool::GetImagesFromHtml(content), sender_id == selfInfo.account ? 0 : 1);
                } else if (msg_type == MixedContent) {
                    chatWindow->sendContentFromInput(content, sender_id == selfInfo.account ? 0 : 1);
                }
            }
        }
        break;
    }
    case cmd_group_create:
    {
        QString res = msg["res"].toString();
        if(res == "yes") {
            QMessageBox::information(this, "提示", "群聊创建成功！");
            RefreshGroupList();
        } else {
            QString err = msg["err"].toString();
            QMessageBox::warning(this, "错误", "群聊创建失败：" + err);
        }
        break;
    }
    default:
        break;
    }
}

void Client::on_listWidget_info_itemClicked(QListWidgetItem *item)
{
    FriendItem* friendItem = qobject_cast<FriendItem*>(friendsListWidget->itemWidget(item));
    SetChatWindow(friendItem);
    int account = friendItem->account();
    QString friendKey = QString("f_%1").arg(account);
    if(messageItemMap.find(friendKey) == messageItemMap.end())
    {
        FriendItem *msgItem = new FriendItem(friendItem->GetFriendInfo());
        QListWidgetItem *listItem = new QListWidgetItem(messagesListWidget);
        listItem->setSizeHint(QSize(260, 85));
        friendsListWidget->addItem(listItem);
        friendsListWidget->setItemWidget(listItem, msgItem);

        messagesListWidget->addItem(listItem);
        messagesListWidget->setItemWidget(listItem, msgItem);

        messageItemMap.insert(friendKey, msgItem);
    }
}
void Client::on_groupsListWidget_itemClicked(QListWidgetItem *item)
{
    FriendItem* friendItem = qobject_cast<FriendItem*>(groupsListWidget->itemWidget(item));
    int account = friendItem->account();
    qDebug() << "[群聊点击] account=" << account;
    SetChatWindow(friendItem);
    QString groupKey = QString("g_%1").arg(account);
    if(messageItemMap.find(groupKey) == messageItemMap.end())
    {
        FriendItem *msgItem = new FriendItem(friendItem->GetGroupInfo());
        QListWidgetItem *listItem = new QListWidgetItem(messagesListWidget);
        listItem->setSizeHint(QSize(260, 85));
        groupsListWidget->addItem(listItem);
        groupsListWidget->setItemWidget(listItem, msgItem);

        messagesListWidget->addItem(listItem);
        messagesListWidget->setItemWidget(listItem, msgItem);

        messageItemMap.insert(groupKey, msgItem);
    }
    // 新增：点击时请求群聊历史消息
    json msg;
    msg["cmd"] = cmd_get_history;
    msg["type"] = 1;
    msg["group_id"] = account;
    qDebug() << "[群聊历史请求] group_id=" << account;
    t->SendMsg(msg);
}

void Client::on_pushBtn_send_clicked()
{
    ContentType type = CheckContentType(ui->textEdit_send);
    if(ui->stackedWidget->currentIndex() == 0)
    {
        QToolTip::showText(ui->pushBtn_send->mapToGlobal(QPoint(0, -50)), "选择的好友不能为空", ui->pushButton);
        return;
    }

    ChatWindow* chatWindow = qobject_cast<ChatWindow*>(ui->stackedWidget->currentWidget());
    int account = chatWindow->GetAccount();

    // 只显示时间，不显示用户名
    QString pushMsg = StringTool::MergeSendTimeMsg(currentDateTime, 0, "");
    json msg = {
        {"cmd", chatWindow->GetType() ? cmd_group_chat : cmd_friend_chat},
        {"account", account},
        {"sender", selfInfo.account},
        {"type", type},
        {"timestamp", currentDateTime.toString("yyyy-MM-dd hh:mm:ss")}
    };
    QString friendKey;
    if(curChatType == 1)
    {
        friendKey = QString("f_%1").arg(curChatAccount);
    }
    else if (curChatType == 2)
    {
        friendKey = QString("g_%1").arg(curChatAccount);
    }
    FriendItem *item = messageItemMap.value(friendKey);

    switch (type) {
    case TextOnly: {
        QString sendText = ui->textEdit_send->toPlainText();
        if(sendText.isEmpty())
        {
            QToolTip::showText(ui->pushBtn_send->mapToGlobal(QPoint(0, -50)), "发送的消息不能为空", ui->pushButton);
            return;
        }
        msg["content"] = (sendText );
        chatWindow->pushMsg(pushMsg, 0);
        chatWindow->sendMessage(msg["content"].toString(), 0);
        item->SetLastMsg(sendText);
        break;
    }
    case ImageOnly:
    {
        QString sendImage = ui->textEdit_send->toHtml();
        msg["content"] = sendImage;
        chatWindow->pushMsg(pushMsg, 0);
        chatWindow->sendImages(StringTool::GetImagesFromHtml(sendImage), 0);
        item->SetLastMsg("[图片]");
        break;
    }
    case MixedContent: {
        QString html = ui->textEdit_send->toHtml();
        chatWindow->pushMsg(pushMsg, 0);
        chatWindow->sendContentFromInput(html, 0);
        msg["content"] = html;
        item->SetLastMsg("[自定义消息]");
        break;
    }

    }
    ui->textEdit_send->clear();
    t->SendMsg(msg);
}


void Client::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        on_pushBtn_send_clicked();
    }
}

void Client::on_pushButton_msg_list_clicked()
{
    if(curListWidgetIndex == 0)
    {
        ui->pushButton_msg_list->setChecked(true);
        return;
    }
    else
    {
        ui->pushButton_friend_list->setChecked(false);
        ui->pushButton_group_list->setChecked(false);
    }
    curListWidgetIndex = 0;
    ui->stackedWidget_list->setCurrentWidget(messagesListWidget);
}

void Client::on_pushButton_friend_list_clicked()
{
    if(curListWidgetIndex == 1)
    {
        ui->pushButton_friend_list->setChecked(true);
        return;
    }
    else
    {
        ui->pushButton_msg_list->setChecked(false);
        ui->pushButton_group_list->setChecked(false);
    }
    curListWidgetIndex = 1;
    ui->stackedWidget_list->setCurrentWidget(friendsListWidget);
}

void Client::on_pushButton_group_list_clicked()
{
    if(curListWidgetIndex == 2)
    {
        ui->pushButton_group_list->setChecked(true);
        return;
    }
    else
    {
        ui->pushButton_msg_list->setChecked(false);
        ui->pushButton_friend_list->setChecked(false);
    }
    curListWidgetIndex = 2;
    ui->stackedWidget_list->setCurrentWidget(groupsListWidget);
}

void Client::SetChatWindow(FriendItem *item) {
    if(item == nullptr)
        return;
    int account = item->account();
    //Friend ChatWindow
    if(item->GetType() == 0) {
        if (chatMap.find(account) == chatMap.end())  //账号对应的聊天窗口不存在
        {
            FriendInfo info{account, item->getLabelName()};
            ChatWindow *chatWindow = new ChatWindow(info);
            ui->stackedWidget->addWidget(chatWindow);
            ui->stackedWidget->setCurrentWidget(chatWindow);
            chatMap.insert(account, chatWindow);
        } else {
            ui->stackedWidget->setCurrentWidget(chatMap.value(account));
        }
        curChatType = 1;
        // 自动拉取私聊历史
        json msg;
        msg["cmd"] = cmd_get_history;
        msg["type"] = 0;
        msg["user_id"] = selfInfo.account;
        msg["peer_id"] = account;
        t->SendMsg(msg);
    }
    else
    {
        if (groupChatMap.find(account) == groupChatMap.end())  //账号对应的聊天窗口不存在
        {
            GroupInfo info{account, item->getLabelName(),{}};
            ChatWindow *chatWindow = new ChatWindow(info);
            ui->stackedWidget->addWidget(chatWindow);
            ui->stackedWidget->setCurrentWidget(chatWindow);
            groupChatMap.insert(account, chatWindow);
        } else {
            ui->stackedWidget->setCurrentWidget(groupChatMap.value(account));
        }
        curChatType = 2;
        // 自动拉取群聊历史
        json msg;
        msg["cmd"] = cmd_get_history;
        msg["type"] = 1;
        msg["group_id"] = account;
        t->SendMsg(msg);
    }
    item->SetNewMsgNum(0);
    curChatAccount = account;
    ui->label_info->setText(item->GetChatName());
}

void Client::on_pushButton_system_msg_clicked()
{
    if(systemMsg->isHidden())
        systemMsg->show();
}

void Client::on_pushButton_icon_clicked()
{
    IconSelect *iconSelect = new IconSelect;
    iconSelect->show();

    connect(iconSelect, &IconSelect::SetIcon, this, [&](QString url){
        ui->label_icon->SetIcon(url);
        selfInfo.icon = url;
        json msg = {{"cmd",cmd_set_icon},{"account",selfInfo.account},{"icon",url}};
        t->SendMsg(msg);
    });
}

ContentType Client::CheckContentType(const QTextEdit *textEdit)
{
    bool hasText = false;
    bool hasImage = false;

    QTextDocument *doc = textEdit->document();
    for (QTextBlock block = doc->begin(); block != doc->end(); block = block.next()) {
        for (QTextBlock::iterator it = block.begin(); !it.atEnd(); ++it) {
            QTextFragment fragment = it.fragment();
            if (fragment.isValid()) {
                if (fragment.charFormat().isImageFormat()) {
                    hasImage = true;
                } else {
                    hasText = true;
                }

                if (hasText && hasImage) {
                    return MixedContent;
                }
            }
        }
    }
    if (hasText) {
        return TextOnly;
    } else if (hasImage) {
        return ImageOnly;
    } else {
        return TextOnly; // 如果输入框为空，我们可以认为它是文本类型
    }
}

void Client::on_pushButton_emoj_clicked()
{
    QPoint buttonPos = ui->pushButton_emoj->mapToGlobal(QPoint(0, 0));
    int x = buttonPos.x() + (ui->pushButton_emoj->width() / 2) - (m_emojiSelector->width() / 2);
    int y = buttonPos.y() - m_emojiSelector->height();
    m_emojiSelector->move(x, y-10);
    m_emojiSelector->show();
}

void Client::insertEmoji(const QString &emoji)
{
    ui->textEdit_send->insertPlainText(emoji);
}



void Client::on_pushButton_image_clicked()
{
    //open file select dialog
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("Images (*.png *.jpg)"));
    if(fileName.isEmpty())
        return;
    QImage image(fileName);
    if(image.isNull())
        return;

    // Convert image to QPixmap
    QPixmap pixmap = QPixmap::fromImage(image);

    // Save QPixmap as PNG and convert it to Base64
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    pixmap.save(&buffer, "PNG"); // write pixmap into bytes in PNG format
    buffer.close();
    QString base64Image = byteArray.toBase64().data();

    // Insert image into QTextEdit as HTML
    ui->textEdit_send->insertHtml("<img src='data:image/png;base64," + base64Image + "' />");
    ui->textEdit_send->setFocus();
}

void Client::on_pushButton_file_clicked()
{
    qDebug() << "on_pushButton_file_clicked called";
    QString filePath = QFileDialog::getOpenFileName(this, tr("选择要发送的文件"), "", tr("所有文件 (*.*)"));
    if (filePath.isEmpty())
        return;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, "错误", "无法打开文件");
        return;
    }
    QByteArray fileData = file.readAll();
    file.close();

    QFileInfo fileInfo(filePath);
    QString fileName = fileInfo.fileName();

    json msg;
    msg["cmd"] = cmd_file_transfer; // 你需要在协议里定义这个命令号
    msg["account"] = curChatAccount; // 对方账号
    msg["sender"] = selfInfo.account;
    msg["file_name"] = fileName;
    msg["file_size"] = fileData.size();
    msg["file_data"] = QString(fileData.toBase64()); // base64编码
    msg["timestamp"] = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    if (curChatType == 2) msg["is_group"] = 1;
    t->SendMsg(msg);

    // TODO: 在自己窗口显示"已发送文件"
    if (chatMap.contains(curChatAccount)) {
        ChatWindow* chatWindow = chatMap.value(curChatAccount);
        if (chatWindow) {
            chatWindow->addFileMessage(fileName, QString(fileData.toBase64()), true);
        }
    }
}

void Client::on_pushButton_screenshot_clicked() {
    // 实现截图功能
    ScreenShotWidget *shot = new ScreenShotWidget();
    connect(shot, &ScreenShotWidget::regionSelected, this, [this, shot]() {
        QRect rect = shot->getSelectedRect();
        QPixmap fullPixmap = shot->getScreenPixmap();
        if (rect.isNull() || rect.width() < 5 || rect.height() < 5) {
            shot->deleteLater();
            return;
        }
        QPixmap cropped = fullPixmap.copy(rect);
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);
        cropped.save(&buffer, "PNG");
        QString base64Image = byteArray.toBase64();
        ui->textEdit_send->insertHtml("<img src='data:image/png;base64," + base64Image + "' />");
        ui->textEdit_send->setFocus();
        shot->deleteLater();
    });
    shot->show();
}
