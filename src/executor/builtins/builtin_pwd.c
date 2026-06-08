/* ************************************************************************** */
/*                                                                            */
/*   builtin_pwd.c                                                            */
/*                                                                            */
/*   Prints the absolute path of the current working directory.               */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	builtin_pwd(void)
{
	char	cwd[PATH_MAX];

	if (!getcwd(cwd, PATH_MAX))
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	return (0);
}
