#include "../pipex.h"

void	printdata(t_pipex data)
{
	for (int i = 0; data.alloc.paths[i]; i++)
		printf("path %d = %s\n", i + 1, data.alloc.paths[i]);
	write(1, "\n", 1);
	for (int i = 0; data.alloc.cmdpaths[i]; i++)
		printf("cmdpath %d = %s\n", i + 1, data.alloc.cmdpaths[i]);
	write(1, "\n", 1);
	printf("data.file1 = %s\n", data.file1);
	write(1, "\n", 1);
	printf("data.deli = %s\n", data.deli);
	write(1, "\n", 1);
	printf("data.file2 = %s\n", data.file2);
	write(1, "\n", 1);
	for (int x = 0; data.alloc.spcmd[x]; x++)
	{
		printf("data.cmd[%d]:\n", x);
		for (int y = 0; data.alloc.spcmd[x][y]; y++)
		{
			printf("  word[%d] = %s\n", y, data.alloc.spcmd[x][y]);
		}
		write(1, "\n", 1);
	}
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}