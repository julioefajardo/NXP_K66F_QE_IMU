/*
  Print.h - Base class that provides print() and println()
  Copyright (c) 2008 David A. Mellis.  All right reserved.
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.
  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef Print_h
#define Print_h

#include <inttypes.h>
#include <stdio.h> // for size_t
#include <stdarg.h>
#include "WString.h"
#include "Printable.h"

#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2
#define BYTE 0

class __FlashStringHelper;

class Print
{
  public:
	virtual void write(uint8_t);
	virtual void write(const char *str);
	virtual void write(const uint8_t *buffer, size_t size);
	void print(const String &s);
	void print(char c)				{ write((uint8_t)c); }
	void print(const char s[])			{ write(s); }
	void print(const __FlashStringHelper *f);

	void print(uint8_t b)				{ write(b); }
	void print(int n)				{ print((long)n); }
	void print(unsigned int n)			{ printNumber(n, 0, 10); }
	void print(long n);
	void print(unsigned long n)			{ printNumber(n, 0, 10); }

	void print(unsigned char n, int base)		{ printNumber(n, 0, base); }
	void print(int n, int base)			{ (base == 10) ? print(n) : printNumber(n, 0, base); }
	void print(unsigned int n, int base)		{ printNumber(n, 0, base); }
	void print(long n, int base)			{ (base == 10) ? print(n) : printNumber(n, 0, base); }
	void print(unsigned long n, int base)		{ printNumber(n, 0, base); }

	void print(double n, int digits = 2)		{ printFloat(n, digits); }
	void println(void);
	void println(const String &s)			{ print(s); println(); }
	void println(char c)				{ print(c); println(); }
	void println(const char s[])			{ print(s); println(); }
	void println(const __FlashStringHelper *f)	{ print(f); println(); }
	void println(uint8_t b)				{ print(b); println(); }
	void println(int n)				{ print(n); println(); }
	void println(unsigned int n)			{ print(n); println(); }
	void println(long n)				{ print(n); println(); }
	void println(unsigned long n)			{ print(n); println(); }

	void println(unsigned char n, int base)		{ print(n, base); println(); }
	void println(int n, int base)			{ print(n, base); println(); }
	void println(unsigned int n, int base)		{ print(n, base); println(); }
	void println(long n, int base)			{ print(n, base); println(); }
	void println(unsigned long n, int base)		{ print(n, base); println(); }

	void println(double n, int digits = 2)		{ print(n, digits); println(); }
  private:
	void printNumberDec(unsigned long n, uint8_t sign);
	void printNumberHex(unsigned long n);
	void printNumberBin(unsigned long n);
	void printNumberAny(unsigned long n, uint8_t base);
	inline size_t printNumber(unsigned long n, uint8_t sign, uint8_t base) __attribute__((always_inline)) {
		if (base == 0) { write((uint8_t)n); return; }
		if (base == 10 || base < 2) { printNumberDec(n, sign); return; }
		if (base == 16) { printNumberHex(n); return; }
		if (base == 2) { printNumberBin(n); return; }
		printNumberAny(n, base);
	}
	void printFloat(double n, uint8_t digits);
};

#endif