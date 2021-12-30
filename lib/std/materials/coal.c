#include <material.h>

class Material_t material;

void create() {
    material = new(class Material_t);
    material->name = "coal";
    material->density = 1;
}

class Material_t query_material() {
    return material;
}

void print_mat() {
    mixed* res = disassemble_class( material ) ;
    write(sprintf("%O\n", res ));
}