#include "logging.h" // 登录窗口类的头文件，定义了登录界面相关功能
#include <QBitmap> // Qt位图类，用于窗口遮罩等
#include <QGraphicsDropShadowEffect> // 阴影效果类，用于美化窗口
#include <QPainter> // 绘图类
#include "stringtool.h" // 字符串工具类
#include "client.h" // 主窗口类头文件，登录成功后进入主界面
#include<QPropertyAnimation> // 属性动画类，实现界面切换动画
#include <QThread> // 线程类
#include <QParallelAnimationGroup> // 并行动画组
#include <QSequentialAnimationGroup> // 顺行动画组
#include <QTimer> // 定时器类
#include <QShortcut> // 快捷键类
#include <QDebug> // 调试输出

using json = QJsonObject; // 定义json为QJsonObject类型，便于后续使用
using namespace std;

// Logging类构造函数，初始化登录窗口
Logging::Logging(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Logging)
{
    ui->setupUi(this); // 设置UI界面
    t = new TcpClient(this); // 创建TCP客户端对象，用于与服务器通信
    msgBox = new QMessageBox(this); // 创建消息提示框对象
    Init(); // 初始化窗口属性和控件
}

// 析构函数，释放UI资源
Logging::~Logging()
{
    delete ui;
}

// 初始化窗口属性和控件
void Logging::Init()
{
    this->setWindowTitle("WeChat 登录"); // 设置窗口标题
    setWindowFlags(windowFlags() | Qt::WindowMinimizeButtonHint); // 添加最小化按钮
    setWindowFlags(windowFlags() | Qt::WindowContextHelpButtonHint); // 添加帮助按钮

    int width = this->width()-10;
    int height = this->height()-10;
    ui->centerWidget->setGeometry(5,5,width,height); // 设置中心控件位置和大小
    ui->centerWidget->setStyleSheet("QWidget{border-radius:4px;background:rgba(255,255,255,1);}");  //设置圆角和背景色

    this->setWindowFlags(Qt::FramelessWindowHint); // 设置无边框窗口
    this->setAttribute(Qt::WA_TranslucentBackground,true); // 设置背景透明

    // 创建阴影效果
    QGraphicsDropShadowEffect *shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(0, 0); // 阴影偏移
    shadow->setColor(QColor(39,40,43,100)); // 阴影颜色
    shadow->setBlurRadius(10); // 阴影模糊半径
    ui->centerWidget->setGraphicsEffect(shadow); // 应用阴影到中心控件

    // 创建回车快捷键，绑定到登录按钮
    QShortcut *key=new QShortcut(QKeySequence(Qt::Key_Return),this);
    connect(key,&QShortcut::activated,this,&Logging::on_pushButton_login_clicked);

    // 连接TCP客户端的信号到本类的命令处理槽
    connect(t, &TcpClient::CallLogging, this, [this](const QJsonObject& msg){
        CmdHandler(msg);
    });
}

// 鼠标按下事件，记录鼠标相对窗口左上角的位置，用于后续拖动窗口
void Logging::mousePressEvent(QMouseEvent *event)
{
    mouseWindowTopLeft = event->pos();
}

// 鼠标移动事件，实现窗口拖动
void Logging::mouseMoveEvent(QMouseEvent *event)
{
    // 如果按下左键
    if (event->buttons() & Qt::LeftButton)
    {
        mouseDeskTopLeft = event->globalPosition().toPoint(); // 鼠标在桌面上的位置
        windowDeskTopLeft = mouseDeskTopLeft - mouseWindowTopLeft;  // 计算窗口左上角新位置
        this->move(windowDeskTopLeft);     // 移动窗口
    }
}

// 最小化按钮槽函数
void Logging::on_pushBtn_hide_clicked()
{
    QWidget* pWindow = this->window();
    if(pWindow->isWindow())
        pWindow->showMinimized(); // 最小化窗口
}

// 关闭按钮槽函数，发送登出命令并关闭窗口
void Logging::on_pushBtn_close_clicked()
{
    json msg;
    msg.insert("cmd",cmd_logout); // 插入登出命令
    t->SendMsg(msg); // 发送消息到服务器
    this->close(); // 关闭窗口
}

// 另一个关闭按钮槽函数（可能用于注册页等），同样发送登出命令并关闭
void Logging::on_pushBtn_close_2_clicked()
{
    json msg;
    msg.insert("cmd",cmd_logout);
    t->SendMsg(msg);
    this->close();
}

// 另一个最小化按钮槽函数
void Logging::on_pushBtn_hide_2_clicked()
{
    QWidget* pWindow = this->window();
    if(pWindow->isWindow())
        pWindow->showMinimized();
}

// 返回按钮槽函数，切换到登录页面
void Logging::on_pushButton_return_clicked()
{
    PageSwitch(0); // 切换到第0页（登录页）
}

// 注册按钮槽函数，切换到注册页面
void Logging::on_pushbtn_regist_clicked()
{
    PageSwitch(1); // 切换到第1页（注册页）
}

// 页面切换函数，实现登录页与注册页的切换，并带有滑动动画效果
void Logging::PageSwitch(int pageIndex)
{
    int curIndex = ui->stackedWidget->currentIndex(); // 当前页面索引
    {
        // 检查目标页索引是否合法
        if (pageIndex < 0 || pageIndex >= ui->stackedWidget->count()) {
            return;
        }
        QWidget *currentPage = ui->stackedWidget->currentWidget(); // 当前页面
        QWidget *targetPage = ui->stackedWidget->widget(pageIndex); // 目标页面
        targetPage->setGeometry(0,0,currentPage->width(),currentPage->height()); // 设置目标页面大小

        // 如果页面无效或已经是当前页，直接返回
        if (!currentPage || !targetPage || currentPage == targetPage) {
            return;
        }

        int currentPageX = currentPage->x();
        int targetPageX = targetPage->x();
        int currentPageWidth = currentPage->width();
        // 创建当前页面向左滑出的动画
        QPropertyAnimation *currentPageAnimation = new QPropertyAnimation(currentPage, "geometry");
        currentPageAnimation->setDuration(600); // 动画时长
        currentPageAnimation->setEasingCurve(QEasingCurve::InOutQuad); // 缓动曲线
        // 创建目标页面从右至左滑进的动画
        QPropertyAnimation *targetPageAnimation = new QPropertyAnimation(targetPage, "geometry");
        targetPageAnimation->setDuration(600);
        targetPageAnimation->setEasingCurve(QEasingCurve::InOutQuad);

        if(pageIndex == 1) // 切换到注册页
        {
            currentPageAnimation->setStartValue(QRect(currentPageX, currentPage->y(), currentPageWidth, currentPage->height()));
            currentPageAnimation->setEndValue(QRect(currentPageX - currentPageWidth, currentPage->y(), currentPageWidth, currentPage->height()));

            targetPageAnimation->setStartValue(QRect(targetPageX + currentPageWidth, targetPage->y(), targetPage->width(), targetPage->height()));
            targetPageAnimation->setEndValue(QRect(targetPageX, targetPage->y(), targetPage->width(), targetPage->height()));
        }
        else // 切换回登录页
        {
            currentPageAnimation->setStartValue(QRect(currentPageX, currentPage->y(), currentPageWidth, currentPage->height()));
            currentPageAnimation->setEndValue(QRect(currentPageX + currentPageWidth, currentPage->y(), currentPageWidth, currentPage->height()));

            targetPageAnimation->setStartValue(QRect(targetPageX - currentPageWidth, targetPage->y(), targetPage->width(), targetPage->height()));
            targetPageAnimation->setEndValue(QRect(targetPageX, targetPage->y(), targetPage->width(), targetPage->height()));
        }
        // 创建动画组，添加动画，并启动动画组
        QParallelAnimationGroup *animationGroup = new QParallelAnimationGroup();
        animationGroup->addAnimation(currentPageAnimation);
        animationGroup->addAnimation(targetPageAnimation);
        ui->stackedWidget->widget(pageIndex)->setVisible(true);
        ui->stackedWidget->widget(pageIndex)->update();
        ui->stackedWidget->widget(pageIndex)->show();
        animationGroup->start(QAbstractAnimation::DeleteWhenStopped);

        animationGroup->setProperty(
            "widget", QVariant::fromValue(ui->stackedWidget->widget(curIndex)));

        connect(animationGroup, &QParallelAnimationGroup::finished, [=]() {
            // 动画结束后切换页面
            ui->stackedWidget->widget(pageIndex)->hide();
            ui->stackedWidget->setCurrentIndex(pageIndex);
        });
    }
}

// 登录按钮点击槽函数，处理登录逻辑
void Logging::on_pushButton_login_clicked()
{
    if(!t->m_isConnected) // 如果还未连接服务器
    {
        qDebug() << "未连接" << endl;
        if(t->ConnectToServer() == -1) // 尝试连接服务器
        {
            qDebug() << "连接失败" << endl;
            return;
        }
    }
    if(!ui->lineEdit_account->text().size()) // 检查账号是否为空
    {
        msgBox->setText("账号不能为空");
        msgBox->exec();
        return;
    }
    if(!ui->lineEdit_password->text().size()) // 检查密码是否为空
    {
        msgBox->setText("密码不能为空");
        msgBox->exec();
        return;
    }
    // 构造登录请求消息
    json msg;
    msg.insert("cmd", cmd_login); // 登录命令
    msg.insert("account", ui->lineEdit_account->text());
    msg.insert("password", ui->lineEdit_password->text());
    t->SendMsg(msg); // 发送消息到服务器
}

// 注册按钮点击槽函数，处理注册逻辑
void Logging::on_pushButton_regist_clicked()
{
    if(!t->m_isConnected) // 如果还未连接服务器
    {
        if(t->ConnectToServer() == -1)
        {
            msgBox->setText("连接服务器失败");
            msgBox->exec();
            return;
        }
    }
    if(!ui->lineEdit_account_2->text().size())
    {
        msgBox->setText("账号不能为空");
        msgBox->exec();
        return;
    }
    if(!ui->lineEdit_password_2->text().size())
    {
        msgBox->setText("密码不能为空");
        msgBox->exec();
        return;
    }
    if(ui->lineEdit_password_2->text() != ui->lineEdit_password_3->text())
    {
        msgBox->setText("两次输入的密码不一致");
        msgBox->exec();
        return;
    }
    // 构造注册请求消息
    json msg;
    msg.insert("cmd", cmd_regist); // 注册命令
    msg.insert("account", ui->lineEdit_account_2->text());
    msg.insert("password", ui->lineEdit_password_2->text());
    msg.insert("name", ui->lineEdit_name->text());
    t->SendMsg(msg); // 发送消息到服务器
}

void Logging::on_pushButton_seePassword_clicked()
{
    if(ui->lineEdit_password->echoMode() == QLineEdit::Password)
    {
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    }
    else
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}

void Logging::CmdHandler(json msg)
{
    if(msg.isEmpty()) return ;
    int cmd = msg.value("cmd").toInt();
    switch(cmd) {
    case cmd_login: {
        if (msg.value("res").toString() == "yes") {
            qDebug() << "登录成功";
            QString a = ui->lineEdit_account->text();
            int account;
            if (a.startsWith("0x") || a.startsWith("0X"))
                account = a.toInt(NULL, 16);
            else if (a.startsWith("0"))
                account = a.toInt(NULL, 8);
            else
                account = a.toInt();
            SelfInfo info;
            QJsonArray arr = msg.value("info").toArray();
            info.account = account;
            info.password = ui->lineEdit_password->text();
            info.name = arr[0].toString();
            info.sig = arr[1].toString();
            info.icon = arr[2].toString();
            qDebug() << info.account << " " << info.password << " " << info.name << " " << info.sig << " " << info.icon << endl;
            static Client *client = new Client(info, t);
            client->show();
            this->close();
        } else {
            // 登录失败，弹窗显示服务器返回的err信息
            msgBox->setText(msg.value("err").toString());
            msgBox->exec();
        }
        break;
    }

    case cmd_regist: {
        if (msg.value("res").toString() == "yes") {
            msgBox->setText("注册成功");
            msgBox->showNormal();
        } else {
            msgBox->setText("注册失败");
            msgBox->showNormal();
        }
    }
    default:
        break;
    }
}




