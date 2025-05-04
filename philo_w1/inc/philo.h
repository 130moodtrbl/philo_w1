/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: speters <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:57:55 by speters           #+#    #+#             */
/*   Updated: 2025/05/04 19:32:15 by speters          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

/*error msgs*/
# define WNBARGS "\e[1;91mWrong input format!\e[0m: ./philo __ __ __ __ [__]\n"
# define INP "\e[1;91mError:\e[0m Invalid number_of_philosophers!\n"
# define ITTD "\e[1;91mError:\e[0m Invalid time_to_die!\n"
# define ITTE "\e[1;91mError:\e[0m Invalid time_to_eat!\n"
# define ITTS "\e[1;91mError:\e[0m Invalid time_to_sleep!\n"
# define INB "\e[1;91mError:\e[0m Invalid nb_of_times_each_philosopher_must_eat!\n"
# define BUG_TOD "\e[1;95mIssue:\e gettimeofday() failed (utils.c)\n" /*mettre le bon*/
# define ERR_CREATE_THREAD "\e[1;95mIssue:\e failed to create thread\n"
# define BUG_UNIPHIL "\e[1;95mIssue:\e failed to initilise philo\n"

/*structure philos, table*/
typedef struct s_philos
{
	struct s_table		*table;
	pthread_t		thread; /* tread individuel pour exécuter la routine, */
	pthread_mutex_t	*lock_last_meal;  /* ptr → dernier repas du philo, et le 🔒*/
	pthread_mutex_t	*lock_has_eaten;  /* ptr → avec s_table, 🔒  has_eaten*/
	size_t			nb_of_philos;  /* pour les calculs et la gestion des datas */
	size_t			last_meal;  /*qd était le dernier repas (en ms depuis le debs*/
	size_t			time_to_die;  /*en ms avant mort si pas mangé (w last_meal)*/
	size_t			time_to_eat;  /*ms, duree du repas*/
	size_t			time_to_sleep;  /*ms, durée du sommeil*/
	int				philo_seat; /*id of philo, ou seat*/
	int				is_sleeping;  /*si le philo dort ou pas*/
	int				has_eaten;  /*si le philo a mangé, objectif repas*/
	int				*is_dead;  /*ptr → death_check de s_table*/
}	t_philos;

typedef struct s_table
{
	pthread_t		table;  /*thread posix principal, supervise la table, MONITOR*/
	t_philos		*philos; /*-> vers un tableau de philosophers*/
	pthread_mutex_t	mutex;  /*mutex(🔒) générique, lock les data partagées*/
	pthread_mutex_t	*lock_is_dead; /*ptr →(🔒) qui handle a la mort (is_dead flag..)*/
	pthread_mutex_t	*lock_has_eaten;  /*ptr → (🔒) les infos sur le repas (nb of meals…)*/
	pthread_mutex_t	*forks;  /*ptr → 🔒 tab qui lock les forks de chaque philo (L/R) */
	unsigned long			starting_time;  /*demarrage de la simulation*/
	int				death_check;  /*si philo dead, fin de simulation, BOOL?*/
	int				total_meal;  /*BONUS??*/
}	t_table;

/*parsing*/
int		check_args(int ac, char **av);
int		check_for_dig(char *str);
long	utils_atoi(char *str);

/*utils, time*/
size_t     current_time(void);
int     helper_usleep(size_t milisecs);
size_t	utils_strlen(const char *str);
void	error_msg(const char *msg);
void	print_state(t_philos *philo, char *str);
int utils_strcmp(char *s1, char *s2);

/*init*/
void	init_invited_philos(t_philos *philos, char **av);
void	init_seat_philos(t_table *table, t_philos *philos, char **av);
void	init_set_table(t_philos *philos, t_table *table, char **av);
void	dinner_begin(t_table *table, t_philos *philos, char **av);
void	dinner_over(t_table *table, t_philos *philos, char **av);

/*state_checker*/
int	is_philo_still_alive(t_philos *philo);
int	is_philo_starved(t_philos *philo);
int	is_philo_dead(t_philos *philo);
int	is_philo_full(t_philos *philo);
void	*state_checker(void *arg);

/*routine*/
int	lonely_philo(t_philos *philo);
void	philo_eating(t_philos *philo);
void	philo_sleeping(t_philos *philo);
void	philo_thinking(t_philos *philo);
void *routine(void *arg);

#endif