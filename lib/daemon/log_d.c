void log(string type, string log) {
    write_file("log/daemon/" + type, log);
}