#ifndef IRCSERVER_HPP
#define IRCSERVER_HPP
#define MAX_CLIENTS 5
#define MAX_EVENTS 5
#define SUCCESS 0
#define FAILURE -1
#include <iostream>
#include <functional>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>//pour la structure sockaddr_in
#include <vector>
#include "Client.hpp"
#include <sstream>
#include <map>
#include <signal.h>
#include "commands.hpp"
#include "Channel.hpp"
//#include "globals.hpp"
/*MAX_EVENTS le choix pour max_event
    5 : pour gérer les événements de base
    10 : pour gérer les événements de base et quelques messages volumineux
    20 : pour gérer de nombreux messages volumineux
*/
class Client ; 
class Channel;

class IRCServer
{
private:
    int serverSocket;//descripteur de fichier(fd)
    int port;//numero de porte
    std::string password;
    typedef int (*CommandFunction)(IRCServer&, Client&, std::vector<std::string>&);
    std::map<std::string, CommandFunction> _commands;
    std::map<int, Client*>clients;
    std::vector<Channel*>chanells;
    int epollFd;
    std::string _name;
public:
    IRCServer(int port,std::string password);
    ~IRCServer();
    IRCServer(const IRCServer &other);
    IRCServer& operator=(const IRCServer &other);
    std::string getServerName() const {
        return _name; // Remplacez ceci par le nom réel de votre serveur
    }

    /*****************clients***********************/
    std::map<int, Client*> getClients() const {
        return clients;
    }
    std::vector<Channel*> getChannel() const {
        return chanells;
    }
    void addClient(int clientId, Client* client);
    void removeClient(int clientId);
    Client *getClientByNickname(const std::string &nickname);

    Client *getClientByUsername(const std::string &username);
    Client *getClientByFd(int fd);
    void MsgForListClient(const std::string &message);
    /*****************chanell***********************/
    std::vector<Channel*> getChanell() const {
        return chanells;
    }
    void addChanell(Channel* channel);
    void removeChannel(Channel* Channel);
    Channel* getChannelByName(std::string name);
    const char* concatenate(const char* str1, const char* str2);
    void broadcastMessage(const char* message);
    /*************************************************/
    int getPort(){ return (port); }

		std::string getPassword(){ return (password); }
		void setPassword(std::string new_pwd){password = new_pwd;}

		int getEpollFd(){ return (epollFd); }
		void setEpollFd(int epoll){epollFd = epoll;}
		int setupEpoll();

		bool	start();
		void	stop();
		void	sendMessage(int clientSocket, const std::string message);
		void    acceptConnections(); 
		int     parseCommand(Client *client, std::string &message);
		int     parseCommand2(Client *client, std::string &message);
		void    NewMsg(int client_fd);
		int    NewConnection(int epollFd, struct sockaddr_in &client_address, socklen_t &client_len);
		void    initCommands( void );
};

#endif 
