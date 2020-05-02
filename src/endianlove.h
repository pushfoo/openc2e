/*
 *  endianlove.h
 *  openc2e
 *
 *  Created by Alyssa Milburn on Sat May 22 2004.
 *  Copyright (c) 2004 Alyssa Milburn. All rights reserved.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 */

#ifndef _ENDIANLOVE_H
#define _ENDIANLOVE_H

#include <iostream>
#include <stdlib.h> // load the standard libraries for these defines
#include <stdint.h>

static inline uint16_t swapEndianShort(uint16_t a) {
	uint8_t *t = reinterpret_cast<uint8_t*>(&a);
	return (t[0] << 0) | (t[1] << 8);
}

static inline uint32_t swapEndianLong(uint32_t a) {
	uint8_t *t = reinterpret_cast<uint8_t*>(&a);
	return (t[0] << 0) | (t[1] << 8) | (t[2] << 16) | (t[3] << 24);
}

static inline uint8_t read8(std::istream &s) {
	uint8_t t[1];
	s.read(reinterpret_cast<char*>(t), 1);
	return t[0];
}

static inline uint16_t read16le(std::istream &s) {
	uint8_t t[2];
	s.read(reinterpret_cast<char*>(t), 2);
	return (t[0] << 0) | (t[1] << 8);
}

static inline uint16_t read16be(std::istream &s) {
	uint8_t t[2];
	s.read(reinterpret_cast<char*>(t), 2);
	return (t[0] << 8) | (t[1] << 0);
}

static inline void readmany16le(std::istream &s, uint16_t* out, size_t n) {
	for (size_t i = 0; i < n; ++i) {
		out[i] = read16le(s);
	}
}

static inline void write16le(std::ostream &s, uint16_t v) {
	uint8_t t[] = {
		static_cast<uint8_t>(v >> 0),
		static_cast<uint8_t>(v >> 8)
	};
	s.write(reinterpret_cast<char *>(t), 2);
}

static inline void write16be(std::ostream &s, uint16_t v) {
	uint8_t t[] = {
		static_cast<uint8_t>(v >> 8),
		static_cast<uint8_t>(v >> 0)
	};
	s.write(reinterpret_cast<char *>(t), 2);
}

static inline uint32_t read32le(std::istream &s) {
	uint8_t t[4];
	s.read(reinterpret_cast<char*>(t), 4);
	return (t[0] << 0) | (t[1] << 8) | (t[2] << 16) | (t[3] << 24);
}

static inline void write32le(std::ostream &s, uint32_t v) {
	uint8_t t[] = {
		static_cast<uint8_t>(v >> 0),
		static_cast<uint8_t>(v >> 8),
		static_cast<uint8_t>(v >> 16),
		static_cast<uint8_t>(v >> 24)
	};
	s.write(reinterpret_cast<char *>(t), 4);
}

#endif // _ENDIANLOVE_H

/* vim: set noet: */
