#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: String array copy of environ
 */
char **get_environ(info_t *info)
{
if (!info->environ || info->env_changed)
{
free_string_array(info->environ);
info->environ = list_to_string_array(info->env);
info->env_changed = 0;
}

return (info->environ);
}

/**
 * unset_env_var - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The environment variable to unset
 * Return: (1) if variable is unset, (0) otherwise
 */
int unset_env_var(info_t *info, const char *var)
{
if (!info->env || !var)
return (0);

int removed = remove_node(&(info->env), var);
info->env_changed = removed;
return (removed);
}

/**
 * set_env_var - Set or modify an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: The environment variable to set or modify
 * @value: The value to assign to the environment variable
 * Return: (0) on success, (1) on failure
 */
int set_env_var(info_t *info, const char *var, const char *value)
{
if (!var || !value)
return (1);

char *env_var = malloc(strlen(var) + strlen(value) + 2);
if (!env_var)
return (1);

sprintf(env_var, "%s=%s", var, value);
int updated = update_or_add_node(&(info->env), var, env_var);
info->env_changed = updated;

free(env_var);
return (0);
}

