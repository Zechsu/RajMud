// stolen from gesslar

#define VNUM_SAVE "/data/daemon/vnum"

private nomask mapping vnums;
private nomask mapping reverse_vnums;
int next_number;

void create() {
    if (clonep(this_object())) {
        return;
    }
    if (!restore_object(VNUM_SAVE)) {
        vnums = ([]);
        reverse_vnums = ([]);
    }
    if (!sizeof(vnums)) {
        vnums = ([]);
    }
    if (!sizeof(reverse_vnums)) {
        reverse_vnums = ([]);
    }
}

void save_me() {
    save_object(VNUM_SAVE);
}

nomask int lookup_vnum( mixed room )
{
    string fname;
    int num;

    if( objectp(room) ) fname = base_name( room );
    else if( stringp(room) ) fname = room;
    else return 0;

    if( !mapp(vnums) )
    {
        vnums = ([ ]);
        reverse_vnums = ([ ]);
        next_number = 0;
    } 

    if( fname[<2..] == ".c" ) fname = fname[0..<3];
    
    if( vnums[fname] ) return vnums[ fname ];

    vnums[ fname ] = next_number;
    reverse_vnums[ next_number ] = fname;

    num = next_number ++;
    
    save_me();

    return num;
}

nomask string reverse_lookup_vnum( int num )
{
    return reverse_vnums[ num ];
}
