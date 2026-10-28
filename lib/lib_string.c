/*
 * SPDX-FileCopyrightText: Copyright (C) 2026 Altera Corporation
 *
 * SPDX-License-Identifier: MIT-0
 */

#include <stdint.h>
#include <stddef.h>

void *memcpy(void *dst, const void *src, size_t n)
{
	uint8_t *d = (uint8_t *)dst;
	const uint8_t *s = (const uint8_t *)src;

	while (n--) {
		*d++ = *s++;
	}

	return dst;
}

void *memset(void *dst, int c, size_t n)
{
	uint8_t *d = (uint8_t *)dst;
	uint8_t v = (uint8_t)c;

	while (n--) {
		*d++ = v;
	}

	return dst;
}

int memcmp(const void *a, const void *b, size_t n)
{
	const uint8_t *pa = (const uint8_t *)a;
	const uint8_t *pb = (const uint8_t *)b;

	while (n--) {
		uint8_t va = *pa++;
		uint8_t vb = *pb++;

		if (va != vb) {
			return (va < vb) ? -1 : 1;
		}
	}

	return 0;
}

// optional bzero wrapper
void bzero(void *s, size_t n)
{
	memset(s, 0, n);
}

static uint8_t heap[1024];
static size_t heap_index = 0;

void* malloc(size_t size) 
{
	if (heap_index + size > sizeof(heap)) return NULL;
	void* ptr = &heap[heap_index];
	heap_index += size;
	return ptr;
}

void free(void* ptr)
{
	(void)ptr;
}

// Optional: simple realloc (inefficient)
void* realloc(void* ptr, size_t size) {
	(void)ptr; // ignore old pointer
	return malloc(size);
}

