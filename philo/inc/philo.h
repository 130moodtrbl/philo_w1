/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:26:53 by speters           #+#    #+#             */
/*   Updated: 2025/05/07 15:43:06 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define WNBARGS "\e[1;91mWrong input format!\e[0m: ./philo __ __ __ __ [__]\n"
# define INP "\e[1;91mError:\e[0m Invalid number_of_philosophers!\n"
# define ITTD "\e[1;91mError:\e[0m Invalid time_to_die!\n"
# define ITTE "\e[1;91mError:\e[0m Invalid time_to_eat!\n"
# define ITTS "\e[1;91mError:\e[0m Invalid time_to_sleep!\n"
# define INB "\e[1;91mError:\e[0m Invalid nb_of_times_each_philo_must_eat!\n"
# define BUG_TOD "\e[1;95mIssue:\e gettimeofday() failed (utils.c)\n"
# define ERR_CREATE_THREAD "\e[1;95mIssue:\e failed to create thread\n"
# define BUG_UNIPHIL "\e[1;95mIssue:\e failed to initilise philo\n"
// # define TIMESTAMPS "\033[0;38;5;245m%05lums\e[0m "
# define TIMESTAMPS "\033[0;38;5;245m%lu\e[0m "
# define STATE_FORK "%03d \033[38;5;22mhas taken a fork\e[0m\n"
# define STATE_EAT "%03d \033[38;5;94mis eating\e[0m\n"
# define STATE_SLEEP "%03d \033[38;5;52mis sleeping\e[0m\n"
# define STATE_THINK "%03d \033[38;5;17mis thinking\e[0m\n"
# define STATE_DIE "%03d \033[38;2;101;67;33mdied\e[0m\n"
# define PHILOS_FULL "\n\e[1;37mAll philos have eaten %d plates of 🍝!"

typedef struct s_philos
{
	struct s_table		*table;
	pthread_t			thread;
	pthread_mutex_t		*lock_last_meal;
	pthread_mutex_t		*lock_has_eaten;
	pthread_mutex_t		*lock_meal_count;
	size_t				nb_of_philos;
	size_t				last_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					philo_seat;
	int					is_sleeping;
	int					has_eaten;
	int					*is_dead;
}	t_philos;

typedef struct s_table
{
	pthread_t			table;
	t_philos			*philos;
	pthread_mutex_t		mutex;
	pthread_mutex_t		*lock_is_dead;
	pthread_mutex_t		*lock_has_eaten;
	pthread_mutex_t		*forks;
	unsigned long		starting_time;
	int					death_check;
	int					total_meal;
}	t_table;

/*main & init*/
void	init_invited_philos(t_philos *philos, char **av);
void	init_seat_philos(t_table *table, t_philos *philos, char **av);
void	init_set_table(t_philos *philos, t_table *table, char **av);
void	init_starting_time(t_table *table, t_philos *philos);

/*dinner*/
void	dinner_begin(t_table *table, t_philos *philos, char **av);
void	dinner_over(t_table *table, t_philos *philos, char **av);

/*print*/
void	print_state(t_philos *philo, char *state);

/*routine*/
int		lonely_philo(t_philos *philo);
void	philo_eating(t_philos *philo);
void	philo_sleeping(t_philos *philo);
void	philo_thinking(t_philos *philo);
void	*routine(void *arg);

/*state_checker*/
int		philo_has_starved(t_philos *philo);
int		philo_has_died(t_philos *philo);
int		check_any_philo_dead(t_philos *philos);
int		are_all_philos_full(t_philos *philos);
void	*state_checker(void *arg);

/*parsing*/
long	utils_atoi(char *str);
int		check_for_dig(char *str);
int		check_args(int ac, char **av);

/*utils*/
void	error_msg(const char *msg);
size_t	current_time(void);
size_t	utils_strlen(const char *str);
int		utils_strcmp(char *s1, char *s2);
int		helper_usleep(size_t milisecs);

void	lock_forks(t_philos *philo, pthread_mutex_t *right_fork,
			pthread_mutex_t *left_fork);
void	get_forks(t_philos *philo, pthread_mutex_t **right_fork,
			pthread_mutex_t **left_fork);

#endif
