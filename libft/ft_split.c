#include "libft.h"

int	count_words(const char *s, char d)
{
	int	i;
	int	is_word;

	i = 0;
	is_word = 0;
	while (*s)
	{
		if (*s == d)
			is_word = 0;
		else if (!is_word)
		{
			is_word = 1;
			i++;
		}
		s++;
	}
	return (i);
}

void	copy_words(const char *s, char d, char **m)
{
	int			len;
	int			i;
	const char	*start;

	i = 0;
	while (*s)
	{
		while (*s == d && *s != '\0')
			s++;
		if (*s == '\0')
			break ;
		start = s;
		while (*s != d && *s != '\0')
			s++;
		len = s - start;
		m[i] = (char *)malloc((len + 1) * sizeof(char));
		if (m[i] == NULL)
			return ;
		ft_strlcpy(m[i], start, len + 1);
		i++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**result;
	int		wrd;

	if (s == NULL)
		return (NULL);
	wrd = count_words(s, c);
	result = (char **)malloc((wrd + 1) * sizeof(char *));
	if (result == NULL)
		return (NULL);
	result[wrd] = NULL;
	copy_words(s, c, result);
	return (result);
}
