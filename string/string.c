// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source) {
	while (*source != '\0') {
		// Copying the characters
		*destination = *source;
		destination++;
		source++;
	}

	// Setting the string terminator
	*destination = '\0';

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len) {
	char *dest_ptr = destination;
	const char *src_ptr = source;

	while (len > 0) {
		// Checking if I can copy
		if (*src_ptr != '\0')
			*dest_ptr = *src_ptr;
		else
			*dest_ptr = '\0';
		// Moving forward
		dest_ptr++;
		src_ptr++;
		len--;
	}

	return destination;
}

char *strcat(char *destination, const char *source) {
	strcpy(destination + strlen(destination), source);

	return destination;
}

char *strncat(char *destination, const char *source, size_t len) {
	char *dest_ptr = destination;
	// Reaching the end of the destination pointer
	while (*dest_ptr)
		dest_ptr++;
	// Concatenating the strings
	while (*source && len > 0) {
		*dest_ptr++ = *source++;
		len--;
	}

	*dest_ptr = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2) {
	// Iterating trough str1 and checking whether str1 and str2 at a position
	// are equal
	while (*str1 && (*str1 == *str2)) {
		str1++;
		str2++;
	}

	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}

int strncmp(const char *str1, const char *str2, size_t len) {
	for (; str1 && str2 && len > 0; len--, str1++, str2++)
		if (*str1 != *str2) {
			if (*str1 < *str2)
				return -1;
			return 1;
		}

	return 0;
}

size_t strlen(const char *str) {
	size_t i = 0;

	for (; *str != '\0'; str++, i++) continue;

	return i;
}

char *strchr(const char *str, int c) {
	for (; *str; str++) {
		// Finding the first appearance of the character
		if (*str == (char)c)
			return (char *)str;
	}

	return NULL;
}

char *strrchr(const char *str, int c) {
	const char *last_occurence = NULL;

	for (; *str; str++) {
		if (*str == (char)c)
			last_occurence = str; // Updating the last appearance of c
	}

	return (char *)last_occurence;
}

char *strstr(const char *haystack, const char *needle) {
	for (size_t i = 0; i < strlen(haystack); i++) {
		// Looking for the first appearance
		if (!strncmp(haystack + i, needle, strlen(needle)))
			return (char *) haystack + i;
	}

	return NULL;
}

char *strrstr(const char *haystack, const char *needle) {
	const char *last_occurence = NULL;

	if (*needle == '\0')
		return haystack;
	// Looking for the last appearance of the substring needle
	for (const char *i = haystack; *i != '\0'; i++) {
		const char *j = i;
		const char *k = needle;

		for (; *k != '\0'; j++, k++)
			if (*j != *k)
				break;

		if (*k == '\0')
			last_occurence = i;
	}

	return last_occurence;
}

void *memcpy(void *destination, const void *source, size_t num) {
	strncpy(destination, source, num);
	return destination;
}

void *memmove(void *destination, const void *source, size_t num) {
	char buffer[10000];

	strcpy(buffer, source);

	return memcpy(destination, buffer, num);
}

int memcmp(const void *ptr1, const void *ptr2, size_t num) {
	return strncmp(ptr1, ptr2, num);
}

void *memset(void *source, int value, size_t num) {
	unsigned char *src = (unsigned char *)source;
	size_t i = 0;
	// Iterating through the string and assigning the value
	while (i < num) {
		src[i] = value;
		i++;
	}

	return source;
}
