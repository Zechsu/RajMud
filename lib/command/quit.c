#include <command.h>

int main(string arg)
{
    object po = previous_object();
    object login = new(LOGIN_OB);
    object tp = this_player();
    tp->refresh_play_time();
    tp->save_player();
    destruct(tp->query_account_link());
    write("Bye.\n");
    say(po->query_name() + " leaves this reality.\n");
    login->setup_link(po->query_name());
    exec(login, po);
    po->remove();
    login->goto_account_menu();
    return 1;
}
