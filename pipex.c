/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:08:48 by rgiambon          #+#    #+#             */
/*   Updated: 2024/08/15 11:24:21 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*execution(char *cmd, char **envp)
{
	char	**cmd_tab;
	char	*path;

	cmd_tab = create_cmd_tab(cmd, envp);
	path = path_finder(cmd_tab[0], envp);
	if (path == NULL)
	{
		free_all(cmd_tab);
		perror("Path finding failed.");
		exit(EXIT_FAILURE);
	}
	if (execve(path, cmd_tab, envp) == -1)
	{
		perror("Execution failed failed.");
		free(path);
		free(cmd_tab);
		exit(EXIT_FAILURE);
	}
	free(path);
	free_all(cmd_tab);
}

void	open_and_check(int argc, char *argv[], int *fd1, int *fd2)
{
	if (argc != 5)
	{
		write(2, "Error: wrong number of arguments", 32);
		exit(EXIT_FAILURE);
	}
	*fd1 = open(argv[1], O_RDONLY);
	if (*fd1 < 0)
	{
		perror("Error opening file1");
		exit(EXIT_FAILURE);
	}
	*fd2 = open(argv[4], O_WRONLY | O_CREATE | O_TRUNC, 0777);
	if (fd2 < 0)
	{
		perror("Error opening file2");
		exit(EXIT_FAILURE);
	}
}

void	child_process(char *cmd1, int file_fd, int *pipe_fds, char **envp)
{
	dup2(file_fd, 0);
	dup2(pipe_fds[1], 1);
	close(pipe_fds[0]);
	execution(cmd1, envp);
}

void	parent_process(char *cmd2, int file_fd, int *pipe_fds, char **envp)
{
	int	child_status;

	wait(&child_status);
	dup2(file_fd, 1);
	dup2(pipe_fds[0], 0);
	close(pipe_fds[1]);
	execution(cmd2, envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		fd_file1;
	int		fd_file2;
	int		pipe_fds[2];
	pid_t	id;

	open_and_check(argc, argv, &fd_file1, &fd_file2);
	if (pipe(pipe_fds) < 0)
	{
		perror("Pipe creation failed");
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == -1)
	{
		perror("Fork system call failed.");
		exit(EXIT_FAILURE);
	}
	if (id == 0)
		child_process(argv[2], fd_file1, pipe_fds, envp);
	else
		parent_process(argv[3], fd_file2, pipe_fds, envp);
	return (0);
}
