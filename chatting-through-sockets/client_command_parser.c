#include "client_command_parser.h"
#include "commands_format.h"

#include <string.h>



static const char delimiter[] = " ";



static bool
check_trailing_stuff(void)
{
    char *token = strtok(NULL, delimiter);
    return token == NULL;
}



static bool
parse_register(char *username)
{
    char *token = strtok(NULL, delimiter);
    if (token == NULL)
        return false;
    strcpy(username, token);

    return check_trailing_stuff();
}



static bool
parse_who(void)
{
    return check_trailing_stuff();
}



static bool
parse_quit(void)
{
    return check_trailing_stuff();
}



static bool
parse_deregister(void)
{
    return check_trailing_stuff();
}



static bool
parse_send(char *username)
{
    char *token = strtok(NULL, delimiter);
    if (token == NULL)
        return false;
    strcpy(username, token);

    return check_trailing_stuff();
}



static int16_t
match_command(const char *command)
{
    if (strcmp(command, "!register") == 0)
        return REGISTER;
    if (strcmp(command, "!who") == 0)
        return WHO;
    if (strcmp(command, "!quit") == 0)
        return QUIT;
    if (strcmp(command, "!deregister") == 0)
        return DEREGISTER;
    if (strcmp(command, "!send") == 0)
        return SEND;
    return UNKNOWN_COMMAND;
}



bool
parse_command(const char* str, int16_t *command, char *username)
{
    char *token = NULL;

    // parse command
    token = strtok(command, delimiter);
    if (token == NULL)
        return false;

    *command = match_command(token);
    switch(*command) {
        case REGISTER:
            return parse_register(username);
        case WHO:
            return parse_who();
        case QUIT:
            return parse_quit();
        case DEREGISTER:
            return parse_deregister();
        case SEND:
            return parse_send(username);
    }
    return true;
}