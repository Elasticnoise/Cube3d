#include "../../includes/cube3d.h"

int	create_trgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}