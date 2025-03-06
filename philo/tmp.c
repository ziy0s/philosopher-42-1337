// void	six_args(char *v[], t_philo **ptr)
// {
// 	ptr = ft_malloc(sizeof(t_philo));
// 	ptr->num_philo = ft_atoi(v[1]);
// 	if (ptr->num_philo < 2 || ptr->num_philo > 200)
// 		ft_exit(1);
// 	ptr->time_die = ft_atoi(v[2]);
// 	if (ptr->time_die < 60)
// 		ft_exit(1);
// 	ptr->time_eat = ft_atoi(v[3]);
// 	if (ptr->time_eat < 60)
// 		ft_exit(1);
// 	ptr->time_sleep = ft_atoi(v[4]);
// 	if (ptr->time_sleep < 60)
// 		ft_exit(1);
// 	ptr->num_eat = ft_atoi(v[5]);
// 	if (ptr->num_eat < 1)
// 		ft_exit(1);
// }

// void	*eat(void *arg)
// {
// 	t_philo	*ptr;

// 	ptr = (t_philo *) arg;
// 	pthread_mutex_lock(ptr->l_fork);
// 	printf("%llu the philo %d has tak the lift fork !\n", ptr->start, ptr->id);
// 	pthread_mutex_lock(ptr->r_fork);
// 	printf("%llu the philo %d has tak the right fork !\n", ptr->start, ptr->id);
// 	pthread_mutex_lock(&ptr->data->eating_mutex);
// 	printf("%llu the philo %d has start eating !\n", ptr->start, ptr->id);
// 	usleep(ptr->data->time_eat * 1000);
// 	pthread_mutex_unlock(&ptr->data->eating_mutex);
// 	ptr->start = ptr->data->time_eat * 1000;
// 	printf("%llu the philo %d has finish eating !\n", ptr->start, ptr->id);
// 	pthread_mutex_unlock(ptr->r_fork);
// 	printf("%llu the philo %d has live the lift fork !\n", ptr->start, ptr->id);
// 	pthread_mutex_unlock(ptr->l_fork);
// 	printf("%llu the philo %d has live the right fork !\n", ptr->start, ptr->id);
// 	return (NULL);
// }

// void	creat_threads(t_data	**ptr)
// {
// 	t_data *tmp;
// 	int i;
// 	// int *num;

// 	tmp = *ptr;
// 	i = 0;
// 	pthread_mutex_init(&tmp->eating_mutex, NULL);
// 	while (i < tmp->num_philo)
// 	{
// 		tmp->id = ft_malloc(sizeof(int));
// 		*tmp->id = i + 1;
// 		printf("%d\n", *tmp->id);
// 		pthread_mutex_init(&tmp->forks[i], NULL);
// 		pthread_mutex_init(&tmp->forks[(i + 1) % tmp->num_philo], NULL);
// 		pthread_create(&tmp->philo[i].thread, NULL, &eat, &tmp->philo[i]);
// 		// free(ptr->id);
// 		i++;
// 	}
// 	i = 0;
// 	while (i < tmp->num_philo)
// 	{
// 		pthread_join(tmp->thread[i], NULL);
// 		i++;
// 	}
// }

// unsigned long get_time(void) {
//     struct timeval tv;
//     gettimeofday(&tv, NULL);
//     return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
// }

// void init_philo(t_data *data) {
//     data->philo = ft_malloc(sizeof(t_philo) * data->num_philo);
//     // data->forks = ft_malloc(sizeof(pthread_mutex_t) * data->num_philo);
    
//     for (int i = 0; i < data->num_philo; i++) {
//         data->philo[i].id = i + 1;
//         pthread_mutex_init(&data->forks[i], NULL);
//         data->philo[i].l_fork = &data->forks[i];
//         data->philo[i].r_fork = &data->forks[(i + 1) % data->num_philo];
//         data->philo[i].data = data;
//     }
//     data->start =0;
// }