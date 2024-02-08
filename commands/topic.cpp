#include "../commands.hpp"

int topic(IRCServer &server, Client &client, std::vector<std::string> &arguments)
{
	if (!client.getAuth() && !client.getRegistered())
	{
		client.msg(ERR_NOTREGISTERED(client.getNickname(), "TOPIC"));
		return 0;
	}
	if (arguments.size() < 2)
	{
		client.msg(ERR_NEEDMOREPARAMS(client.getNickname(), "TOPIC"));
		return (0);
	}

	std::string channelName = arguments[1].substr(1);
	Channel *channel = server.getChannelByName(channelName);
	if (!channel)
	{
		client.msg(ERR_NOSUCHCHANNEL(client.getNickname(), channelName));
		return (0);
	}

	// Check if client is part of the channel.
	if (!channel->isUser(&client))
	{
		client.msg(ERR_NOTONCHANNEL(client.getNickname(), channelName));
		return (0);
	}
	
	// If no topic was provided, return the current topic.
	if (arguments.size() == 2)
	{
		std::string currentTopic = channel->getTopic();
		if (currentTopic.empty())
			client.msg(RPL_NOTOPIC(client.getNickname(), channel->getName()));
		else
			client.msg(RPL_TOPIC(client.getNickname(), channel->getName(), currentTopic));
		return 1;
	}
	else // A new topic was provided. Set the new topic.
	{
		std::string topic = "";
		for (int i = 2; i < (int)arguments.size(); i++)
			topic += arguments[i] + " ";

		// if topicRestricted, then Only operator can change topic.
		if (channel->getTopicRestricted() && !channel->isOperator(&client))
		{
			client.msg(ERR_CHANOPRIVSNEEDED(client.getNickname(), channel->getName()));
			return (0);
		}
		
		if (topic[0] == ':')
			topic = topic.substr(1);
		// Set the new topic.
		channel->setTopic(topic);

		// Notify the client that the topic was successfully changed.
		channel->sendToChannel(TOPIC(client.getNickname(), client.getUsername(), channel->getName(), channel->getTopic()),NULL);
	}
	return (1);
}