#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdbool.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data {
	int				num_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	nb_meals;
	unsigned long	start_time;
}	t_data;

typedef struct s_philo {
	pthread_t			philo_thread;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*pprint;
	pthread_mutex_t		*iinfo;
	bool				start;
	bool				fork;
	bool				eat;
	bool				sleep;
	bool				think;
	bool				alive;
	int					meals_eaten;
	unsigned int		id;
	unsigned long		last_meal;
	struct s_philo		*previous;
	t_data				*datas;
}	t_philo;

typedef struct s_state{
	pthread_mutex_t	print;
	pthread_mutex_t	info;
	pthread_t		monitor;
	t_data			*datas;
	t_philo			*philos;
	int				done_eat;
	int				philos_created;
	int				end;
}	t_state;

t_data			*parsing(int ac, char **av);
void			ft_putstr_fd(int fd, char *s);
void			*ft_calloc(size_t n, size_t size_of);
unsigned long	get_start_time(void);
unsigned long	get_time(unsigned long start);
int				get_fork(t_state *state, t_philo *philo, int previous);
int				get_last_meal(t_philo *philo, int status);
int				set_meal(t_philo *philo, int status);
int				set_fork(t_philo *philo, int status);
int				set_start(t_philo *philo, int status);
int				get_alive(t_philo *philo, int status);
int				get_created(t_state *state, int status);
void			create_philos(t_state *state);
void			init_philos(t_state *state);
void			previous_philo(t_state *state);
void			join_philos(t_state *state);
void			kill_philo(t_philo *philo);
void			kill_philos(t_state *state);
void			error_philo(t_state *state, char *msg);
void			*check_alive(void *state);
void			*routine(void *philo);
void			ft_usleep(t_philo *philo, size_t time);
void			print_fork(t_philo *philo, int status);
void			print_infos(t_philo *philo, int status);
void			print_end(t_state *state, int status);
void			set_datas(t_state *state, t_philo *philo, int id);
void			free_state(t_state *state);
#endif

