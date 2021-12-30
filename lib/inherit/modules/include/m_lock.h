#ifndef __mlock_h__
#define __mlock_h__

int set_can_lockpick(int can);
int set_locked(int lock);
int query_complexity();
int set_complexity(int comp);
mixed event_pick_lock(object who);
int is_locked();
mixed event_lock(object who, object key);
mixed event_unlock(object who, object key);
int has_lock();

#endif