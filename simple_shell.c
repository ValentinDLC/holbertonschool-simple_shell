#include "shell.h"
/**
 * main - Entry point for the simple shell
 *
 * @ac: Argument count
 * @av: Argument vector
 * @env: Environment variables
 *
 * Return:
 */
int main(int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    /*Loops*/
    while (true)
    {
        /*Display prompt*/
        display_prompt();
        /*Read input*/
        if (read_input() == -1)
        {
            break;
        }
        
    }
    
    /*Parse Command*/
    /*Execute command*/
    /*Wait for completion*/
    /*Repeat/EOF*/
    return(0);
}