#ifndef l_body_h
#define l_body_h

string* query_limbs();
mapping query_body();
int create_new_body(string race);
string query_current_room();
varargs mixed query_worn(string limb);
varargs string* find_limb(string* match, int flag, int slot);
void sever_limb(string limb);
int is_limb_severed(string limb);
int is_limb_damaged(string limb);

#endif