private int save_recurse;
private nosave int retain = 1;
private mixed* saved = ({});

private int event_convert_object(mixed val, int recurse);
int event_load_object(mixed val, int recurse);

string query_short();

int event_load_object(mixed val, int recurse) {
    mixed *tmp, *saved = this_object()->query_csaved();
    string *flat = ({});
    mixed data;

    data = val;
    if( arrayp(data) ) return event_convert_object(data, recurse);
    if (data["#base_name#"] != base_name(this_object())) error("Invalid save string.\n");
    tmp = map(saved, (: functionp($1)? evaluate($1, "loading") : $1 :));
    foreach (mixed elem in tmp) {
        if (arrayp(elem)) flat += elem;
        else flat += ({elem});
    }
    flat -= ({0});

    foreach(string var, val in data) {
        if (var[0] == '#') continue;
        catch(store_variable(var, val));
    }

    if(data["#inventory#"]) {
        foreach(mixed obdata in data["#inventory#"]) {
            object ob;

            val = restore_variable(obdata);
            if (arrayp(val)) {
                catch(ob = new(val[0]));
            }
            else {
                catch(ob = new(val["#base_name#"]));
            }
            if (ob) {
                ob->event_load_object(val, 1);
            }
        }
    }

    if (recurse) {
        object prev = previous_object();

        if (move_object(prev)) {
            call_out(
                function(object p) {
                    object env;
                    if (p && objectp(p)) env = environment(p);
                    else return;

                    if (!env) {
                        tell_object(p, "You lose " + query_short() + ".\n");
                    } else {
                        tell_object(p, "You drop " + query_short() + ".\n");
                        move_object(env);
                    }
                }, 1, prev);
        }
    }
}

private int event_convert_object(mixed val, int recurse) {
    string* flat = ({});
    mixed* tmp, *saved = this_object()->query_csaved();

    if (val[0] != base_name(this_object())) error("Invalid save string.\n");
    tmp = map(saved, (: functionp($1) ? evaluate($1, "loading"): $1 :));
    foreach (mixed elem in tmp) {
        if(arrayp(elem)) flat += elem;
        else flat += ({elem});
    }
    flat -= ({0});

    if (sizeof(flat) != sizeof(val[1])) error("Invalid save string size.\n");
    for (int i = 0; i < sizeof(flat); i++) {
        store_variable(flat[i], val[1][i]);
    }
    if (sizeof(val) == 3) {
        foreach (string obdata in val[2]) {
            object ob;
            val = restore_variable(obdata);
            ob = new(val[0]);
            ob->event_load_object(val, 1);
        }
    }
    if (recurse) {
        move_object(previous_object());
    }
    return 1;
}

mixed* query_csaved() {
    return copy(saved);
}

mixed* query_dsaved() {
    return saved;
}

protected mixed* add_save(mixed* vars) {
    mixed* tmp = saved + vars;
    saved = tmp;
    return copy(saved);
}

protected int set_save_recurse(int flag) {
    return save_recurse = flag;
}

string query_save_string() {
    mixed* tmp, *saved = this_object()->query_csaved();
    string* vv = variables(this_object());
    string* flat = ({});
    mapping mp = ([]);

    tmp = map(saved, (: functionp($1) ? evaluate($1, "saving"): $1 :));
    foreach(mixed elem in tmp) {
        if (arrayp(elem)) flat += elem;
        else flat += ({elem});
    }

    if (flat && sizeof(flat)) {
        flat -= ({0});
        foreach (mixed var in flat) {
            if (stringp(var)) {
                if (member_array(var, vv) == -1) continue;
                catch(mp[var] = fetch_variable(var)); 
            }
        }
    }
    mp["#base_name#"] = base_name(this_object());
    if (save_recurse) {
        mp["#inventory#"] = all_inventory()->query_save_string() - ({0});
    }
    return save_variable(mp);
}

int set_retain(int i) {
    if (i) retain = 1;
    else retain = 0;
    return retain;
}

int query_retain() {
    return retain;
}