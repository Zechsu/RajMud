private nosave int start_play = time();
private nosave int end_play = 0;
private int play_time = 0;

void refresh_play_time() {
    end_play = time();
    play_time += end_play - start_play;
    start_play = time();
}

int query_play_time() {
    refresh_play_time();
    return play_time;
}
