#include <push_swap.h>

void	write_error(char *str)
{
	ft_putstr_fd("Error", 2);
	if (str != NULL)
	{
		ft_putchar(' ');
		ft_putstr_fd(str, 2);
		ft_putchar(' ');
	}
	ft_putstr_fd("\n", 2);
}
void	error_exit(char *str)
{
	write_error(str);
	exit(-1);
}
int skip_whitespaces(const char *st)
{
	int i;

	i = 0;
	while(st[i] == ' ' || st[i] == '\t' || st[i] == '\v' ||
			st[i] == '\f' || st[i] == '\n' || st[i] == '\r')
		i++;
	return (i);
}

void push(STACK *to, int add)
{
	to->top += 1;
	to->stk[(to->top)] = add;
}

void swap_a(INIT_NEXUS)
{
	if (ATOP >= 1)
		F_SWAP(&A->stk[ATOP], &A->stk[ATOP - 1]); //OPPOSITE: ATOP , ATOP - 1
}
void swap_b(INIT_NEXUS)
{
	if (BTOP >= 1)
		F_SWAP(&B->stk[BTOP], &B->stk[BTOP - 1]);
}
void swap_both(INIT_NEXUS)
{
	swap_a(NEXUS);
	swap_b(NEXUS);
}
int pop(STACK *to)
{
	int n;

	n = to->stk[(to->top)];
	to->stk[(to->top)] = 0;
	to->top -= 1;
	return (n);
}

int		push_b(INIT_NEXUS)
{
	if (ATOP >= 0 && (BTOP + 1) < B->limit)
	{
		push(B, pop(A));
		return (1);
	}
	return (-1);
}

int		push_a(INIT_NEXUS)
{
	if (BTOP >= 0 && (ATOP + 1) < A->limit)
	{
		push(A, pop(B));
		return (1);
	}
	return (-1);
}

STACK *malloc_stack(int argc)
{
	STACK *new;

	new = (STACK*)malloc(sizeof(STACK));

	new->top = -1 ;
	new->limit = argc;
	new->stk = (int*)malloc((argc + 1) * sizeof(int));
	return (new);
}

int		check_valid(char *arg)
{
	int i;
	int len;
	int sign_last;
	i = 0;
	sign_last = 0;
	len = ft_strlen(arg);
	if (len < 1)
		return (ZEROLEN);
	while(arg[i] == '\t' || arg[i] == ' ' || arg[i] == '\v'
			|| arg[i] == '\r' || arg[i] == '\b' || arg[i] == '\n')
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		((ft_strlen(&arg[i]) < 2) ? sign_last++ : i++);
	if (sign_last > 0)
		return (INV_ARG);
	i--;
	while (arg[++i])
		if (arg[i] < '0' || arg[i] > '9')
			return (INV_ARG);
	return (1);
}

STACK	*parse_list(int argc, char **args) //executable ALREADY skipped and argc down
{
	STACK *output;
	int		i;

	i = -1;
	output = malloc_stack(argc);
	while (++i < argc)
		push(output, ft_atoi(args[i]));
	return (output);
}

#define SP_PUTNBR(X){ F_PUTNBR(X) ; ft_putchar(' ');}
void	print_stack(STACK *st)
{
	int i;

	if (st == NULL || st->stk == NULL)
		return ;
	i = -1;
	while (++i <= st->top)
		SP_PUTNBR(st->stk[i]);
}

t_push_swap *malloc_nexus(int argc, char **argv)
{
	t_push_swap *output;

	output = (t_push_swap*)malloc(sizeof(t_push_swap));
	output->a = parse_list(argc - 1, argv + 1);
	output->b = malloc_stack(argc - 1);
	output->total = (size_t)output->a->limit;
	return (output);
}

int *rotate_a(INIT_NEXUS)
{
	int size;
	int *tmp;
	size = A->top + 1;
	if (size <= 1)
		return (A->stk);
	tmp = (int*)malloc(size * sizeof(int));
	tmp = (int*)ft_memcpy(tmp, &A->stk[1], ((size - 1) * sizeof(int)));
	tmp[A->top] = (int)(A->stk)[0];
	free(A->stk);
	A->stk = tmp;
	return (tmp);
}

int *revrot_a(INIT_NEXUS)
{
	int size;
	int *tmp;
	int *tmp2;

	size = A->top + 1;
	if (size <= 1)
		return (A->stk);
	tmp = (int*)malloc(size * sizeof(int));
	tmp2 = &tmp[1];
	tmp2 = (int*)ft_memcpy(tmp2, A->stk, ((size - 1) * sizeof(int)));
	tmp[0] = A->stk[A->top];
	free(A->stk);
	A->stk = tmp;
	return (tmp);
}

int *rotate_b(INIT_NEXUS)
{
	int size;
	int *tmp;
	size = B->top + 1;
	if (size <= 1)
		return (B->stk);
	tmp = (int*)malloc(size * sizeof(int));
	tmp = (int*)ft_memcpy(tmp, &B->stk[1], ((size - 1) * sizeof(int)));
	tmp[B->top] = (int)(B->stk)[0];
	free(B->stk);
	B->stk = tmp;
	return (tmp);
}

int *revrot_b(INIT_NEXUS)
{
	int size;
	int *tmp;
	int *tmp2;

	size = B->top + 1;
	if (size <= 1)
		return (B->stk);
	tmp = (int*)malloc(size * sizeof(int));
	tmp2 = &tmp[1];
	tmp2 = (int*)ft_memcpy(tmp2, B->stk, ((size - 1) * sizeof(int)));
	tmp[0] = B->stk[B->top];
	free(B->stk);
	B->stk = tmp;
	return (tmp);
}

void revrot_both(INIT_NEXUS)
{
	A->stk = revrot_a(NEXUS);
	B->stk = revrot_b(NEXUS);
}

void rotate_both(INIT_NEXUS)
{
	A->stk = rotate_a(NEXUS);
	B->stk = rotate_b(NEXUS);
}

int	sorted(INIT_NEXUS)
{
	int i;

	ft_putstr("A: ");
	print_stack(A);
	ft_putchar('\n');
	ft_putstr("B: ");
	print_stack(B);
	ft_putchar('\n');
	if (BTOP >= 0)
		return (FALSE);
	i = ATOP + 1;
	while (--i > 0)
		if (A->stk[i] < A->stk[i - 1])
			return (FALSE);
	return (TRUE);
}

int		read_commands(INIT_NEXUS)
{
	int len;
	char *line;
	
	len = 2;
	while (sorted(NEXUS) != TRUE && len > 1)
	{
		get_next_line(0, &line);
		len = ft_strlen(line);
		if (len == 2 && line[0] == 'p' && (line[1] == 'a' || line[1] == 'b'))
			line[1] == 'a' ? push_a(NEXUS) : push_b(NEXUS);
		else if (len == 2 && line[0] == 's' && line[1] == 's')
			swap_both(NEXUS);
		else if (len == 2 && line[0] == 's' &&
				(line[1] == 'a' || line[1] == 'b'))
			line[1] == 'a' ? swap_a(NEXUS) : swap_b(NEXUS);
		else if (len > 1 && len < 4 && line[0] == 'r')
		{
			if (ft_strcmp("ra", line) == 0 || ft_strcmp("rb", line) == 0)
				line[1] == 'a' ? rotate_a(NEXUS) : rotate_b(NEXUS);
			else if (ft_strcmp("rr", line) == 0 || ft_strcmp("rra", line) == 0)
				LEN(line) >= 3 ? rotate_both(NEXUS) : revrot_a(NEXUS);
			else if (ft_strcmp("rrb", line) == 0 || ft_strcmp("rrr", line) == 0)
				line[2] == 'b' ? revrot_b(NEXUS) : revrot_both(NEXUS);	
		}
		else
			return (-1);
	}
	return (sorted(NEXUS) == TRUE ? 1 : -1);
}


int main(int argc, char **argv)
{
	INIT_NEXUS;
	int temp;
	char **subarg;
	int counter;
	if (argc < 2)
		error_exit(NULL);
	//subarg = (argc == 2 ? ft_strsplit(argv[1], ' ') : argv);
	temp = 0;
	while(++temp < argc)
		if (check_valid(argv[temp]) < 0)
			error_exit(NULL);
	NEXUS = malloc_nexus(argc, argv);
	ft_putstr((read_commands(NEXUS) > 0) ? "OK\n" : "KO\n"); 
	/*A->stk = rotate_a(NEXUS);
	print_stack(A);
	ft_putchar('\n');
	A->stk = revrot_a(NEXUS);
	print_stack(A);
	print_stack(B);
	push_a(NEXUS);
	push_b(NEXUS);
	//print_stack(A);
	push_b(NEXUS);
	push_b(NEXUS);
	ft_putchar('\n');
	print_stack(B);
	print_stack(A);
	rotate_a(NEXUS);
	ft_putchar('\n');
	print_stack(A);
	rotate_b(NEXUS);

	revrot_b(NEXUS);
	return (0);
	char *str;
	int *m;
	int ctoi;
	int tmp;
	ctoi = (sizeof(int) / sizeof(char));
	int n[10] = { 9, 0, 1, 2, 3, 4, 5, 6, 7, 8 };
	int n_size = sizeof(n) / sizeof(*n);
	m = (int*)malloc(n_size * sizeof(int));
    m = (int*)ft_memcpy(m, &n[1], sizeof(n) - (1 * sizeof(*n)));
	m[9] = n[0];

	for (int i = 0; i < 10; i++)
		printf("%d\n", m[i]);*/
	//rotate(&m);
	//for (int i = 0; i < 10; i++)
	//	printf("%d\n", m[i]);
	//str = ft_strndup((char*)(&n[1]), (ctoi * n_size));

	//m[9] = 0 + n[0];
	//for (i = 0; i < 10; i++)
	//	printf("%d\n", m[i]);
//	return(0);
}

