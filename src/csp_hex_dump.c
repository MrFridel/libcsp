

#include <stdio.h>
#include <inttypes.h>

void csp_hex_dump_format(const char * desc, void * addr, int len, int format) {
	int i;
	unsigned char buff[17];
	unsigned char * pc = (unsigned char *)addr;

	// Output description if given.
	if (desc != NULL)
		printf("%s\n", desc);

	if (!(len > 0))
		return;

	// Process every byte in the data.
	for (i = 0; i < len; i++) {
		// Multiple of 16 means new line (with line offset).

		if ((i % 16) == 0) {
			// Just don't print ASCII for the zeroth line.
			if (i != 0)
				printf("  %s\n", buff);

			// Output the offset.
			if (format & 0x1) {
				printf("  %p ", ((uint8_t *)addr) + i);
			} else {
				printf("        ");
			}
		}

		// Now the hex code for the specific character.
		printf(" %02x", pc[i]);

		// And store a printable ASCII character for later.
		if ((pc[i] < 0x20) || (pc[i] > 0x7e))
			buff[i % 16] = '.';
		else
			buff[i % 16] = pc[i];
		buff[(i % 16) + 1] = '\0';
	}

	// Pad out last line if not exactly 16 characters.
	while ((i % 16) != 0) {
		printf("   ");
		i++;
	}

	// And print the final ASCII bit.
	printf("  %s\n", buff);
}

void csp_hex_dump(const char * desc, void * addr, int len) {
	csp_hex_dump_format(desc, addr, len, 0);
}
