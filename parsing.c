#include "philo.h"

static void	error_parsing(int error, t_data *datas)
{
	ft_putstr_fd(2, " : Wrong input\n");
	if (error == 1)
		ft_putstr_fd(2, "Error: Invalid number of arguments\n");
	if (error == 2)
		ft_putstr_fd(2, "Error: Invalid format of arguments\n");
	if (error == 3)
		ft_putstr_fd(2, "Argument can't be 0 or less\n");
	free(datas);
	exit(1);
}

static int	ft_atoi(char *s, int *sign)
{
	int		i;
	long	nb;

	i = 0;
	*sign = 1;
	nb = 0;
	if (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			*sign *= -1;
		i++;
	}
	while (s[i])
	{
		nb = (nb * 10) + s[i] - 48;
		if (nb * *sign > 2147483647 || nb * *sign < -2147483648
			|| s[i] < '0' || s[i] > '9')
			*sign = 0;
		i++;
	}
	return (nb * *sign);
}

static unsigned int	check_int(char *s, t_data *datas)
{
	int	sign;
	int	nbr;

	sign = 1;
	nbr = ft_atoi(s, &sign);
	if (sign == 0)
	{
		ft_putstr_fd(2, s);
		error_parsing(2, datas);
	}
	else if (nbr <= 0)
	{
		ft_putstr_fd(2, s);
		error_parsing(3, datas);
	}
	return ((unsigned int) nbr);
}

t_data	*parsing(int ac, char **av)
{
	t_data	*datas;

	datas = (t_data *) calloc (1, sizeof(t_data));
	if (!datas)
		exit(1);
	if (ac < 5 || ac > 6)
		error_parsing(1, datas);
	datas->num_philo = check_int(av[1], datas);
	datas->time_to_die = check_int(av[2], datas);
	datas->time_to_eat = check_int(av[3], datas);
	datas->time_to_sleep = check_int(av[4], datas);
	if (ac == 6)
		datas->nb_meals = check_int(av[5], datas);
	else
		datas->nb_meals = -1;
	return (datas);
}

