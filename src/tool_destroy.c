/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tool_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:54:18 by gialexan          #+#    #+#             */
/*   Updated: 2022/11/10 14:31:44 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear(char **array, char *str)
{
	ft_free_split((void *)array);
	if (str != NULL)
		ft_free((void *)&str);
}

void	check_error(int function, char *cmd)
{
	if (function == -1)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Error executing command\n", 26);
		exit(EXIT_FAILURE);
	}
}

void	check_file(t_data *data, int file_index, int file)
{
	if (file_index == 0 && file == -1)
	{
		if (!access(data->argv[1], F_OK))
	 		exit(EXIT_SUCCESS);
		else
	   		exit(EXIT_FAILURE);
	}
	else if (file_index == 1 && file == -1)
		exit(EXIT_FAILURE);
		
}
