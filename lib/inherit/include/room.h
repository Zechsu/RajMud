#ifndef l_room_h
#define l_room_h

void add_item(mixed item);
void add_prop(string prop, string desc);
object* query_props();
object* query_items();
int can_enter(object who);
varargs int event_enter(object who);

#endif