#include "Ircserver.hpp"
#include "Client.hpp"
#include "Channel.hpp"

Client::Client(int fd, std::string name) : 
	_fd(fd),
	_hostname(name),
	_username(""),
	_nickname(""),
	_realname(""),
	_partialInput(""),
	_isRegistered(false),
	_isAuth(false),
	_isOp(false),
	_isInvisible(false),
	_isWallops(false)
	{ }
Client::~Client() {
	quitChannels();
}

//fct rajouter apres derniere vertion 
void	Client::joinChannel(Channel *channel)
{
	channel->addUser(this);
	_channels.push_back(channel);
}
//quiter channel
void Client::quitChannel(Channel *channel)
{
    if (!channel)
        return;

    // Recherche manuelle du canal dans le vecteur
    std::vector<Channel*>::iterator it;
    for (it = _channels.begin(); it != _channels.end(); ++it)
    {
        if (*it == channel)
        {
            // Canal trouvé. Sortez de la boucle
            break;
        }
    }

    // Vérifiez si le canal a été trouvé
    if (it != _channels.end())
    {
        (*it)->removeUser(this);
        _channels.erase(it);
    }
}

//quiter tout channel
void	Client::quitChannels() {
	std::vector<Channel*> tmp(_channels);
	for (std::vector<Channel*>::iterator it = tmp.begin(); it != tmp.end(); ++it)
		this->quitChannel(*it);
}

