/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:33:52 by rverhoev          #+#    #+#             */
/*   Updated: 2024/01/17 12:46:29 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef WAIT_PHILO
#  define WAIT_PHILO 4000
# endif
# ifndef GETTING_OUT_OF_BED
#  define GETTING_OUT_OF_BED 100
# endif
# define PHILO_DIED_ERROR 1
# define END_SIMULATION 1
# define NEVER_REACHES_THIS -2
# define ONLY_ONE_PHILO 1

typedef struct s_philo	t_philo;

typedef struct s_fork
{
	pthread_mutex_t	lock;
	int				init_bool;
}	t_fork;

typedef struct s_data
{
	int				n_of_philos;
	int				time_to_die;
	int				died_bool;
	int				cnt_to_start_th;
	int				time_to_eat;
	unsigned int	start_time;
	int				time_to_sleep;
	int				n_times_to_eat_philo;
	t_fork			*forks_ptr;
	pthread_t		monitor_th_id;
	struct timeval	monitor_tv;
	t_philo			*philos_ptr;
	int				end;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*die_lock;
	pthread_mutex_t	*time_since_meal;
	pthread_mutex_t	*done_lock;
	pthread_mutex_t	*cnt_to_start_th_lock;
	pthread_mutex_t	*start_time_lock;
}	t_data;

struct s_philo
{
	pthread_t		th_id;
	int				philo_nbr;
	t_fork			*left_fork;
	t_fork			*right_fork;
	char			nbr_str1[1000];
	char			nbr_str2[1000];
	int				print_len[2];
	int				done_bool;
	char			*phi_nb_str[3];
	unsigned int	last_meal_ms;
	unsigned int	start_time;
	unsigned int	current_time;
	int				eat_counter;
	int				nbr_of_times_eaten;
	int				time_since_meal;
	t_data			*data;
};

// philo thread routine
void	*routine(void *voidptr);
// philo thread actions
int		try_pick_forks(t_philo *philo, struct timeval *tv,
			int what_lock_sequence);
void	phil_sleep(t_philo *philo, struct timeval *tv);
int		phil_eat(t_philo *philo, struct timeval *tv);
// philo thread helper functions
void	set_data_philo(t_philo *philo);
void	assign_time_since_last_meal(t_philo *philo, struct timeval *tv);
void	assign_fork_ptrs(t_philo *philo);
void	unlock_both(t_philo *philo);
int		check_continue(t_philo *philo);

// make philos
int		create_philos(t_philo **philos, t_data *data);

// inits
void	init_data(t_philo **philos, t_data *data);
int		init_locks(t_fork *forks, t_data *data);
int		init_args_data(t_data *data, int argc, char **argv);

// joining threads
void	join_philos(t_philo *philos, int n_of_philos);

// monitoring thread
void	*monitoring(void *ptr);

// monitoring helper functions
int		check_if_die(t_philo *philo, t_data *data);
int		check_if_done(t_philo *philo);
int		printfunc_monitor(t_philo *philo, struct timeval *tv,
			char *print_str);
// printing
void	printfunc(t_philo *philo, struct timeval *tv, char *print_str);
//void	printfunc2(t_philo *philo, char *print_str);
void	writing(char nbr_str1[1000], char nbr_str2[1000],
			char *print_str, int print_len[2]);

// standard functions
int		ft_utoa_1000(unsigned int num, char str[1000]);
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *s);

#endif
