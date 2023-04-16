mixed event_hear(mixed source, string mess) {
    if (this_object() == source) {
        return;
    }
    tell_object(this_object(), mess);
}