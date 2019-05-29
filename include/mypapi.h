#ifndef MYPAPI_H

	#define MYPAPI_H

	void error_handler_papi(int line, const char *call, int retval);

	void overflow_handler();

	void papi_init();

	void papi_thread_init(void *data);

	void papi_thread_finish(void *data);

#endif