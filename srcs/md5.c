#include"ssl.h"

unsigned char *pad_str(char *str, size_t *pad_len)
{
	uint32_t	msg_len = ft_strlen(str);
	uint8_t		*new_msg = NULL;
	uint32_t	new_len = msg_len + 1;

	while (new_len % 64 != 56)
		new_len++;
	
	new_msg = ft_calloc(new_len + 8, sizeof(char));
	ft_memcpy(new_msg, str, msg_len);
	new_msg[msg_len] = 0x80;

	uint64_t bit_len = ((uint64_t)msg_len * 8);

	// #if defined(__BYTE_ORDER__) && __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
	// 	bit_len = ft_swapLongEndian(bit_len);
	// #endif

	for (int i = 0; i < 8; i++)
		new_msg[new_len + i] = (bit_len >> (8 * i)) & 0xFF;

	ft_memcpy(&new_msg[new_len - 8], &bit_len, 8);
	*pad_len = new_len;
	return (new_msg);
}

uint32_t set32intbit(unsigned char *str)
{
	uint8_t b1 = (uint8_t)(str[0]);
	uint8_t b2 = (uint8_t)(str[1]);
	uint8_t b3 = (uint8_t)(str[2]);
	uint8_t b4 = (uint8_t)(str[3]);

	uint32_t newnbr = ((uint32_t)b1 << 24) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 8) | ((uint32_t)b4);

	return (newnbr);
}

uint32_t leftRotate(int n, unsigned int t)
{
    return (n << t) | (n >> (sizeof(uint32_t) - t));
}

char *md5(void)
{
	char test[] = "The quick brown fox jumps over the lazy dog";
	uint32_t s[64] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};
	uint32_t K[64] = {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee, 0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501, 0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be, 0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821, 0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa, 0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8, 0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed, 0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a, 0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c, 0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70, 0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05, 0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665, 0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039, 0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1, 0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1, 0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

	uint32_t a0 = 0x67452301;
	uint32_t b0 = 0xefcdab89;
	uint32_t c0 = 0x98badcfe;
	uint32_t d0 = 0x10325476;

	size_t pad_len = 0;
	unsigned char *pad = pad_str(test, &pad_len);
	if (!pad)
		return (NULL);

	size_t bit_len = pad_len * 8;

	for (size_t chunk = 0; chunk < bit_len; chunk += 512)
	{
		uint32_t M[16];
		for (int i = 0; i < 16; i++)
		{
			M[i] = set32intbit(pad + (4 * i));
		}

		uint32_t A = a0;
		uint32_t B = b0;
		uint32_t C = c0;
		uint32_t D = d0;
		for (uint32_t i = 0; i < 64; i++)
		{
			uint32_t F, g;
			if (i <= 15)
			{
				F = (B & C) | ((~D) & C);
				g = i;
			}
			else if (i >= 16 && i <= 31)
			{
				F = (D & B) | ((~D) & C);
				g = (5 * i) % 16;
			}
			else if (i >= 32 && i <= 47)
			{
				F = (B ^ C ^ D);
				g = (3 * i) % 16;
			}
			else if (i >= 48 && i <= 63)
			{
				F = (C ^ (B | (~D)));
				g = (7 * i) % 16;
			}
			F = F + A + K[i] + M[g];
			A = D;
			D = C;
			C = B;
			B = B + leftRotate(F, s[i]);
		}
		a0 += A;
		b0 += B;
		c0 += C;
		d0 += D;
	}
	char digest[16];
	sprintf(digest, "%x%x%x%x\n", a0, b0, c0, d0);

	printf(digest);

	free(pad);
	return (NULL);
}