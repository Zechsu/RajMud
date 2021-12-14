#ifndef __beetle_obj_h__
#define __beetle_obj_h__

int has_horn();
int is_fighter_beetle();
string query_owner();
int set_owner(string);
void set_target(object);
object query_target();
string query_long();
int can_get(object);
int get_damage();
int is_dead();
int take_damage(int);
int lose_horn();
void set_special_attack(function);
mixed event_special_attack();
void set_special_attack_chance(int);
varargs void heal(int);

#endif
