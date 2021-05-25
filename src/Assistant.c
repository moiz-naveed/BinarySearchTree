#include "Assistant.h"
#include "BinarySearchTreeAPI.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void deleteRule(void *data)
{
	Rule *temp = (Rule *)data;
	temp->keyword = NULL;
	temp->response = NULL;
	temp->user_rating = 0.0;
	temp->system_rating = 0.0;
	temp->learing_rate = 0.0;
	temp->count = 0;
}

int compareRule(const void *a, const void *b)
{
	Rule *fi = (Rule *)a;
	Rule *se = (Rule *)b;
	return strcmp(fi->keyword, se->keyword);
}

Rule *createRule(char *keyword, char *response)
{
	Rule *temp = malloc(sizeof(Rule));
	temp->keyword = keyword;
	temp->response = response;
	temp->user_rating = 0.5;
	temp->system_rating = 0.5;
	temp->learing_rate = 0.05;
	return temp;
}

void printRule(void *data)
{
	Rule *temp = (Rule *)data;
	printf("%s ", temp->keyword);
	printf("Rating: %.2f System: %.2f Occurrences: %d\n", temp->user_rating, temp->system_rating, temp->count);
}
