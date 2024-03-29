#include "holberton.h"

/**
 * _printf - print the numbers passed to func with separator
 * @format: a string to print with various identifiers to inject variables
 * Return: void
 */
int _printf(const char * const format, ...)
{
	int i = 0, D = 0, bcnt = 0;
	void (*funk)(va_list *, int *, flag_list *);
	char *buffr = malloc(1024);
	va_list args;
	flag_list flags;

	if (!format || !buffr) /* check if format and malloc exists */
		return (-1);

	flags_reset(&flags, buffr);
	va_start(args, format);
	while (format && format[i])
	{
		/* identify and set flags, or exit returning chars printed */
		if (flag_check(&format[i], &flags, &i, &D, buffr, &bcnt))
			return (-1);
		/* if not for flags.op */
		if (!flags.op)
		{
			D += _putchar(format[i]);
			flags_reset(&flags, buffr);
		}
		else
		{
			funk = get_funky(format[i]);
			/* check if func != NULL */
			if (funk != NULL)
			{
				funk(&args, &D, &flags);
				flags_reset(&flags, buffr);
			}
		}
		++i;
	}
	va_end(args);
	flags_reset(&flags, buffr);
	free(buffr);
	return (D);
}
/**
 * get_funky - returns a pointer to the correct function to use
 * @s: string of operation fed from argv[2]
 * Return: pointer to the correct function
 */
void (*get_funky(char s))(va_list *, int *, flag_list *)
{
	char ch2str[2];
	spec_list spec[] = {
		{"b", p_b},
		{"c", p_c},
		{"d", p_di},
		{"i", p_di},
		{"o", p_o},
		{"%", p_p},
		{"S", p_Ss},
		{"s", p_Ss},
		{"u", p_u},
		{"X", p_Xx},
		{"x", p_Xx},
		{NULL, NULL}
	};
	int i = 0;

	ch2str[0] = s;
	ch2str[1] = '\0';

	/* find the correct func based on s */
	while (spec[i].op != NULL && _strcmp(spec[i].op, ch2str))
		++i;

	return (spec[i].f);
}
/**
 * flags_reset - set the print modifiers to zero
 * @flagz: a flag_list with values to reset
 * @buffr: temp storage of format chars
 * Return: void
 */
void flags_reset(flag_list *flagz, char *buffr)
{
	(*flagz).op = 0;
	(*flagz).h = 0;
	(*flagz).l = 0;
	(*flagz).S = 0;
	(*flagz).sp = 0;
	(*flagz).X = 0;

	buffr[0] = '\0';
}
/**
 * flag_check - sets the flags for the current char
 * @c: current char in format
 * @f: our flag_list variable
 * @i: iterator where the op is found
 * @D: count of printed chars
 * @bfr: temp holder for chars, may not need now
 * @bi: iterator for bfr
 * Return: 1 if % is last char in c string, else 0
 */
int flag_check(const char *c, flag_list *f, int *i, int *D, char *bfr, int *bi)
{
	int f_test = 0;

	if (!(*f).op && *c == '%') /* check for op char */
	{
		(*f).op = 1;
		++c;
		++*i;
		*bfr = '%';
		++*bi;
		if (*c == '\0')
			return (1);
	}
	f_test = flag_set(c, f);

	if ((*f).op && get_funky(*c))
		return (0);

	if ((*f).op && *c == '\0')
	{
		*(bfr + *bi) = '\0';
		*bi = 0;
		/* print the buffer */
		p_buffer(bfr, D);
		flags_reset(f, bfr);
		return (1);
	}
	else if ((*f).op && (*c == ' ' || f_test))
	{
		*(bfr + (*bi)) = *c;
		++*i;
		++*bi;
		flag_check((c + 1), f, i, D, bfr, bi);
	}
	else if (!f_test)
	{
		*(bfr + *bi) = '\0';
		*bi = 0;
		p_buffer(bfr, D);
		flags_reset(f, bfr);
	}
	return (0);
}
/**
 * flag_set - sets the flags for the current char
 * @c: current char in format
 * @flagz: our flag_list variable
 * Return: 1 if a flag was set
 */
int flag_set(const char *c, flag_list *flagz)
{
	char *mods = "_hlS X";
	int i;

	/* stop loop when char match */
	for (i = 0; (*flagz).op && mods[i] != *c && mods[i]; ++i)
	;
	if (i == 1)
		(*flagz).h = 1;
	else if (i == 2)
		(*flagz).l = 1;
	else if (i == 3)
		(*flagz).S = 1;
	else if (i == 4)
		(*flagz).sp = 1;
	else if (i == 5)
		(*flagz).X = 1;

	if (i < 6 && i != 0)
		return (1);

	return (0);
}
