#ifndef l_item_h
#define l_item_h

string* query_ids();
int set_message(string kind, string mess);
string query_message(string kind);
int can_get(object who);
varargs mixed event_recieved(object who);
protected mixed* add_save(mixed* vars);
string* query_save();
void set_name(string n);
string query_name();

#endif /* l_item_h */
