string *split_path (string path) {
    int pos;
    while (path[<1] == '/' && strlen(path) > 1) path = path[0..<2];
    pos = strsrch(path, '/', -1);
    return ({ path[0..pos], path[pos+1..] });
}

string base_path (string path) {
    return split_path(path)[0];
}

// Evaluate . and .. and enforce leading /
string sanitize_path (string path) {
    string *parts;
    int i = 0;
    int trailingSlash;

    if (undefinedp(path) || !path || path == "" || (path[0] != '/' && path[0] != '~' && path[0] != '^')) {
        if (previous_object() && previous_object()->query_shell()) {
            path = previous_object()->query_shell()->query_cwd();
        }
    }

    trailingSlash = (strlen(path) > 0 && (path[<1] == '/' || path[<2..] == "/." || path[<3..] == "/.."));
    if (path[0] == '^') {
        path = replace_string(path, "^", "domain/");
    } else if (path[0] == '~') {
        path = replace_string(path, "~", "realm/" + this_player()->query_account_link()->query_account_name() + "/");
    }
    parts = explode(path, "/") - ({ "", "." });
    if (!sizeof(parts)) {
        return "/";
    }

    while (i < sizeof(parts)) {
        string tmp = parts[i];
        if (tmp == "..") {
            if (i) {
                parts[i-1..i] = ({});
                i --;
            } else {
                parts[i..i] = ({});
            }
            continue;
        }
        i ++;
    }

    if (!sizeof(parts) && trailingSlash) {
        trailingSlash = 0;
    }

    return "/" + implode(parts, "/") + (trailingSlash ? "/" : "");
}