#include "holberton.h"
/**
 * p_b - print unsigned base10 as base2
 * @argz: currently unsigned decimal in va_list
 * @D: count of chars printed
 * @flagz: UNUZED - list of possible print modifiers
 * Return: count of chars from int printed
 */
void p_b(va_list *argz, int *D, flag_list *flagz)
{
	unsigned int val = va_arg(*argz, unsigned int);
	unsigned int digit = 1;

	if ((*flagz).sp)
		*D += _putchar(' ');
	/* find the size of val */
	for (digit = 1; (val / digit) >= 2; digit *= 2)
	;
	for (; digit >= 1; val %= digit, digit /= 2)
		*D += _putchar((val / digit) + '0');
}
/**
 * p_c - print char
 * @argz: currently char in va_list
 * @D: count of chars printed
 * @flagz: UNUSED - list of possible print modifiers
 * Return: 1 since char is only ever 1 character
 */
void p_c(va_list *argz, int *D, flag_list *flagz)
{
	char ch = va_arg(*argz, int);

	(void)(flagz);
	*D += _putchar(ch);
}
/**
 * p_di - print integer
 * @argz: currently integer in va_list
 * @D: count of chars printed
 * @flagz: list of possible print modifiers
 * Return: count of chars from int printed
 */
void p_di(va_list *argz, int *D, flag_list *flagz)
{
	int val;
	int digit, too_neg = 0;

	if ((*flagz).l)
	{
		*D += p_l_sgn(argz, 10, flagz);
		return;
	}
	/* pull the arg if it isn't a long */
	val = va_arg(*argz, int);
	if ((*flagz).h)
	{
		/* check if value is within short range */
		if (val > 32767 || val < -32768)
		{
			*D += _putchar('-');
			*D += _putchar('1');
			return;
		}
	}
	if ((*flagz).sp && val >= 0)
		*D += _putchar(' ');
	/* check for negative val, INT_MIN > INT_MAX by 1 */
	if (val < 0)
	{
		*D += _putchar('-');
		if (val == INT_MIN)
			val += ++too_neg;
		val *= -1;
	}
	for (digit = 1; (val / digit) >= 10; digit *= 10)
	;
	for (; digit >= 1; val %= digit, digit /= 10)
	{
		if (digit == 1 && too_neg)
			*D += _putchar((val / digit) + too_neg + '0');
		else
			*D += _putchar((val / digit) + '0');
	}
}
/**
 * p_p - print %
 * @argz: UNUSED - argument pointer
 * @D: count of chars printed
 * @flagz: UNUSED - list of possible print modifiers
 * Return: count
 */
void p_p(va_list *argz, int *D, flag_list *flagz)
{
	(void)(argz);
	(void)(flagz);

	*D += _putchar('%');
}
/**
 * p_Ss - print string
 * @argz: currently string in va_list
 * @D: count of chars printed
 * @flagz: UNUSED - list of possible print modifiers
 * Return: count of chars from string printed
 */
void p_Ss(va_list *argz, int *D, flag_list *flagz)
{
	unsigned int i;
	char *str = va_arg(*argz, char *);

	if (str == 0)
		str = "(null)";

	if ((*flagz).S)
	{
		for (i = 0; str[i]; ++i, ++*D)
			if (str[i] < 32 || str[i] > 126)
			{
				*D += _putchar('\\');
				_putchar('x');
				*D += p_hex_hlpr(str[i] / 16, 1);
				*D += p_hex_hlpr(str[i] % 16, 1);
			}
			else
				_putchar(str[i]);
	}
	else
	{
		for (i = 0; str[i]; ++i, ++*D)
			_putchar(str[i]);
	}
}
