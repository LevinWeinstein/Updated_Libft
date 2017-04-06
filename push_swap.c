#ifdef STACK
# undef STACK
#endif

#ifdef TRUE
# undef TRUE
#endif

#ifdef FALSE
# undef FALSE
#endif

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

#define HUB_NAME hub
#define MAKE_HUB t_strlen HUB_NAME
#define CPTR HUB_NAME.cptr
#define LPTR HUB_NAME.lptr
#define LWRD HUB_NAME.lword
#define BTMG HUB_NAME.bitmagic
#define HIMG HUB_NAME.himagic
#define LOMG HUB_NAME.lomagic
#define CP HUB_NAME.dp

typedef struct s_strlen{
	const char			*cptr;
	const unsigned long	*lptr;
	unsigned long		lword;
	unsigned long		bitmagic;
	unsigned long		himagic;
	unsigned long		lomagic;

	char				*dp;
}				t_strlen;
size_t ft_strlen(const char *str);
void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_putstr_fd(int fd, char *str);

#define STACK t_stack
#define NODE t_stack*
#define MACROLEN(X) ((sizeof(X) / sizeof(char)) - 1)
#define LEN(X) ft_strlen(X)
# define TRUE 1
# define FALSE 0
#define INV_ARG -1
#define EMPTY -1
#define NO_ARGS -2
#define ZEROLEN -3
#define FOR_GCC -42
#define HI 0
#define LO 1

#define F_PUTNBR(X){\
	typeof(X)pntmp; pntmp = X;\
	typeof(X)pntmp2; pntmp2 = X;\
	__INNER_PUTNBR(pntmp, pntmp2);\
}

#define __INNER_PUTNBR(NBR, TMP){\
	___HELPER_HANDLE_NEG(NBR, TMP);\
	NBR = TMP;\
	TMP = 1;\
	while ((NBR / TMP) > 0)\
		TMP *= 10;\
	while ((TMP /= 10) >= 1){\
		ft_putchar('0' + ((NBR/ TMP) % 10));\
	};\
}

#define ___HELPER_HANDLE_NEG(IN, OUT) {\
	if (IN < 0){ ft_putchar('-'); OUT = (IN * -1);}\
	else (OUT = IN); if (OUT == 0) ft_putchar('0'); }\

#define NEXUS midpoint
#define A NEXUS->a
#define B NEXUS->b
#define INIT_NEXUS t_push_swap *midpoint
#define SIZE NEXUS->size
#define ATOP A->top
#define BTOP B->top
#define F_SWAP(P, Q){ typeof((*P))r; r = *P; *P = *Q; *Q = r; }

#define OP_STRLEN(STR) ft_strlen(STR)
#define FULL_LEN(STR, STR2) (OP_STRLEN(STR) + OP_STRLEN(STR2))
#define SIZE_MALLOC(STR, STR2) (char*)malloc((FULL_LEN(STR, STR2) + 1) * sizeof(char))
#define ZERO_OUT(STR){ int n; (n = sizeof(STR)); while(--n >= 0){ STR[n] = 0;};}

#define COPY_INTO(FROM, INTO, I, J){ if ((*J) == 0){ ZERO_OUT(*INTO); } (*I = 0);\
	while((*I < OP_STRLEN(FROM))){ F_PUTNBR(*I); F_PUTNBR(*J); puts("\n"); ((*INTO)[((*J))]) = (FROM[(*I)]) ; (*I)++; (*J)++; };}

#define REAL_CAT(LEFT, RIGHT, BLANK){ *BLANK = SIZE_MALLOC(LEFT, RIGHT); ZERO_OUT(*BLANK); int i[2] = {0, 0};\
	COPY_INTO(LEFT, BLANK, &i[0], &i[1]); COPY_INTO(RIGHT, BLANK, &i[0], &i[1] ); }

#ifndef MAX
# define MAX(X, Y)  X > Y ? X : Y
#endif

#ifndef MIN
# define MIN(X, Y) X < Y ? X : Y
#endif

void	ft_putchar(char c)
{
	write(1, &c, 1);
}
void	ft_putstr_fd(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}
static void init_bits(unsigned long *bit, unsigned long *hi, unsigned long *lo)
{
	*bit = 0x7efefeffL;
 	*hi = 0x80808080L;
	*lo = 0x01010101L;
}

static void change_bits(unsigned long *bit, unsigned long *hi, unsigned long *lo)
{
	*bit = ((0x7efefefeL << 16) << 16) | 0xfefefeffL;
 	*hi = (((*hi) << 16) << 16) | (*hi);
	*lo = (((*lo) << 16) << 16) | (*lo);
}

static int	first_zero(char *copy, int start, int top)
{
	while (start < top)
		if (copy[start++] == 0)
			return (start - 1);
	return (INV_ARG);
}

static void	do_nothing(void)
{
	return ;
}

size_t	ft_strlen(const char *str)
{
	MAKE_HUB;
	int tmp;

	if ((CPTR = str) == NULL)
		return (0);
	while (((unsigned long)CPTR & (sizeof(LWRD) - 1)) != 0)
		if (*CPTR  == '\0' || *(CPTR++) == 4 + *(CPTR) )
			return(CPTR - str); 
	LPTR = (unsigned long*)CPTR;
	init_bits(&BTMG, &HIMG, &LOMG);
	sizeof(LWRD) > 4 ? change_bits(&BTMG, &HIMG, &LOMG) : do_nothing();
	while (TRUE)
	{
		LWRD = *LPTR++;
		if ( ((LWRD - LOMG) & HIMG) != 0 )
		{
			CP = (char*)(LPTR - 1);
			if ((tmp = first_zero(CP, 0, 4)) > INV_ARG)
				return CP + tmp - str;
			if (sizeof(LWRD) > 4 && (tmp = first_zero(CP, 4, 8)) >= 4)
				return CP + tmp - str;
		}
	}
	return (FOR_GCC);
}

/*
** End silly strlen
*/
static char *zero(void)
{
	char *output;

	output = (char*)malloc(sizeof(char));
	output[0] = '\0';
	return (output);
}
char *ft_strndup(const char *s1, size_t n)
{
	size_t i;
	char *output;

	i = 0;
	output = (char*)malloc((n + 1) * sizeof(char));
	if (!output)
		return (NULL);
	while(s1[i] && i < n)
	{
		output[i] = s1[i];
		i++;
	}
	while (i <= n)
		output[i++] = '\0';
	return (output);
}
int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	if (s1 == NULL && s2 == NULL)
		return (0);
	else if (s1 == NULL || s2 == NULL)
		return ((s1 == NULL) ? 0 - s2[0] : s1[0]);
	i = -1;
	while(++i != -1 && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
		;
	return(s1[i] - s2[i]);		
}

void	write_error(char *str)
{
	ft_putstr_fd(2, "Error: ");
	ft_putstr_fd(2, str);
	ft_putstr_fd(2, " \n");
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
int		ft_atoi(const char *s)
{
	int index;
	int output;
	int negative;

	output = 0;
	index = skip_whitespaces(s);
	if (ft_strlen(&s[index])== 1 && (s[index] == '-' || s[index] == '+'))
		error_exit("Invalid Number");
	if (ft_strcmp(&s[index], "-2147483648") == 0)
		return (-2147483648);
	negative = ((s[index]) == '-' ? -1 : 1);
	if ((s[index]== '+' || s[index] == '-'))
		index++;
	while (s[index] != '\0' && s[index] >= '0' && s[index] <= '9')
		output = ((output * 10) + (s[index++] - '0'));
	return (output * negative);
}





//End Libft Pseudosection
typedef struct s_stack	t_stack;
struct					s_stack{
	int					*stk;
	
	int					top;
	int					limit;
};

typedef struct	s_push_swap{
				STACK *a;
				STACK *b;

				size_t total;
}				t_push_swap;

void push(STACK *to, int add)
{
	to->top += 1;
	to->stk[(to->top)] = add;
}

void swap_a(INIT_NEXUS)
{
	if (ATOP >= 1)
		F_SWAP(&A->stk[ATOP], &A->stk[ATOP - 1]);
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

int		push_a(INIT_NEXUS)
{
	if (ATOP >= 0 && (BTOP + 1) < B->limit)
	{
		push(B, pop(A));
		return (1);
	}
	return (-1);
}

int		pp_a(INIT_NEXUS)
{
	if (ATOP >= 1 && (BTOP + 2) < B->limit)
	{
		push(B, pop(A));
		push(B, pop(A));
		return (1);
	}
	return (-1);
}

int		push_b(INIT_NEXUS)
{
	if (BTOP >= 0 && (ATOP + 1) < A->limit)
	{
		push(A, pop(B));
		return (1);
	}
	return (-1);
}

int		pp_b(INIT_NEXUS)
{
	if (BTOP >= 1 && (ATOP + 2) < A->limit)
	{
		push(A, pop(B));
		push(A, pop(B));
		return (1);
	}
	return (-1);
}

void	int_swap(int *p, int *q)
{
	int r;

	r = *p;
	*p = *q;
	*q = r;
}

void swap(STACK *to)
{
	if (to->top >= 1)
		int_swap(&to->stk[to->top], &to->stk[to->top - 1]);
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




#include <string.h>
#include <stdlib.h>



char	*ft_strdup(char *str)
{
	int len;
	char *output;

	if((len = ft_strlen(str)) <= 0)
		return (str == NULL ? NULL : zero()); 
	output = (char*)malloc(sizeof(char) * (len + 1));
	output[len] = '\0';
	while(--len >= 0)
		output[len] = str[len];
	return (output);
}

void	ft_putstr(char *str)
{
	ft_putstr_fd(1, str);
}

void	print_stack(STACK *st)
{
	int i;

	if (st == NULL || st->stk == NULL)
		return ;
	i = -1;
	while (++i <= st->top)
		F_PUTNBR(st->stk[i]);
}


//void print_nexus(INIT_NEXUS)
//{
//	int length;
//	int i;
//
//	length = MAX(ATOP, BTOP) + 1;
//	i = 0;
//	while(i < length)
//		if (i <= ATOP)
t_push_swap *malloc_nexus(int argc, char **argv)
{
	t_push_swap *output;

	output = (t_push_swap*)malloc(sizeof(t_push_swap));
	output->a = parse_list(argc - 1, argv + 1);
	output->b = malloc_stack(argc - 1);
	output->total = (size_t)output->a->limit;
	return (output);
}

void *ft_memcpy(void *dst, const void *src, size_t n)
{
	char *temp;
	char *temp1;

	if (n == 0 || dst == src)
		return (dst);
	temp = (char*)dst;
	temp1 = (char*)src;
	while (--n)
		*temp++ = *temp1++;
	*temp = *temp1;
	return (dst);
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


int main(int argc, char **argv)
{
	INIT_NEXUS;
	int temp;

	if (argc < 2)
		error_exit("Bye");
	temp = 0;
	while(++temp < argc)
		if (check_valid(argv[temp]) < 0)
			error_exit("Bad One");
	NEXUS = malloc_nexus(argc, argv);
	ft_putstr(ft_strndup("Cowhats", 256));
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

