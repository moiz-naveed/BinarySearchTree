#ifndef assistant
#define assistant

#include "BinarySearchTreeAPI.h"

typedef struct rule
{
	char *keyword, *response;
	double user_rating, system_rating, learing_rate;
	int count;
} Rule;
/**
 * disposes off data*/
void deleteRule(void *data);
/**
 * casts to char* and compares keyword using strcmp
 */
int compareRule(const void *a, const void *b);
/**
 * allocates memory and assigns default ratings
 */
Rule *createRule(char *keyword, char *response);
/**
 * casts to char* and prints
 */
void printRule(void *data);

#endif
