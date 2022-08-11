private mapping attributes;

void create() {
    attributes = ([]);
}

void set_attribute(mixed attr, mixed val) {
    attributes[attr] = val;
}

mapping query_attributes() {
    return copy(attributes);
}

mapping query_attribute(mixed attr) {
    return attributes[attr];
}