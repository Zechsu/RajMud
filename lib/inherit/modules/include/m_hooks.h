#ifndef __mhooks_h__
#define __mhooks_h__

#define HOOK_IGNORE     0   // Ignore the return values
#define HOOK_LAND       1

varargs mixed call_hook(string tag, mixed func, mixed start, mixed* args...);
void add_hook(string tag, function hook);
void remove_hook(string tag, function hook);

#endif