#ifndef TGA_HEADER_H
#define TGA_HEADER_H

#include "sb7.h"

// Define targa header. This is only used locally.
#pragma pack(1)
typedef struct
{
	GLbyte	identsize;				// Size of ID field that follows header (0)
	GLbyte	colorMapType;			// 0 = None, 1 = Paletted
	GLbyte	imageType;				// 0 = None, 1 = Indexed, 2 = RGB, 3 = Gray, +8 = RLE
	unsigned short	colorMapStart;	// First color map entry
	unsigned short	colorMapLength;	// Number of colors
	unsigned char	colorMapBits;	// Bits per palette entry
	unsigned short	xStart;			// Image x origin
	unsigned short	yStart;			// Image y origin
	unsigned short	width;			// Width in pixels
	unsigned short	height;			// Height in pixels
	GLbyte	bits;					// Bits per pixel (8, 16, 24, 32)
	GLbyte	descriptor;				// Image descriptor
} TGAHEADER;
#pragma pack(8)

#endif
