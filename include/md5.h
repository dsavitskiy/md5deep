
/* MD5DEEP - md5.h
 *
 * By Jesse Kornblum
 *
 * This is a work of the US Government. In accordance with 17 USC 105,
 * copyright protection is not available for any work of the US Government.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 */

/* $Id: md5.h 171 2009-01-15 23:04:12Z jessekornblum $ */

#ifndef __MD5_H
#define __MD5_H

#include "common.h"

// -------------------------------------------------------------- 
// After this is the algorithm itself. You shouldn't change these

typedef struct _context_md5_t {
  uint32_t buf[4];
  uint32_t bits[2];
  unsigned char in[64];
} context_md5_t;

// This is needed to make RSAREF happy on some MS-DOS compilers 
typedef context_md5_t MD5_CTX;

void MD5Init(context_md5_t *ctx);
void MD5Update(context_md5_t *context, unsigned char *buf, unsigned len);
void MD5Final(unsigned char digest[16], context_md5_t *context);
void MD5Transform(uint32_t buf[4], uint32_t const in[16]);

int hash_init_md5(void * ctx);
int hash_update_md5(void *ctx, unsigned char *buf, uint64_t len);
int hash_final_md5(void *ctx, unsigned char *digest);

#endif /* ifndef __MD5_H */
