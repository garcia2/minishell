/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nigarcia <nigarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 13:57:37 by nigarcia          #+#    #+#             */
/*   Updated: 2023/09/15 00:00:01 by nigarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_env_list *env)
{
	char	**paths;
	char	*env_path;

	env_path = get_env_by_key(env, "PATH");
	if (env_path == NULL)
		return (NULL);
	paths = ft_split(env_path, ':');
	return (paths);
}

char	*join_path_and_command(char *command, char *path)
{
	char	*str_temp;
	char	*path_and_command;

	str_temp = ft_strjoin(path, "/");
	if (str_temp == NULL)
		return (NULL);
	path_and_command = ft_strjoin(str_temp, command);
	free(str_temp);
	return (path_and_command);
}

char	*find_valid_path(char *command, char **paths)
{
	int		i;
	char	*command_path;

	if (ft_strlen(command) == 0)
		return (NULL);
	i = 0;
	while (paths[i] != NULL)
	{
		command_path = join_path_and_command(command, paths[i]);
		if (command_path != NULL)
		{
			if (access(command_path, X_OK) == 0)
				return (command_path);
			free(command_path);
		}
		i++;
	}
	return (NULL);
}

int	set_command_path(t_cmd_table *cmd_table, t_env_list *env)
{
	char	*command_path;
	char	**paths;

	if (cmd_table->cmd[0][ft_strlen(cmd_table->cmd[0]) - 1] == '.'
		|| cmd_table->cmd[0][ft_strlen(cmd_table->cmd[0]) - 1] == '/')
		return (-1);
	if (access(cmd_table->cmd[0], X_OK) == 0)
		return (1);
	paths = get_paths(env);
	if (paths == NULL)
		return (0);
	command_path = find_valid_path(cmd_table->cmd[0], paths);
	free_lexer(paths);
	if (command_path == NULL)
	{
		if (access(cmd_table->cmd[0], X_OK) == 0)
			return (1);
		else
			return (0);
	}
	free(cmd_table->cmd[0]);
	cmd_table->cmd[0] = command_path;
	return (1);
}
