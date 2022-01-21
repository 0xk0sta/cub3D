#include "cub3d.h"

int skip_spaces(char *line, int i)
{
	if (!line)
		return (0);
	while (line[i] && line[i] == ' ')
		i++;
	return (i);
}

int check_above(t_map **map, int i, int j)
{
	if ((*map)->map[i - 1][j - 1] != '1' || (*map)->map[i - 1][j] != '1' || (*map)->map[i - 1][j + 1] != '1')
	{
		if ((*map)->map[i - 1][j - 1] == ' ')
		{
			if (check_surroundings(map, i + 1, j - 1) != 0)
				return (1);
		}
		else if ((*map)->map[i - 1][j] == ' ')
		{
			if (check_surroundings(map, i + 1, j) != 0)
				return (1);
		}
		else if ((*map)->map[i - 1][j + 1] == ' ')
		{
			if (check_surroundings(map, i - 1, j + 1) != 0)
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

int check_below(t_map **map, int i, int j)
{
	if ((*map)->map[i + 1][j - 1] != '1' || (*map)->map[i + 1][j] != '1' || (*map)->map[i + 1][j + 1] != '1')
	{
		if ((*map)->map[i + 1][j - 1] == ' ')
		{
			if (check_surroundings(map, i + 1, j - 1) != 0)
				return (1);
		}
		else if ((*map)->map[i + 1][j] == ' ')
		{
			if (check_surroundings(map, i + 1, j) != 0)
				return (1);
		}
		else if ((*map)->map[i + 1][j + 1] == ' ')
		{
			if (check_surroundings(map, i + 1, j + 1) != 0)
				return (1);
		}
		else
			return (1);
	}
	return (0);
}

int check_surroundings(t_map **map, int i, int j)
{
	int		map_len;
	char	c[2];

	map_len = dptr_len((*map)->map);
	if (i > map_len - 1)
		return (0);
	c[0] = (*map)->map[i][j + 1];
	c[1] = (*map)->map[i][j - 1];
	if (c[0] != '1' || c[1] != '1')
		return (1);
	if (i == map_len - 1)
	{
		if (check_above(map, i, j) != 0)
			return (1);
	}
	else if (i == 0)
	{
		if (check_below(map, i, j) != 0)
			return (1);
	}
	else
	{
		if (check_above(map, i, j) != 0 || check_below(map, i, j) != 0)
			return (1);
	}
	return (0);
}

int last_map_check(t_map **map)
{
	int i;
	int j;

	i = 1;
	while ((*map)->map[++i])
	{
		j = skip_spaces((*map)->map[i], 0);
		while((*map)->map[i][++j] != '\n' && (*map)->map[i][j] != '\0')
		{
			if ((*map)->map[i][j] == 'N' || (*map)->map[i][j] == 'S'
				|| (*map)->map[i][j] == 'W' || (*map)->map[i][j] == 'E')
			{
				(*map)->p_pos[0] = (float)j;
				(*map)->p_pos[1] = (float)i;
			}
			if ((*map)->map[i][j] == ' ')
				if (check_surroundings(map, i, j) != 0)
					return (error_ret("Error\nMap is not surrounded by 1's\n", 1));
		}
	}
	return (0);
}

int check_top_and_bot(char *line)
{
	int i;

	i = -1;
	while (line[++i] && (line[i] != '\n' && line[i] != '\0'))
	{
		if (line[i] != '1' && line[i] != ' ')
			return (error_ret("Error\nFirst or last line is not filled by 1's\n", 1));
	}
	return (0);
}

int	counter(char c, t_map **map)
{
	if (c == 'E' || c == 'S' || c == 'W' || c == 'N')
		(*map)->count++;
	if ((*map)->count > 1)
		return (1);
	return (0);
}

int line_handler(char *line, int index, t_map **map)
{
	int i;

	i = skip_spaces(line, 0);
	if (index == 0 || index == (*map)->lines)
		return (check_top_and_bot(line));
	else if (line && (line[i] != '1' || line[ft_strlen(line) - 1] != '1'))
		return (error_ret("Error\nMap not closed by 1's\n", 1));
	while (line[++i] != '\n' && line[i] != '\0')
	{
		if (!(line[i] == '0' || line[i] == '1' || line[i] == 'N' || line[i] == ' '
			  || line[i] == 'E' || line[i] == 'W' || line[i] == 'S'))
			return (error_ret("Error\nInvalid character on the map\n", 1));
		else
		{
			if (counter(line[i], map) != 0)
				return (error_ret("Error\nToo many player spawns\n", 1));
		}
	}
	return (0);
}

void fill_map(t_map **map)
{
	int i;

	i = 0;
	while((*map)->index < ((*map)->lines) && (*map)->buffer[(*map)->index])
	{
		(*map)->map[i++] = ft_substr((*map)->buffer[(*map)->index], 0, ft_strlen((*map)->buffer[(*map)->index]));
		(*map)->index++;
	}
//	i = 0;
//	while((*map)->map[i])
//		printf("%s\n", (*map)->map[i++]);
}

int parse_map(t_map **map)
{
	int i;

	i = -1;
	while ((*map)->buffer[(*map)->aux] && (*map)->buffer[(*map)->aux][0] == '\n')
		(*map)->aux++;
	(*map)->index = (*map)->aux;
	while ((*map)->aux < ((*map)->lines - 1) && (*map)->buffer[(*map)->aux])
	{
		if (line_handler((*map)->buffer[(*map)->aux++], ++i, map) != 0)
			return (1);
	}
	(*map)->map = (char **)ft_calloc(1, sizeof(char *) * (i + 3));
	if (!(*map)->map)
		return (1);
	fill_map(map);
	return (0);
}
