/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 11:08:48 by rgiambon          #+#    #+#             */
/*   Updated: 2024/08/13 13:06:44 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	error_check(int argc, char *argv[], int *fd1, int *fd2)
{	
	if (argc != 5)
	{
		write(2, "Error: wrong number of arguments", 32);
		exit(EXIT_FAILURE);
	}
	*fd1 = open(argv[1], O_RDONLY);
	if(*fd1 < 0)
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

void	child_process(char *cmd1, int file_fd)
{
	//redirect input from standard to infile
	dup2(0, file_fd);
	//execute cmd1 on input file, you need:
	//split command and arguments
	//find the path of the command
	//create argv with: [0] = path, [1] - [n] = the arguments, [last] = NULL
	//call execve

void	parent_process();

int	main(int argc, char *argv[], char *envp[])
{
	int		fd_file1;
	int		fd_file2;
	int		pipe_fds[2];
	pid_t	id;

	error_check(argc, argv, &fd_file1, &fd_file2);
	if (pipe(pipe_fds < 0))
	{
		perror("Pipe creation failed");
		exit(EXIT_FAILURE);
	}
	id = fork();
	if (id == 0)
		child_process(argv[2], fd_file1, envp)

				
