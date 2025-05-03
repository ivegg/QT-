#include "client.h" // 主窗口类的头文件，包含聊天主界面的定义
#include "logging.h" // 登录窗口类的头文件，包含登录界面的定义
#include "tcpclient.h" // TCP客户端通信类的头文件，实现与服务器的通信
#include <QApplication> // Qt应用程序类，管理应用程序的控制流和主要设置

bool friendWidgetOn = false; // 全局变量，标记好友信息窗口是否打开

int main(int argc, char *argv[])
{
    QApplication a(argc, argv); // 创建Qt应用程序对象，管理应用程序生命周期
    Logging w; // 创建登录窗口对象
    w.show(); // 显示登录窗口
    return a.exec(); // 进入Qt事件循环，等待用户操作
}
