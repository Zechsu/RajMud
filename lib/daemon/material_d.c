#include <globals.h>
#include <material.h>

private mapping materials = ([]);

void create() {
    foreach (string file in get_dir(MATERIALS_DIR + "/*.c")) {
        string tmp = MATERIALS_DIR + "/" + file;
        string name;

        if (!load_object(tmp)) {
            debug_message("Couldn't load material " + tmp + "\n");
            continue;
        }
        name = tmp->query_material()->name;
        materials[name] = tmp->query_material();
    }
}

class Material_t query_material(string mat) {
    return materials[mat];
}