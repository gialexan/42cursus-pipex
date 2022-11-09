/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:54:18 by gialexan          #+#    #+#             */
/*   Updated: 2022/11/09 18:36:01 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear(char **array, char *str)
{
	ft_free_split((void *)array);
	if (str != NULL)
		ft_free((void *)&str);
}

void	check_error(t_data *data, int file, int function, char *cmd)
{
	if (file == -1 && function == -1)
	{
		write(2, ": command not found\n", 20);
		clear(data->cmd, data->path);
		clear(data->paths, NULL);
		exit(EXIT_FAILURE);
	}
	else if (file == -1)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	else if (function == -1)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Error executing command\n", 26);
		exit(EXIT_FAILURE);
	}
}
