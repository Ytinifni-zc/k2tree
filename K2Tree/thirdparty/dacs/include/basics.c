
// Basics

// #include "basics.h" included later to avoid macro recursion for malloc
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

const unsigned char __popcount_tab[] = {
  0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4,1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,
  1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
  1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
  2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
  1,2,2,3,2,3,3,4,2,3,3,4,3,4,4,5,2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,
  2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
  2,3,3,4,3,4,4,5,3,4,4,5,4,5,5,6,3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,
  3,4,4,5,4,5,5,6,4,5,5,6,5,6,6,7,4,5,5,6,5,6,6,7,5,6,6,7,6,7,7,8,
};

const unsigned char select_tab[] = {
  0,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
  6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
  7,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
  6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
  8,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
  6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
  7,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
  6,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,5,1,2,1,3,1,2,1,4,1,2,1,3,1,2,1,
};

const unsigned char prev_tab[] = {
  0,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
};

		// Memory management

	void *Malloc (int n)

	   { void *p;
	     if (n == 0) return NULL;
	     p = (void*) malloc (n);
	     if (p == NULL)
	        { fprintf (stderr,"Could not allocate %i bytes\n",n);
	          exit(1);
	        }
	     return p;
	   }

	void Free (void *p)

	   { if (p) free (p);
	   }

	void *Realloc (void *p, int n)

	   { if (p == NULL) return Malloc (n);
	     if (n == 0) { Free(p); return NULL; }
	     p = (void*) realloc (p,n);
	     if (p == NULL)
	        { fprintf (stderr,"Could not allocate %i bytes\n",n);
	          exit(1);
	        }
	     return p;
	   }

#include "basics.h"

        // bits needed to represent a number between 0 and n

uint bits (uint n)

   { uint b = 0;
     while (n)
	{ b++; n >>= 1; }
     return b;
   }

        // returns e[p..p+len-1], assuming len <= W

uint bitread (uint *e, uint p, uint len)

   { uint answ;
     e += p/W; p %= W;
     answ = *e >> p;
     if (len == W)
	  { if (p) answ |= (*(e+1)) << (W-p);
	  }
     else { if (p+len > W) answ |= (*(e+1)) << (W-p);
            answ &= (1<<len)-1;
	  }
     return answ;
   }


  	// writes e[p..p+len-1] = s, len <= W

void bitwrite (uint *e, uint p,
	       uint len, uint s)

   { e += p/W; p %= W;
     if (len == W)
	  { *e |= (*e & ((1<<p)-1)) | (s << p);
            if (!p) return;
            e++;
            *e = (*e & ~((1<<p)-1)) | (s >> (W-p));
	  }
     else { if (p+len <= W)
	       { *e = (*e & ~(((1<<len)-1)<<p)) | (s << p);
		 return;
	       }
	    *e = (*e & ((1<<p)-1)) | (s << p);
            e++; len -= W-p;
            *e = (*e & ~((1<<len)-1)) | (s >> (W-p));
	  }
   }
  	// writes e[p..p+len-1] = 0

void bitzero (uint *e, uint p,
	       uint len)

   { e += p/W; p %= W;
     if (p+len >= W)
	{ *e &= ~((1<<p)-1);
	  len -= p;
	  e++; p = 0;
	}
     while (len >= W)
	{ *e++ = 0;
	  len -= W;
	}
     if (len > 0)
	*e &= ~(((1<<len)-1)<<p);
   }


uint GetField(uint *A,  uint len, uint index) {
  uint i=index*len/W, j=index*len-W*i, result;
  if (j+len <= W)
    result = (A[i] << (W-j-len)) >> (W-len);
  else {
    result = A[i] >> j;
    result = result | (A[i+1] << (WW-j-len)) >> (W-len);
  }
  return result;
}


void SetField(uint *A,uint len, uint index, uint x) {
  uint i=index*len/W, j=index*len-i*W;
  uint mask = ((j+len) < W ? ~0u << (j+len) : 0) | ((W-j) < W ? ~0u >> (W-j) : 0);
  A[i] = (A[i] & mask) | x << j;
  if (j+len>W) {
    mask = ((~0u) << (len+j-W));
    A[i+1] = (A[i+1] & mask)| x >> (W-j);
  }
}


uint GetVarField(uint *A,  uint ini, uint fin) {
  uint i=ini/W, j=ini-W*i, result;
  uint len = (fin-ini+1);
  if (j+len <= W)
    result = (A[i] << (W-j-len)) >> (W-len);
  else {
    result = A[i] >> j;
    result = result | (A[i+1] << (WW-j-len)) >> (W-len);
  }
  return result;
}


void SetVarField(uint *A,uint ini, uint fin, uint x) {
  uint i=ini/W, j=ini-i*W;
  uint len = (fin-ini+1);
  uint mask = ((j+len) < W ? ~0u << (j+len) : 0) | ((W-j) < W ? ~0u >> (W-j) : 0);
  A[i] = (A[i] & mask) | x << j;
  if (j+len>W) {
    mask = ((~0u) << (len+j-W));
    A[i+1] = (A[i+1] & mask)| x >> (W-j);
  }
}


unsigned GetFieldW32(uint *A,uint index) {
  return A[index];
}


void SetField32(uint *A, uint index,uint x) {
  A[index]=x;
}


unsigned GetFieldW16(uint *A,uint index) {
  uint i=index/2, j=(index&1)<<4, result;
  result = (A[i] << (16-j)) >> (16);
  return result;
}

unsigned GetFieldW4(uint *A,uint index) {
  uint i=index/8, j=(index&0x7)<<2;
  /*unsigned i=index/8, j=index*4-32*i; */
  return (A[i] << (28-j)) >> (28);
}


uint popcount (int x) {
  return __popcount_tab[(x >>  0) & 0xff]  + __popcount_tab[(x >>  8) & 0xff]  + __popcount_tab[(x >> 16) & 0xff] + __popcount_tab[(x >> 24) & 0xff];
}


uint popcount16 (int x) {
  return __popcount_tab[x & 0xff]  + __popcount_tab[(x >>  8) & 0xff];
}


uint popcount8 (int x) {
  return __popcount_tab[x & 0xff];
}
