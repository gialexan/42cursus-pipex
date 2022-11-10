/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:57:13 by gialexan          #+#    #+#             */
/*   Updated: 2022/11/10 14:17:37 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static	void	open_files(t_data *data)
{
	data->file[1] = open (data->argv[data->argc - 1],
			O_WRONLY | O_CREAT | O_TRUNC, 0777);
	check_file(data, 1, data->file[1]);
	data->file[0] = open(data->argv[1], O_RDONLY, 0777);
	check_file(data, 0, data->file[0]);
}

static	void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->index = 2;
	open_files(data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc >= 5)
	{
		init_data(&data, argc, argv, envp);
		create_path(&data);
		start_pipex(&data);
	}
	else
	{
		write(2, "Invalid arguments\n", 18);
		exit(EXIT_FAILURE);
	}
	return (0);
}
