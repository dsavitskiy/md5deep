
/* MD5DEEP - sha1.h
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

/* $Id: sha1.h 171 2009-01-15 23:04:12Z jessekornblum $ */

#ifndef __SHA1_H
#define __SHA1_H

#include "common.h"

struct SHA1_Context{
  uint32_t state[5];
  uint32_t count[2];
  unsigned char buffer[64];
};

typedef struct SHA1_Context SHA1_CTX;

typedef SHA1_CTX context_sha1_t;

void SHA1Transform(uint32_t state[5], unsigned char buffer[64]);
void SHA1Init(SHA1_CTX* context);

//void SHA1Update(SHA1_CTX* context, unsigned char * data, uint64_t len);
void SHA1Update(SHA1_CTX* context, unsigned char * data, unsigned int len);

void SHA1Final(unsigned char digest[20], SHA1_CTX* context);

int hash_init_sha1(void *ctx);
int hash_update_sha1(void *ctx, unsigned char *buf, uint64_t len);
int hash_final_sha1(void *ctx, unsigned char *digest);


#endif   /* ifndef __SHA1_H */
