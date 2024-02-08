#ifndef CLIENT_HPP
# define CLIENT_HPP
# include "Ircserver.hpp"
# include "Channel.hpp"
# include <vector>

class Channel;
class IRCServer;

class Client
{
	private:
		int						_fd;//Il s'agit probablement d'un descripteur de fichier pour représenter la connexion avec le client
		std::string				_hostname; // C'est le nom de l'ordinateur à partir duquel le client se connecte.
		std::string				_username; // Il représente le nom utilisé à des fins d'authentification et peut être unique pour chaque utilisateur.
		std::string				_nickname; // Il s'agit d'un nom utilisé pour identifier l'utilisateur dans le chat.
		std::string				_realname;//Ce champ contenir le vrai nom de l'utilisateur.
		std::string				_partialInput;//une variable utilisée pour stocker une entrée partielle du client avant de recevoir une entrée complète.
		bool					_isRegistered;//Un indicateur booléen indiquant si le client est enregistré.
		bool					_isAuth;//C'est un indicateur booléen pour représenter si le client est authentifié.
		bool					_isOp;// Indique si le client est un opérateur.
		bool					_isInvisible;// Indique si le client est invisible.
		bool					_isWallops;// Indique si le client reçoit les messages de type "wallops".
		std::string				_name;
		std::vector<Channel *>	_channels;

	public:
		Client(int fd, const std::string name);
		~Client();
		void msg(const std::string &message) 
		{
		if (_fd)
			send(_fd, message.c_str(), message.size(), 0);
		}
		int			getFd() { return _fd; };
		std::string getHostname() { return _hostname; };
		std::string getUsername() { return _username; };
		std::string getNickname() { return _nickname; };
		std::string getRealname() { return _realname; };
		std::string getPartialInput() { return _partialInput; };
		bool 		getRegistered() { return _isRegistered; };
		bool 		getAuth() { return _isAuth; };
		bool 		getOp() { return _isOp; };
		bool 		getInvisible() { return _isInvisible; };
		bool 		getWallops() { return _isWallops; };
		void 		setFd(int &fd ) { _fd = fd; };
		void 		setHostname(std::string const &hostname ) { _hostname = hostname; };
		void 		setUsername(std::string const &username ) { _username = username; };
		void 		setNickname(std::string const &nickname ) { _nickname = nickname; };
		void 		setRealname(std::string const &realname ) { _realname = realname; };
		void 		setPartialInput(std::string const &partialInput ) { _partialInput = partialInput; };
		void 		setRegistered(bool isRegistered) { _isRegistered = isRegistered; };
		void 		setAuth(bool isAuth) { _isAuth = isAuth; };
		void 		setOp(bool isOp) { _isOp = isOp; };
		void 		setInvisible(bool isInvisible) { _isInvisible = isInvisible; };
		void 		setWallops(bool isWallops) { _isWallops = isWallops; };
		std::vector<Channel *> getChannels() { return _channels; };
		Channel*	getChannel(const std::string channelName);
		void		joinChannel(Channel *channel);
		void		quitChannel(Channel *channel);
		void		quitChannels();
};
#endif