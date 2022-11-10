/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:55:57 by gialexan          #+#    #+#             */
/*   Updated: 2022/11/10 17:26:48 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static	void	exec_child(t_data *data)
{
	int	pid;
	int	fd[2];

	check_error(pipe(fd), "pipe");
	pid = fork();
	check_error(pid, "fork");
	if (pid == 0)
	{
		close(fd[0]);
		close(data->file[1]);
		dup2(data->file[0], STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		if (data->path != NULL)
			execve(data->path, data->cmd, NULL);
		else
		{
			clear(data->cmd, data->path);
			clear(data->paths, NULL);
			exit(127);
		}
	}
	close(fd[1]);
	waitpid(pid, NULL, 0);
	clear(data->cmd, data->path);
	data->file[0] = fd[0];
}

static	void	exec_father(t_data *data)
{
	int	pid;

	pid = fork();
	check_error(pid, "fork");
	if (pid == 0)
	{
		dup2(data->file[0], STDIN_FILENO);
		dup2(data->file[1], STDOUT_FILENO);
		if (data->path != NULL)
			execve(data->path, data->cmd, NULL);
		else
		{
			clear(data->cmd, data->path);
			clear(data->paths, NULL);
			exit(127);
		}
	}
	waitpid(pid, NULL, 0);
	close(data->file[0]);
	close(data->file[1]);
	clear(data->cmd, data->path);
	clear(data->paths, NULL);
}

void	start_pipex(t_data *data)
{
	while ((data->index) < data->argc - 2)
	{
		find_cmd(data);
		exec_child(data);
	}
	if (!find_cmd(data))
	{
		clear(data->paths, NULL);
		clear(data->cmd, NULL);
		exit (127);
	}
	exec_father(data);
	exit(EXIT_SUCCESS);
}
