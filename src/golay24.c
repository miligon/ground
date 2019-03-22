/**
 * Copyright 2017 Daniel Estevez <daniel@destevez.net>.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 This algorithm is based on 
 R.H. Morelos-Zaragoza, The Art of Error Correcting Coding, Wiley, 2002; Section 2.2.3
*/

#include <stdint.h>

//#include <volk/volk.h>

#include "golay24.h"

#define N 12

static const uint32_t H[N] = { 0x8008ed, 0x4001db, 0x2003b5, 0x100769,
			       0x80ed1, 0x40da3, 0x20b47, 0x1068f,
			       0x8d1d, 0x4a3b, 0x2477, 0x1ffe };

#define B(i) (H[i] & 0xfff)

/** Codifica un numero en Golay24.
 */
int encode_golay24(uint32_t *data) {
  register uint32_t r = (*data) & 0xfff;
  register uint32_t s;
  register int i;

  s = 0;
  for (i=0; i < N; i++) {
    s <<= 1;
    s |= __builtin_parity(H[i] & r);
  }

  *data = ((0xFFF & s) << N) | r;
  return 0;
}
