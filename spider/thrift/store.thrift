struct movie_info
{
	1: string url,
	2: string movienum,
	3: string initial_release_date,
	4: string big_poster,
	5: string small_poster,
	6: string language,
	7: string area,
	8: string scriptwriter,
	9: string actor,
	10: string director,
	11: string source,
	12: string imdb,
	13: string year,
	14: string genre,
	15: string runtime,
	16: string moviename,
	17: string otherName,
}

service store_service
{
	i32 put(1: movie_info info),
}
