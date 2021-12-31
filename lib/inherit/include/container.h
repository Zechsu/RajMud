#ifndef l_container_h
#define l_container_h

int is_container();
string query_contents_mess();
int can_put(object who);
varargs mixed event_recieve_item(object item, object who);
varargs mixed event_get_from(object who, string what);
varargs mixed event_look_in(object who);

#endif