#include "chatTask.h"
using json = nlohmann::json;

void taskThread(int clientFd)
{
	try
	{
		printf("-------------------- new connect --------------------\n");		
		Session session(clientFd);
		json msg;
		while (1)
		{
			msg = session.recvMsg();			
			if (msg.at("cmd") == cmd_logout)
			{
				std::cout << "用户" << std::to_string(clientFd) << "下线" << std::endl;
				if(userMap.size()==1)
				{
					if(userMap.find(clientFd) != userMap.end())
					{
						int account = userMap.at(clientFd);
						std::cout << "userMap只剩一个，清理账号: " << account << std::endl;
						Statement query(db,"update user set online=0 where account=?");
						query.bind(1,account);
						query.exec();
					}
					userMap.erase(clientFd);
					close(clientFd);
					return ;
				}
				
				if(userMap.find(clientFd) != userMap.end())
				{
					//获取用户账号
					int account = userMap.at(clientFd);
					std::cout << "正常登出，清理账号: " << account << std::endl;
					Statement query(db,"update user set online=0 where account=?");
					query.bind(1,account);
					query.exec();
					json message;
					message["account"] = std::to_string(account);
					message["cmd"] = "loggout";
					std::cout << "用户" << std::to_string(userMap.at(clientFd)) << "下线" << std::endl;
					userMap.erase(clientFd);
				}
				else {
					std::cout << "正常登出时userMap中没有fd: " << clientFd << std::endl;
				}
				close(clientFd);
				return ;
			}
		}
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception caught: " << e.what() << std::endl;
		// 异常断开时清理online状态
		if(userMap.find(clientFd) != userMap.end())
		{
			int account = userMap.at(clientFd);
			std::cout << "异常断开，清理账号: " << account << std::endl;
			Statement query(db,"update user set online=0 where account=?");
			query.bind(1,account);
			query.exec();
			userMap.erase(clientFd);
		}
		else {
			std::cout << "异常断开时userMap中没有fd: " << clientFd << std::endl;
		}
		close(clientFd);
		return ;
	}
	// 正常退出循环时也清理online状态
	if(userMap.find(clientFd) != userMap.end())
	{
		int account = userMap.at(clientFd);
		std::cout << "循环结束，清理账号: " << account << std::endl;
		Statement query(db,"update user set online=0 where account=?");
		query.bind(1,account);
		query.exec();
		userMap.erase(clientFd);
	}
	else {
		std::cout << "循环结束时userMap中没有fd: " << clientFd << std::endl;
	}
	close(clientFd);
}
