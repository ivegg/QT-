#include "common.h"
#include "chatTask.h"
#include <unistd.h>
#include <limits.h>
#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

using namespace std;
static pthread_mutex_t _mxMessage;

// 直接指定数据库文件的绝对路径
SQLite::Database db("/home/share/chat-forge/server/build/user.db", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

//在线用户:<socketfd,account>
map<int,int> userMap;
int main(int argc,char* argv[])
{
    // 输出数据库文件路径
    printf("数据库文件路径: /home/share/chat-forge/server/build/user.db\n");
    
    char cwd[PATH_MAX];
    getcwd(cwd, sizeof(cwd));
    printf("当前工作目录: %s\n", cwd);

    printf("=== SERVER STARTED ===\n");
    
    // 执行建表命令
	db.exec("CREATE TABLE IF NOT EXISTS friend (user1 INTEGER NOT NULL, user2 INTEGER NOT NULL, PRIMARY KEY (user1, user2));");
	db.exec("CREATE TABLE IF NOT EXISTS group_table (group_account INTEGER PRIMARY KEY, group_name TEXT, create_time DATETIME, group_master INTEGER);");
	db.exec("CREATE TABLE IF NOT EXISTS user (account INTEGER PRIMARY KEY AUTOINCREMENT, password VARCHAR(32), name VARCHAR(32), signature TEXT, online INT DEFAULT 0 NOT NULL, icon TEXT);");
	db.exec("CREATE TABLE IF NOT EXISTS member (member_id INTEGER, group_account INTEGER, group_nickname TEXT);");

    // 启动时重置所有用户的online状态
    db.exec("UPDATE user SET online=0");

    int default_port = 8888;
    int optch = 0;
    while ((optch = getopt(argc, argv, "s:p:")) != -1)
    {
        switch (optch)
        {
        case 'p':
            default_port = atoi(optarg);
            LOGINFO("port: %s\n", optarg);
            break;
        case '?':
            LOGINFO("Unknown option: %c\n", (char)optopt);
            break;
        default:
            break;
        }
    }
    pthread_mutex_init(&_mxMessage, NULL);
    // pthread_mutex_lock(&_mxMessage);   //lock the mutex

    // pthread_mutex_unlock(&_mxMessage);  //unlock the mutex
    /*声明服务器地址和客户链接地址*/
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len;

    /*声明服务器监听套接字和客户端链接套接字*/
    int listen_fd,connect_fd;

    /*(1) 初始化监听套接字listenfd*/
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1)
    {
        perror("Socket Error:");
        return 0;
    }

    /*(2) 设置服务器sockaddr_in结构*/
    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); //任意地址
    server_addr.sin_port = htons(default_port);

    // 设置允许socket立即重用
    int val = 1;
    setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (void *)&val, sizeof(listen_fd));  
    //setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&listen_fd, sizeof(listen_fd));  

    /*(3) 绑定套接字和端口*/
    if (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    {
        perror("Bind error:");
        return 0;
    }

    /*(4) 监听客户请求*/
    if (listen(listen_fd, 4) == -1)
    {
        perror("Listen error:");
        return 0;
    }
    /*(5) 接受客户请求*/
    vector<thread> threadPool;
    for (;;)
    {
        client_len = sizeof(client_addr);
        connect_fd = accept(listen_fd, (struct sockaddr *)&client_addr, &client_len);
        if (connect_fd < 0)
        {
            perror("accept error");
            return 0;
        }
        LOGINFO("Connect from %s:%u...\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        threadPool.emplace_back(taskThread, connect_fd);
    }
    close(listen_fd);
    //db->close();

    return 0;
}
