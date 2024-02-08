#include "../commands.hpp"

// Command to quit the irc
// input[0] = quit command
// input[1] = message why quit (optional)
int quit(IRCServer &server, Client &client, std::vector<std::string> &arguments)
{
	std::vector<Channel *> channels = client.getChannels();

	if (arguments.size() < 2)
	{
		client.msg(ERR_NEEDMOREPARAMS(client.getNickname(), arguments[0]));
		return 0;
	}

	// Notify other clients in the channels that this client is part of.
	for (std::vector<Channel *>::iterator channel = channels.begin(); channel != channels.end(); channel++)
		(*channel)->sendToChannel(QUIT(client.getNickname(), client.getUsername(), arguments[1].substr(1)),&client);

	// Disconnect the client.
	server.removeClient(client.getFd());

	return 1;
}