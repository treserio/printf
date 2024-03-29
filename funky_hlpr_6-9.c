#include "holberton.h"
/**
 * p_l_sgn - print a long int
 * @argz: currently long int in va_list
 * @base: the base that we're working in, base2 = binary
 * @flagz: currently set flags
 * Return: count of chars printed
 */
int p_l_sgn(va_list *argz, long int base, flag_list *flagz)
{
	long int val = va_arg(*argz, long int), digit;
	int count = 0, too_neg = 0;

	if ((*flagz).sp && val >= 0)
		count += _putchar(' ');
	/* check for negative val, INT_MIN > INT_MAX by 1 */
	if (val < 0)
	{
		count += _putchar('-');
		if (val == LONG_MIN)
			val += ++too_neg;
		val *= -1;
	}
	/* find the size of val */
	for (digit = 1; (val / digit) >= base; digit *= base)
	;
	/* print all the values while walking it back */
	for (; digit >= 1; val %= digit, digit /= base)
	{
		if (digit == 1 && too_neg)
			count += p_hex_hlpr(val / digit + too_neg, (*flagz).X);
		else
			count += p_hex_hlpr(val / digit, (*flagz).X);
	}
	return (count);
}
/**
 * p_l_uns - print an unsigned long int
 * @argz: currently unsigned long int in va_list
 * @base: the base that we're working in, base2 = binary
 * @flagz: currently set flags
 * Return: count of chars printed
 */
int p_l_uns(va_list *argz, unsigned long int base, flag_list *flagz)
{
	unsigned long int val = va_arg(*argz, unsigned long int);
	unsigned long int digit;
	int count = 0;

	if ((*flagz).sp)
		count += _putchar(' ');
	/* find the size of val */
	for (digit = 1; (val / digit) >= base; digit *= base)
	;
	for (; digit >= 1; val %= digit, digit /= base)
		count += p_hex_hlpr(val / digit, (*flagz).X);

	return (count);
}
