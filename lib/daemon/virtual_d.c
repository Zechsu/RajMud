mixed compile_object(string file) {
    int x, y;
    if (sscanf(file, "/forest/%d,%d", x, y) == 2) {
        object forest = new("std/virtual/forest");
        forest->set_square_max_area(10, 10);
        forest->set_x(x);
        forest->set_y(y);
        forest->virtual_create();
        return forest;
    }
    return 0;
}