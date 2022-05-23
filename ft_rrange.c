#include <stdlib.h>
#include <stdio.h>

int	*ft_rrange(int start, int end)
{
	int	i;
	int	len;
	int	*range;

	if (start > end)
		len = start - end;
	else
		len = end - start;
	range = malloc(sizeof(int) * (len + 1));
	if (!range)
		return (NULL);
	i = 0;
	if (end >= start)
	{
		while (end >= start)
		{
			range[i] = end;
			end--;
			i++;
		}
	}
	else
	{
		while (start >= end)
		{
			range[i] = end;
			end++;
			i++;
		}
	}
	return (range);
}

int	ft_len(int start, int end)
{
	int	len;

	if (start > end)
		len = start - end;
	else
		len = end - start;
	len++;
	return (len);
}

int main(int ac, char **av)
{
	int	*range;
	int	i;
	int	len;

	if (ac != 3)
		return(0);
	range = ft_rrange(atoi(av[1]), atoi(av[2]));
	len = ft_len(atoi(av[1]), atoi(av[2]));
	i = 0;
	while (i < len)
	{
		printf("%d,", range[i]);
		i++;
	}
}