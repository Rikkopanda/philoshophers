/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rverhoev <rverhoev@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 12:34:50 by rik               #+#    #+#             */
/*   Updated: 2024/01/16 13:30:42 by rverhoev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# define _GNU_SOURCE
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <semaphore.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <error.h>
# include <string.h>
# include <errno.h>
# include <signal.h>
# include <features.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/mman.h>

# define PHILO_DIED_ERROR 1
# define END_SIGNAL 10

# define NEVER_REACHES_THIS -2
# define DONE_EATING 3
# define DIED 1

typedef struct s_philo	t_philo;

typedef struct s_data
{
	char			*forks_sem_name;
	char			*print_sem_name;
	char			*died_sem_name;
	char			*stop_sem_name;
	int				fork_n;
	int				n_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_times_to_eat_philo;
	t_philo			*philos_ptr;
	pid_t			*pids;
	sem_t			*forks_sem;
	sem_t			*print_sem;
	sem_t			*died_sem;
	int				*stop_bool_shared;
}	t_data;

struct s_philo
{
	int				philo_nbr;
	int				holding_one_fork;
	int				done_bool;
	unsigned int	start_time;
	unsigned int	current_time;
	unsigned int	next_meal;
	int				eat_counter;
	int				nbr_of_times_eaten;
	pthread_t		monitor_th_id;
	char			nbr_str1[1000];
	char			nbr_str2[1000];
	int				print_len[2];
	char			*current_time_sem_name;
	char			*done_sem_name;
	char			*next_meal_sem_name;
	char			*eat_cnt_sem_name;
	sem_t			*current_time_sem;
	sem_t			*done_sem;
	sem_t			*next_meal_sem;
	sem_t			eat_cnt_sem;
	pid_t			pid;
	int				status;
	t_data			*data;
};

// philo
int				philo_process(int process_i, t_data *data);
void			phil_eat(t_philo *philo, struct timeval *tv);
int				phil_pick_forks(t_philo *philo, t_data *data,
					struct timeval *tv);
// philo helper functions
void			init_philo_data1(t_philo *philo, t_data *data, int *process_i);
void			init_philo_data2(t_philo *philo, struct timeval *tv);
void			free_inherited_data(t_data *data);
void			free_philo_data(t_philo *philo);
int				personal_semaphores(t_philo *philo);

// monitoring
void			*monitoring(void *ptr);
int				check_died(t_data *data);
void			assign_time_since_last_meal(t_philo *philo, struct timeval *tv);
void			when_died(t_philo *philo, struct timeval *tv);
void			when_enough(t_philo *philo);

// init main process
int				init_data(t_data *data, int argc, char **argv);
int				init_semaphores(t_data *data);

// terminating
void			destroy_one(t_data *data, pid_t ret_pid,
					pid_t *already_destroyed_or_done);
void			clean_up(t_data *data);
void			wait_for_child_processes(t_data *data);

// helper functions
void			printfunc(t_philo *philo, struct timeval *tv, char *print_str);
unsigned int	get_time(struct timeval *tv);
int				check_stop(t_philo *philo);
void			free_data(t_data *data);

// sem helper functions
void			make_semaphore(char **sem_name_ptr,
					char nbr_str[1000], char *name);
void			open_named_semaphore(sem_t **sem_ptr,
					char **sem_name_ptr, int value);

// standard functions
int				ft_utoa_1000(unsigned int num, char str[1000]);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
void			ft_strcpy(char *dest, const char *src);
char			*ft_strcat(char *dest, char *src);

#endif
