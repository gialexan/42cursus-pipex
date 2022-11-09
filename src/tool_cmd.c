/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:52:20 by gialexan          #+#    #+#             */
/*   Updated: 2022/11/09 18:36:14 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	format_cmd(char **str, int value, int sub)
{
	int		i;
	int		asp;
	char	*tmp;

	i = -1;
	asp = 0;
	tmp = *str;
	while (tmp[++i])
	{
		if (tmp[i] == 39)
			asp++;
		if (asp % 2 == 1 && tmp[i] == value)
			tmp[i] = sub;
	}
	tmp = NULL;
}

static	void	get_cmd(t_data *data)
{
	int		i;
	char	*tmp;

	i = -1;
	format_cmd(&data->argv[data->index], 32, 1);
	data->cmd = ft_split(data->argv[data->index], ' ');
	while (data->cmd[++i])
	{
		format_cmd(&data->argv[data->index], 1, 32);
		tmp = data->cmd[i];
		data->cmd[i] = ft_strtrim(tmp, "'");
		ft_free((void *)&tmp);
	}
	data->index++;
}

int	find_cmd(t_data *data)
{
	int		i;
	char	*tmp_path;
	char	*full_path;

	i = -1;
	get_cmd(data);
	while (data->paths[++i])
	{
		tmp_path = ft_strjoin(data->paths[i], "/");
		full_path = ft_strjoin(tmp_path, data->cmd[0]);
		ft_free((void *)&tmp_path);
		if (!access(full_path, F_OK))
		{
			data->path = full_path;
			return (1);
		}
		ft_free((void *)&full_path);
	}
	write(2, data->cmd[0], ft_strlen(data->cmd[0]));
	write(2, ": command not found\n", 20);
	clear(data->cmd, NULL);
	return (0);
}

void	create_path(t_data *data)
{
	int		i;
	char	*envp_paths;

	i = -1;
	while (data->envp[++i])
	{
		envp_paths = ft_strnstr(data->envp[i], "PATH=/", 6);
		if (envp_paths)
		{
			envp_paths = ft_strchr(data->envp[i], '/');
			data->paths = ft_split(envp_paths, ':');
			return ;
		}
	}
}
