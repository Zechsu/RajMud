#ifndef l_weapon_h
#define l_weapon_h

int can_wield(object who, string limb);
varargs mixed event_wield(object who, string limb);
void set_valid_limbs(mixed equips);
int is_weapon();

#endif