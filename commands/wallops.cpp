#include "../commands.hpp"

//WALLOPS : permet à l'utilisateur d'envoyer un message à tous les utilisateurs présents sur le serveur.

int wallops(IRCServer &server, Client &client, std::vector<std::string> &arguments) {
	// Vérifiez l'authentification ou l'enregistrement du client
	if (!client.getAuth() && !client.getRegistered()) {
		client.msg(ERR_NOTREGISTERED(client.getNickname(), arguments[0]));
		return 0;
	}

	// Vérifiez si suffisamment d'arguments sont fournis
	if (arguments.size() < 2) {
		client.msg(ERR_NEEDMOREPARAMS(client.getNickname(), arguments[0]));
		return 0;
	}

	// Vérifiez si le client est un opérateur
	if (!client.getOp()) {
		client.msg(ERR_NOPRIVILEGES(client.getNickname()));
		return 0;
	}

	// Préparez le message à envoyer
	std::string message = "";
	for (size_t i = 1; i < arguments.size(); ++i) {
		message += arguments[i] + " ";
	}
	if (!message.empty() && message[0] == ':') {
		message = message.substr(1);
	}

	// Utilisez la fonction existante MsgForListClient pour envoyer le message à tous les clients
	server.MsgForListClient(":" + client.getNickname() + " WALLOPS :" + message+ "\r\n");

	return 1;
}