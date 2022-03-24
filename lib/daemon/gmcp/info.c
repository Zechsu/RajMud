// stolen from gesslar

#include <daemons.h>

void Info(object who)
{
    object room = environment(who);
    int num;
    mapping data = ([ ]);
    mapping exits;

    if(!room) return;
    
    num = VNUM_D->lookup_vnum(room);
    exits = room->query_exits() || ([ ]);
    exits = map(exits, (: sprintf("%d", VNUM_D->lookup_vnum($2)) :));

    data = ([
        "name" : remove_color(room->query_short()),
        "vnum" : sprintf("%d", num),
        "terrain" : "unknown",
        "exits" : exits,
        "area" : "Kicata",
    ]);

    who->send_gmcp_data("Room.Info", json_encode(data));
}

void Items(object who) {
    object room = environment(who);
    object* inv = all_inventory(room);
    mapping data = ([]);
    inv = filter_array(inv, (: $1->is_item() :));

    data = ([
        "list": map(inv, (: remove_color($1->query_short()) :))
    ]);

    who->send_gmcp_data("Room.Items", json_encode(data));
}