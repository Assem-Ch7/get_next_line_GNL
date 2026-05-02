#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int		fd;
	char	*line;
	int		lines_read;

	// O_RDONLY is slightly safer since we are only reading, not writing
	fd = open("file.txt", O_RDONLY); 
	if (fd == -1)
	{
		printf("Error: Could not open file.\n");
		return (1);
	}
	
	lines_read = 1;
	// This loop keeps running as long as GNL finds a line!
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Line %d: %s", lines_read, line);
		
		// You MUST free inside the loop so you don't leak the previous lines
		free(line); 
		lines_read++;
	}
	
	close(fd);
	return (0);
}