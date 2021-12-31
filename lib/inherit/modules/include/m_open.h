#ifndef __mopen_h__
#define __mopen_h__

int is_open();
void toggle_opened();
varargs int can_open(object who);
varargs int can_close(object who);
varargs mixed event_open(object who);
varargs mixed event_close(object who);

#endif