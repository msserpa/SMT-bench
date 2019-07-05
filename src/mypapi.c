#include <assert.h>
#include <papi.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "../include/mypapi.h"
#include "../include/workloads.h"
#include "../include/mixed.h"
#include "../include/spinlock.h"

extern uint32_t papi_enabled;
static FILE *fpapi = NULL;
extern char *map;
static spinlock_t threads_lock = SPINLOCK_INIT;

/* Use a positive value of retval to simply print an error message */
void error_handler_papi(int line, const char *call, int retval){
	if(retval >= 0 || retval == PAPI_ESYS)
		fprintf(stderr, "libmypapi - Error: %s on line %d\n", call, line);
	else
		fprintf(stderr, "libmypapi - Error: %s : %s on line %d\n\n", call, PAPI_strerror(retval), line);

	_exit(1);
}

void overflow_handler(){
	error_handler_papi(__LINE__, "overflow", 1);	
}

void papi_init(){
	int retval = PAPI_library_init(PAPI_VER_CURRENT);
	if(retval != PAPI_VER_CURRENT)
		error_handler_papi(__LINE__, "PAPI_library_init", retval);

	/* Initialize pthreads */
	retval = PAPI_thread_init(pthread_self);
	if(retval != PAPI_OK)
		error_handler_papi(__LINE__, "PAPI_thread_init", retval);

	system("rm -f /tmp/micro.papi &> /dev/null");
}

void papi_thread_init(void *data){
	thread_data_t *t = (thread_data_t*)data;

	t->EventSet1 = PAPI_NULL;

	/* Initialize the EventSet */
	int retval = PAPI_create_eventset(&t->EventSet1);
	if(retval != PAPI_OK)
		error_handler_papi(__LINE__, "PAPI_create_eventset", retval);

	/* Get environment variable */
	t->event = getenv("PAPI_EVENT");
	if(t->event == NULL)
		error_handler_papi(__LINE__, "PAPI_EVENT is not defined", 1);

	/* Add event from ENV */
	retval = PAPI_add_named_event(t->EventSet1, t->event);
	if(retval != PAPI_OK)
		error_handler_papi(__LINE__, "Trouble adding event", retval);

	int eventCode;

	retval = PAPI_event_name_to_code(t->event, &eventCode);
	if(retval != PAPI_OK){
		switch(retval){
			case PAPI_EINVAL: 
				error_handler_papi(__LINE__, "One or more of the arguments is invalid", retval);
			break;
			case PAPI_ENOTPRESET:
				error_handler_papi(__LINE__, "The hardware event specified is not a valid PAPI preset", retval);
			break;
			case PAPI_ENOEVNT:
				error_handler_papi(__LINE__, "The PAPI preset is not available on the underlying hardware", retval);
			break;
			case PAPI_ENOINIT:
				error_handler_papi(__LINE__, "The PAPI library has not been initialized", retval);
			break;
			default:
				error_handler_papi(__LINE__, "PAPI_event_name_to_code error", retval);
		}
	}

	if(eventCode >= 0){
		retval = PAPI_overflow(t->EventSet1, eventCode, INT_MAX, 0, (PAPI_overflow_handler_t) overflow_handler);
		if(retval != PAPI_OK){
			switch(retval){
				case PAPI_EINVAL: 
					error_handler_papi(__LINE__, "One or more of the arguments is invalid. Specifically, a bad threshold value", retval);
				break;
				case PAPI_ENOMEM:
					error_handler_papi(__LINE__, "Insufficient memory to complete the operation", retval);
				break;
				case PAPI_ENOEVST:
					error_handler_papi(__LINE__, "The EventSet specified does not exist", retval);
				break;
				case PAPI_EISRUN:
					error_handler_papi(__LINE__, "The EventSet is currently counting events", retval);
				break;
				case PAPI_ECNFLCT:
					error_handler_papi(__LINE__, "The underlying counter hardware cannot count this event and other events in the EventSet simultaneously. Or you are trying to overflow both by hardware and by forced software at the same time", retval);
				break;
				case PAPI_ENOEVNT:
					error_handler_papi(__LINE__, "The PAPI preset is not available on the underlying hardware", retval);
				break;
				case PAPI_ENOINIT:
					error_handler_papi(__LINE__, "The PAPI library has not been initialized", retval);
				break;  				
				default:
					error_handler_papi(__LINE__, "PAPI_EVENT overflowed", retval);
			}
		}
	}

	/* Start PAPI */
	retval = PAPI_start(t->EventSet1);
	if(retval != PAPI_OK)
		error_handler_papi(__LINE__, "PAPI_start", retval);
}

void papi_thread_finish(void *data){
	thread_data_t *t = (thread_data_t*)data;

	/* Stop PAPI */
	int retval = PAPI_stop(t->EventSet1, t->value);
	if(retval != PAPI_OK)
		error_handler_papi(__LINE__, "PAPI_stop", retval);

	/* Shutdown the EventSet */
	retval = PAPI_cleanup_eventset(t->EventSet1);
	if(retval != PAPI_OK)
		error_handler_papi(__LINE__, "PAPI_cleanup_eventset", retval);

	retval = PAPI_destroy_eventset(&t->EventSet1);
	if(retval != PAPI_OK)
		error_handler_papi(__LINE__, "PAPI_destroy_eventset", retval);

	/*remove underlines */
	char *ptr = &t->event[0];
	while(*ptr != '\0'){
		if(*ptr == '_')
			*ptr='-';
		ptr++;
	}

	spinlock_lock(&threads_lock);
	fpapi = fopen("/tmp/micro.papi", "a");
	assert(fpapi != NULL);
	fprintf(fpapi, "%s,%s,%lu,%s,%lu,%s,%d,%lld\n", map, workload_name[t->typeA], t->memoryA, workload_name[t->typeB], t->memoryB, &t->event[0], t->cpu, t->value[0]);
	fclose(fpapi);
	spinlock_unlock(&threads_lock);
}
