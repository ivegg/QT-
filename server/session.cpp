#include "session.h"
#include "CommandHandler.h"
#include <unistd.h>
#include <ctime>
#include <iomanip>
#include <sstream>
using namespace std;
using json = nlohmann::json_abi_v3_11_2::json;

std::string getCurrentTimeString() {
    std::time_t t = std::time(nullptr);
    std::tm tm;
    localtime_r(&t, &tm);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

Session::Session(int socket)
{
    m_isLogin = -1;
    m_account = -1;
    m_socket = socket;
}

Session::~Session()
{
    if (m_socket != -1)
    {
        close(m_socket);
        m_socket = -1;
    }
    if (m_isLogin == 1)
    {
        cleanSession();
        m_isLogin = -1;
    }
};

int Session::handleMsg(json msg)
{
    usleep(1000);
    int cmd = msg.at("cmd");
    //LOGINFO("handleMsg command:%s\n", cmd.c_str());
    printf("[DEBUG] handleMsg received cmd=%d\n", cmd);
    switch (cmd)
    {
         case cmd_regist:
            {
                string account = msg.at("account");
                string password = msg.at("password");
                string name = msg.at("name");
                try{
                    int a = stoi(account,0,0);
                    CommandHandler::Regist(a, password, name, this);
                }
                catch(std::invalid_argument &e)
                {
                    cout <<e.what()<<endl;
                    return 0;
                }
            break;
            }   
        
        case cmd_login:
        {
            string account = msg.at("account");
            string password = msg.at("password");
            
            try{
                int a = stoi(account,0,0);
                CommandHandler::Login(a, password, this);
            }
            catch(std::invalid_argument &e)
           {
                return 0;
           }
           break;
        }
        case cmd_friend_search:
        {
            string info = msg.at("search-info");
            CommandHandler::Search(info, this);
            break;
        }
        case cmd_add_friend_request:
        {
            int sender = msg.at("sender");
            int account = msg.at("account");
            string msg1 = msg.at("msg");
            UserInfo info = {sender,"",msg.at("name"),msg.at("sig"),1,msg.at("icon")};
            CommandHandler::AddFriendRequest(info,account,msg1, this);
        }
        break;
        case cmd_add_friend_response:
        {
            int sender = msg.at("sender");
            int account = msg.at("account");
            int fd = getFriendFd(sender);
            string res;
            if(msg.at("reply") == "yes")
            {
                res="同意";
                Statement query(db,"insert into friend values(?,?)");
                query.bind(1,sender);//发送请求的人
                query.bind(2,account);
                query.exec();
                CommandHandler::FriendList(account, this);
                CommandHandler::FriendList(sender, this);
            }
            else res = "拒绝";
            if(fd > 0)
            {
                string msg1 = std::to_string(account) + res + "了你的好友请求";
                sendSystemMsg(fd,msg1);
            }
            
            break;
        }
        break;
        case cmd_friend_list:
        {
            usleep(400000);
            int account = msg.at("account");
            CommandHandler::FriendList(account, this);
            break;
        }
        case cmd_friend_chat:
        {
            int sender_id = msg.at("sender");
            int receiver_id = msg.at("account");
            std::string content = msg.at("content");
            int msg_type = msg.at("type");
            std::string send_time = msg.value("timestamp", "");

            printf("[DEBUG] cmd_friend_chat: sender_id=%d, receiver_id=%d, content=%s, msg_type=%d, send_time=%s\n", sender_id, receiver_id, content.c_str(), msg_type, send_time.c_str());
            // 保存到数据库
            try {
                Statement stmt(db, "INSERT INTO message (sender_id, receiver_id, content, msg_type, send_time, is_group) VALUES (?, ?, ?, ?, ?, 0)");
                stmt.bind(1, sender_id);
                stmt.bind(2, receiver_id);
                stmt.bind(3, content);
                stmt.bind(4, msg_type);
                std::string actual_time = send_time.empty() ? getCurrentTimeString() : send_time;
                stmt.bind(5, actual_time);
                stmt.exec();
                printf("[DEBUG] Friend message inserted into DB.\n");
            } catch (std::exception& e) {
                printf("[ERROR] Friend message insert failed: %s\n", e.what());
            }

            int fd = getFriendFd(receiver_id);
            if(fd > 0)
            {
                sendMsg(fd,msg);
            }
            else{
                //not online
            }
            break;
        }
        
        case cmd_group_create:
        {
            int account = msg.at("account");
            std::string groupname = msg.at("groupName");
            std::vector<int> members;
            for (auto& m : msg.at("members")) {
                members.push_back(m);
            }
            CommandHandler::GroupCreate(account, groupname, members, this);
            break;
        }
        
        case cmd_group_search:
        {
            string searchInfo = msg.at("search-info");
            CommandHandler::GroupSearch(searchInfo, this);
            break;
        }
        
        case cmd_group_join_request:
        {
            int account = msg.at("account");//group account
            int sender = msg.at("sender");//request sender
            string groupname = msg.at("groupName");
            UserInfo info = {sender,"",msg.at("name"),msg.at("sig"),1,msg.at("icon")};
            CommandHandler::GroupJoinReguest(info,account, groupname, msg.at("msg"),this);
            break;
        }
        case cmd_group_join_response:
        {
            string name = msg.at("name");
            int account = msg.at("account");//group account
            int sender = msg.at("sender");//request sender

            int fd = getFriendFd(sender);
            sendMsg(fd,msg);
            if(msg.at("reply") == "yes")
            {
                sendSystemMsg(fd,"群主同意了你的加群请求");
                Statement query(db,"insert into member values(?,?,?)");
                query.bind(1,sender);
                query.bind(2,account);
                query.bind(3,name);
                query.exec();
                CommandHandler::GroupList(sender, this);
            }
            break;
        }
        
        case cmd_group_list:
        {
            int account = msg.at("account");
            CommandHandler::GroupList(account, this);
            break;
        }
        
        case cmd_group_chat:
        {
            int sender_id = msg.at("sender");
            int group_id = msg.at("account");
            std::string content = msg.at("content");
            int msg_type = msg.at("type");
            std::string send_time = msg.value("timestamp", "");

            printf("[DEBUG] cmd_group_chat: sender_id=%d, group_id=%d, content=%s, msg_type=%d, send_time=%s\n", sender_id, group_id, content.c_str(), msg_type, send_time.c_str());
            // 保存到数据库
            try {
                Statement stmt(db, "INSERT INTO message (sender_id, group_id, content, msg_type, send_time, is_group) VALUES (?, ?, ?, ?, ?, 1)");
                stmt.bind(1, sender_id);
                stmt.bind(2, group_id);
                stmt.bind(3, content);
                stmt.bind(4, msg_type);
                std::string actual_time = send_time.empty() ? getCurrentTimeString() : send_time;
                stmt.bind(5, actual_time);
                stmt.exec();
                printf("[DEBUG] Group message inserted into DB.\n");
            } catch (std::exception& e) {
                printf("[ERROR] Group message insert failed: %s\n", e.what());
            }

            vector<int> friendList = getGroupMember(group_id);
            vector<int> fds = getFriendFd(friendList);
            // 找到fds中自己的fd，然后从fds中删除
            int selfFd = GetSocket();
            auto it = find(fds.begin(), fds.end(), selfFd);
            if (it != fds.end())
            {
                fds.erase(it);
                cout << "skip self" << endl;
            }
            sendMsg(fds, msg);
            break;
        }
        case cmd_group_member_list:
        {
            int account = msg.at("groupAccount");
            CommandHandler::GroupMemberList(account, this);
            break;
        }
        
        case cmd_group_member_add:
        {
            string account = msg.at("account");
            string groupname = msg.at("groupname");
            //CommandHandler::GroupMemberAdd(stoi(account), groupname, this);
            break;
        }
        case cmd_group_member_del:
        {
            string account = msg.at("account");
            string groupname = msg.at("groupname");
            //CommandHandler::GroupMemberDel(stoi(account), groupname, this);
            break;
        }
        case cmd_set_icon:
        {
            int account = msg.at("account");
            string icon = msg.at("icon");
            Statement query(db,"update user set icon=? where account=?");
            query.bind(1,icon);
            query.bind(2,account);
            query.exec();
            break;
        }
        case cmd_file_transfer:
        {
            int sender_id = msg.at("sender");
            int receiver_id = msg.at("account");
            int is_group = msg.value("is_group", 0);
            if (is_group == 1) {
                // 群聊：转发给所有群成员（除自己）
                vector<int> member_ids = getGroupMember(receiver_id);
                vector<int> fds = getFriendFd(member_ids);
                int selfFd = GetSocket();
                auto it = find(fds.begin(), fds.end(), selfFd);
                if (it != fds.end()) fds.erase(it);
                sendMsg(fds, msg);
            } else {
                // 单聊
                int fd = getFriendFd(receiver_id);
                printf("[DEBUG] file_transfer: sender=%d, receiver=%d, fd=%d\n", sender_id, receiver_id, fd);
                if (fd > 0) {
                    sendMsg(fd, msg);
                    printf("[DEBUG] file_transfer: sendMsg called\n");
                }
                printf("[DEBUG] file_transfer: receiver_id=%d, fd=%d\n", receiver_id, fd);
            }
            break;
        }
        case cmd_get_history:
        {
            int type = msg.at("type"); // 0=私聊, 1=群聊
            json resp;
            resp["cmd"] = cmd_get_history;
            resp["type"] = type;

            if (type == 0) { // 私聊
                int user_id = msg.at("user_id");
                int peer_id = msg.at("peer_id");
                Statement stmt(db, "SELECT sender_id, receiver_id, content, msg_type, send_time FROM message WHERE ((sender_id=? AND receiver_id=?) OR (sender_id=? AND receiver_id=?) ) AND is_group=0 ORDER BY send_time ASC");
                stmt.bind(1, user_id);
                stmt.bind(2, peer_id);
                stmt.bind(3, peer_id);
                stmt.bind(4, user_id);
                json history = json::array();
                while (stmt.executeStep()) {
                    json m;
                    m["sender_id"] = stmt.getColumn(0).getInt();
                    m["receiver_id"] = stmt.getColumn(1).getInt();
                    m["content"] = stmt.getColumn(2).getString();
                    m["msg_type"] = stmt.getColumn(3).getInt();
                    m["send_time"] = stmt.getColumn(4).getString();
                    history.push_back(m);
                }
                resp["history"] = history;
            } else if (type == 1) { // 群聊
                int group_id = msg.at("group_id");
                resp["group_id"] = group_id;
                Statement stmt(db, "SELECT sender_id, content, msg_type, send_time FROM message WHERE group_id=? AND is_group=1 ORDER BY send_time ASC");
                stmt.bind(1, group_id);
                json history = json::array();
                while (stmt.executeStep()) {
                    json m;
                    m["sender_id"] = stmt.getColumn(0).getInt();
                    m["content"] = stmt.getColumn(1).getString();
                    m["msg_type"] = stmt.getColumn(2).getInt();
                    m["send_time"] = stmt.getColumn(3).getString();
                    history.push_back(m);
                }
                resp["history"] = history;
            }
            sendMsg(resp);
            break;
        }
    }
    return 0;
}

void Session::sendMsg(json &j)
{
    std::string msg = j.dump();
    int len = msg.length();
    char buffer[4];
    memcpy(buffer, &len, sizeof(len));

    char *message = new char[4 + len];
    memcpy(message, buffer, 4); // 将长度复制到message
    memcpy(message + 4, msg.c_str(), len); // 将消息内容复制到message

    // 使用 send 函数发送消息
    send(m_socket, message, len + 4, 0);

    std::cout << "send: " << msg << std::endl;
    delete[] message;
    message = nullptr;
}


void Session::sendMsg(int fd, json &j)
{
    std::string msg = j.dump();
    int len = msg.length();
    char buffer[4];
    memcpy(buffer, &len, sizeof(len));

    char *message = new char[4 + len];
    memcpy(message, buffer, 4); // 将长度复制到message
    memcpy(message + 4, msg.c_str(), len); // 将消息内容复制到message

    // 使用 send 函数发送消息
    send(fd, message, len + 4, 0);

    std::cout << "send: " << msg << std::endl;
    delete[] message;
    message = nullptr;
}

void Session::sendMsg(vector<int> fds, json &j)
{
    std::string msg = j.dump();
    int len = msg.length();
    char buffer[4];
    memcpy(buffer, &len, sizeof(len));

    char *message = new char[4 + len];
    memcpy(message, buffer, 4); // 将长度复制到message
    memcpy(message + 4, msg.c_str(), len); // 将消息内容复制到message

    // 使用 send 函数发送群体消息
    for(auto fd : fds)
    {
        send(fd, message, len + 4, 0);
    }
    std::cout << "send group msg: " << message << std::endl;
    delete[] message;
    message = nullptr;
}

json Session::recvMsg()
{
    json j;
    int len = 0;
    char buffer[4];
    memset(buffer, 0, 4);

    while (1)
    {
        int res = recv(m_socket, buffer, 4, 0);
        if (res > 0)
            break;
        if (res <= 0)
        {
            if (errno == EWOULDBLOCK || errno == EAGAIN)
                continue;
            j["cmd"] = cmd_logout;
            return j;
        }
    }

    memcpy(&len, buffer, 4); // 使用memcpy从字节转换为整数

    char *msg = new char[len + 1];
    memset(msg, 0, len + 1);
    recv(m_socket, msg, len, MSG_WAITALL);

    std::cout << "rsvlen = " << std::to_string(len) << std::endl;
    std::cout << "rsvmsg = " << msg << std::endl;

    try
    {
        j = json::parse(msg);
    }
    catch (nlohmann::json_abi_v3_11_2::detail::parse_error &e)
    {
        std::cerr << "Failed to parse JSON: " << std::endl;
        std::cout << "error json msg : " << msg << endl;
    }

    delete[] msg;
    msg = nullptr;
    handleMsg(j);
    return j;
}


void Session::cleanSession()
{

}

vector<int> Session::getGroupMember(int groupId)
{
    Statement query(db, "SELECT member_id FROM member WHERE group_account=?;");
    query.bind(1, groupId);
    vector<int> accounts;
    while(query.executeStep())
    {
        int account = query.getColumn(0);
        accounts.push_back(account);
    }
    return accounts;
}

vector<int> Session::getFriendList(int account)
{
    Statement query(db,"select account from user where account in (select user2 from friend where user1=? union select user1 from friend where user2=?)");
    query.bind(1,account);
    query.bind(2,account);
    vector<int> fds;
    while(query.executeStep())
    {
        int fd = query.getColumn(0);
        fds.push_back(fd);
    }
    return fds;
}

vector<int> Session::getGroupList(int account)
{
    Statement query(db,"select group_account from member where account=?");
    query.bind(1,account);
    vector<int> group_accounts;
    while(query.executeStep())
    {
        int group_account = query.getColumn(0);
        group_accounts.push_back(group_account);
    }
    return group_accounts;

}

vector<int> Session::getFriendFd(vector<int> accounts)
{
    vector<int> fds;
    for(auto account : accounts)
    {
        for(auto it = userMap.begin(); it != userMap.end(); it++)
        {
            if(it->second == account)
            {
                fds.push_back(it->first);
            }
        }
    }
    return fds;
}

int Session::getFriendFd(int account)
{
    for(auto it = userMap.begin(); it != userMap.end(); it++)
    {
        if(it->second == account)
        {
            return it->first;
        }
    }
    return -1;
}

void Session::sendSystemMsg(int fd,string msg)
{
    json j;
    j["cmd"] = cmd_friend_chat;
    j["sender"] = 10000;
    j["msg"] = msg;
    sendMsg(fd,j);
}

int Session::getGroupOwnerFd(int groupId)
{
    Statement query(db,"select group_master from group_table where group_account=?");
    query.bind(1,groupId);
    int account = -1;
    if(query.executeStep())
    {
        account = query.getColumn(0);
    }
    return getFriendFd(account);
}
