#ifndef LIBMAPPING_H

	#define LIBMAPPING_H
	#define BUFFER_SIZE 1024

	void error_handler(const char *call, const int line);

	void map_init();

	void map_terminate();

	void map_threads();

	void map_heterogeneous();

	void map_homogeneos();

	void map_random();

	void map_env(char *mapping);

#endif