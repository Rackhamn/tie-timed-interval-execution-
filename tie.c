/* appease the c89 gods */
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 199309L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NS_NS	1
#define MS_NS	1000000
#define SS_NS	1000000000
#define MM_NS	60000000000
#define HH_NS	3600000000000
#define DD_NS	(24 * HH_NS)

#define ARG_ME	0
#define ARG_TT	1
#define ARG_TV	2
#define ARG_OV	3
#define ARG_CD	4

long rt();
void st(long t);
int _strlen(const char * a);
int _strcmp(const char * a, const char * b);

int main(int argc, char **argv)
{
	long long t, s, r; /* timeout, sleeptime, resolution */
	int l;
	char * ic;
	
	if(argc < ARG_CD) 
	{ printf("Error [Not Enough Arguments]\n"); return 1; }

	ic = argv[ARG_TT];
	if(_strcmp(ic, "-dd")) 		{ r = DD_NS; }
	else if(_strcmp(ic, "-hh")) 	{ r = HH_NS; }
	else if(_strcmp(ic, "-mm")) 	{ r = MM_NS; }
	else if(_strcmp(ic, "-ss")) 	{ r = SS_NS; }
	else if(_strcmp(ic, "-ms")) 	{ r = MS_NS; }
	else if(_strcmp(ic, "-ns")) 	{ r = NS_NS; }
	else { printf("Error [Bad Argument]\n"); return 1; }

	s = atol(argv[ARG_TV]) * r;
	t = atol(argv[ARG_OV]);
	if(s <= 0)
	{ printf("Error [Bad Time Value]\n"); return 1; }
	if(t <= 0) { t = 1; }

	printf("resolution %lli (ns)\n", r);
	printf("sleeptime %lli, %lli (ns)\n", s / r, s);
	printf("count %lli, %lli (ns)\n", t,  t * r);

	/* fix: t is checking counts not actual time. */
	while(t-- > 0) {
		st(s);

		l = argc - ARG_CD;
		while(l-- > 0)
		{ system(argv[l + ARG_CD]); }
	};
	printf("Timeout\n");

	return 0;
}

/* appease c89 gods */
int clock_gettime(clockid_t __clock_id, struct timespec *__tp);
int clock_nanosleep(clockid_t __clock_id, int __flags, const struct timespec * __req, struct timespec *__rem);

long rt() {
	struct timespec req;
	req.tv_sec = 0;
	req.tv_nsec = 0;
	clock_gettime(CLOCK_MONOTONIC, &req);
	return (long)(req.tv_sec * SS_NS) + (long)(req.tv_nsec);
};

void st(long t) {
	struct timespec req;
	if(t <= 0) { return; }
	req.tv_sec = 0;
	req.tv_nsec = 0;
	while(t > SS_NS)
	{ req.tv_sec++; t -= SS_NS; }
	/* note: can sleep up to 10ms too long... */
	clock_nanosleep(CLOCK_MONOTONIC, 0, &req, NULL);
};

int _strlen(const char * a) {
	int l;
	l = 0;
	while(*a++ != '\0') { l++; }
	return l;
};

int _strcmp(const char * a, const char * b) {	
	int l;
	l = _strlen(a);
	if(l != _strlen(b)) { return 0; }
	while(l-- > 0)
	{ if(*(a+l) != *(b+l)) { return 0; } }
	return 1;
};
