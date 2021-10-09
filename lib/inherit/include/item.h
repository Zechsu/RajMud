#ifndef l_item_h
#define l_item_h

string* query_ids();
int set_message(string kind, string mess);
string query_message(string kind);
int event_get(object player, int amount);
int event_drop(object player);
int can_get();

#endif /* l_item_h */