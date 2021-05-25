#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Assistant.h"
#include "BinarySearchTreeAPI.h"
#include <ctype.h>
/**
 * function to turn a string into lowercase
 */
void toLower(char word[])
{
	for (int i = 0; i < strlen(word); ++i)
	{
		word[i] = tolower(word[i]);
	}
}

/**
 * print menu function
 */
void menu()
{
	printf("1)Add a new rule\n2)Remove a rule\n3)Display rules\n4)Modify rule rating\n5)Discuss\n\n9) Quit\n");
}
/**
 * menu option1
 * prompts for rule data and returns it
 */
Rule *menuOption1()
{
	getchar();
	printf("Enter a keyword\n");
	char *key = malloc(sizeof(char) * 40);
	fgets(key, 40, stdin);
	toLower(key);
	key[strcspn(key, "\r\n")] = '\0';
	printf("Enter a sentence\n");
	char *sen = malloc(sizeof(char) * 128);
	getchar();
	fgets(sen, 128, stdin);
	sen[strcspn(sen, "\r\n")] = '\0';
	Rule *temp = createRule(key, sen);
	double rating = 2.0;
	while (rating > 1.0 || rating < 0.0)
	{
		printf("Enter the importance rating (0.0-1.0)");
		scanf("%lf", &rating);
	}
	temp->user_rating = rating;
	return temp;
}

int main(int argc, char *argv[])
{
	char *file_keyword = malloc(sizeof(char) * 40);
	char *file_response = malloc(sizeof(char) * 128);
	char menu_in[2];
	if (argc != 2)
	{
		printf("Error. Proper Usage: <program> <filename>\n");
	}
	else
	{
		FILE *f = fopen(argv[1], "r");
		if (f == NULL)
		{
			printf("Could not open file\n");
		}
		else
		{
			/*binary search tree creation*/
			Tree *BST = createBinTree(&compareRule, &deleteRule);
			/*reading data from file*/
			while (fgets(file_keyword, 40, f) != NULL)
			{
				/*keyword case insensitive to keep duplicates out*/
				toLower(file_keyword);
				/*stripping the new line char and white space from the end*/
				file_keyword[strcspn(file_keyword, "\r\n")] = '\0';
				fgets(file_response, 256, f);
				file_response[strcspn(file_response, "\r\n")] = '\0';
				Rule *temp = createRule(file_keyword, file_response);
				addToTree(BST, temp);
				file_keyword = malloc(sizeof(char) * 40);
				file_response = malloc(sizeof(char) * 128);
			}
			/*closing and freeing whats not needed*/
			fclose(f);
			free(file_keyword);
			free(file_response);
			/*main loop*/
			do
			{
				menu();
				scanf("%s", menu_in);
				/*work for adding rule done in function menuOption1*/
				if (strcmp(menu_in, "1") == 0)
				{
					Rule *temp = menuOption1();
					addToTree(BST, temp);
				}
				/*compare function only compares keyword so to make search
				 * effective, creates a new rule with a duplicate keyword,
				 * rest of the data is random and not used*/
				if (strcmp(menu_in, "2") == 0)
				{
					printf("Enter a keyword\n");
					char *key = malloc(sizeof(char) * 40);
					scanf("%s", key);
					Rule *temp = createRule(key, "garbage");
					removeFromTree(BST, temp);
					free(temp);
					free(key);
				}
				/*printInOrder used here but all 3 print functions are functional*/
				if (strcmp(menu_in, "3") == 0)
				{
					printInOrder(BST, printRule);
				}
				/*uses find in tree to look for a rule and updates the user_rating*/
				if (strcmp(menu_in, "4") == 0)
				{
					printf("Enter a keyword\n");
					char *key = malloc(sizeof(char) * 40);
					getchar();
					fgets(key, 40, stdin);
					key[strcspn(key, "\r\n")] = '\0';
					Rule *temp = createRule(key, "garbage");
					temp = findInTree(BST, temp);
					if (temp != NULL)
					{
						double rating = 2.0;
						while (rating > 1.0 || rating < 0.0)
						{
							printf("Enter the importance rating (0.0-1.0)");
							scanf("%lf", &rating);
						}
						temp->user_rating = rating;
					}
					free(key);
				}
				/*tokenizes the input and prints the highest available importance keyword*/
				if (strcmp(menu_in, "5") == 0)
				{
					printf("Raiken wants to talk. Please enter a sentence\n");
					char question[256] = "";
					getchar();
					fgets(question, 256, stdin);
					question[strcspn(question, "\r\n")] = '\0';
					char *token = strtok(question, " ");
					int x = 0;
					double importance = 0.0;
					int index = -353;
					char **token_words = malloc(sizeof(char *) * 10);
					for (int i = 0; i < 10; ++i)
					{
						token_words[i] = malloc(sizeof(char) * 40);
						strcpy(token_words[i], " ");
					}
					while (token != NULL)
					{
						strcpy(token_words[x], token);
						token = strtok(NULL, " ");
						x++;
					}
					for (int i = 0; i < 10; ++i)
					{
						if (strcmp(token_words[i], " ") != 0)
						{
							Rule *temp = createRule(token_words[i], "garbage");
							temp = findInTree(BST, temp);
							if (temp != NULL)
							{
								if (temp->user_rating + temp->system_rating > importance)
								{
									importance = temp->user_rating + temp->system_rating;
									index = i;
								}
							}
						}
					}
					if (index >= 0)
					{
						Rule *temp = createRule(token_words[index], "garbage");
						temp = findInTree(BST, temp);
						printf("%s\n", temp->response);
						temp->count++;
						printf("Was that feedback helpful? (y/n)\n");
						char ans[1];
						scanf("%s", ans);
						if (strcmp(ans, "n") == 0)
							temp->system_rating = temp->system_rating - (temp->system_rating * temp->learing_rate / temp->count);
						else
							temp->system_rating = temp->system_rating + (temp->system_rating * temp->learing_rate / temp->count);
					}
					for (int i = 0; i < 10; ++i)
					{
						free(token_words[i]);
					}
					free(token_words);
				}
			} while (strcmp(menu_in, "9") != 0);
			destroyBinTree(BST);
		}
	}
	return 0;
}
