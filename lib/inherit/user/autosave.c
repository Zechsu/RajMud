private mixed* inventory = 0;
private nosave int  last_save  = time();

string query_name();
void refresh_play_time();

nomask void restore_inventory() {
    if (inventory) {
        foreach (string obdata in inventory) {
            object ob;
            mixed tmp;

            tmp = restore_variable(obdata);
            if (arrayp(tmp)) {
                ob = new(tmp[0]);
                if (ob) ob->event_convert_object(tmp, 1);
            }
            else {
                if (!catch(ob = new(tmp["#base_name#"]))) {
                    if (ob) {
                        ob->event_load_object(tmp, 1);
                    }
                }
            }
        }
    }
    inventory = 0;
}

nomask int restore_player() {
    string file;
    int ret;
    
    file = player_save_file(query_name());
    ret = restore_object(file, 1);
    return ret;
}

nomask void save_player() {
    string file;
    mixed ret;
    
    refresh_play_time();
    inventory = filter(map(all_inventory(), (: $1->query_save_string() :)), (: $1 :));
    file = player_save_file(query_name());
    ret =  save_object(file, 1);
    inventory = 0;
    call_out("save_player", 30);
}

int setup() {
    master()->create_save();
    restore_player();
    restore_inventory();
    call_out("save_player", 5);
}
