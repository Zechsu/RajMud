#ifndef l_item_h
#define l_item_h

string* query_ids();
int can_get(object who);
varargs mixed event_recieved(object who);
protected mixed* add_save(mixed* vars);
string* query_save();
void set_name(string n);
string query_name();
int is_item();
string query_indefinite_article();

#endif /* l_item_h */
