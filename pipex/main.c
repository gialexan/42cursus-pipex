/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gialexan <gialexan@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 14:57:13 by gialexan          #+#    #+#             */
/*   Updated: 2022/11/03 21:38:38 by gialexan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clear(char **array, char *str)
{
	ft_free_split((void *)array);
	if (str != NULL)
		ft_free((void *)&str);
}

void	check_error(int file, int function, char *cmd)
{
	if (file == -1)
	{
		perror("");
		exit(1);
	}
	if (function == -1)
	{
		write(2, cmd, ft_strlen(cmd));
		write(2, ": Error executing command\n", 26);
		exit(1);
	}
}

void	open_files(t_data *data)
{
	data->file[0] = open(data->argv[1], O_WRONLY, 0777);
	check_error(data->file[0], 0, NULL);
	if (data->file[1] == -1)
		data->file[1] = open(data->argv[data->argc - 1],
						O_WRONLY | O_CREAT | O_TRUNC, 0777);
	check_error(data->file[1], 0, NULL);
}

void	init_data(t_data *data, int argc, char **argv, char **envp)
{
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->index = 2;
	data->file[1] = -1;
	open_files(data);
}

void	format_cmd(char **str, int value, int sub)
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

void	get_cmd(t_data *data)
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
	get_cmd(data); // pega o comando
	while (data->paths[++i])
	{
		tmp_path = ft_strjoin(data->paths[i], "/"); //arrumar path com comando
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
	while(data->envp[++i]) // gera o PATH
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

void	exec_child(t_data *data)
{
	int pid;
	int fd[2];
	int	status;

	check_error(0, pipe(fd), "pipe"); //verifica erro ao abrir pipe
	pid = fork();
	check_error(0, pid, "fork"); //verifica erro ao iniciar fork
	if (pid == 0) //processo filho
	{
		close(fd[0]); // fechando leitura pipe pq n vou lê nd
		close(data->file[1]); // fechando escritor do arquivo pq n vou escrever nd
		dup2(data->file[0], STDIN_FILENO); // aponta que file descriptor de leitura do arquivo é o file descriptor de entrada dados
		dup2(fd[1], STDOUT_FILENO); //aponta que STDOUT(saida principal) seja a do pipe
		execve(data->path, data->cmd, NULL);
	}
	close(fd[1]); //fecha file descriptor do escrita do pipe
	waitpid(pid, &status, 0); // processo pai espera
	clear(data->cmd, data->path);
	if (status)
	{
		clear(data->paths, NULL);
		exit(1);
	}
	data->file[0] = fd[0];
}

void	exec_father(t_data *data)
{
	int	pid;
	int	status;

	pid = fork();
	check_error(0, pid, "fork");
	if (pid == 0)
	{
		dup2(data->file[0], STDIN_FILENO);
		dup2(data->file[1], STDOUT_FILENO);
		execve(data->path, data->cmd, NULL);
	}
	waitpid(pid, &status, 0);
	close(data->file[0]);
	close(data->file[1]);
	clear(data->cmd, data->path);
	clear(data->paths, NULL);
	if (status)
		exit(1);
}

void	start_pipex(t_data *data)
{
	while ((data->index + 2) < data->argc)
	{
		if (find_cmd(data) == 1)
			exec_child(data);
	}
	if (find_cmd(data) == 0)
	{
		clear(data->paths, NULL);
		exit (1);
	}
	exec_father(data);
	exit(0);
}

int main (int argc, char **argv, char **envp)
{
	t_data data;
	int i;
	if (argc >= 5)
	{
		init_data(&data, argc, argv, envp);
		create_path(&data);
		start_pipex(&data);
	}
	else
	{
		printf("Erro 1");
		exit(1);
	}
	return (0);
}