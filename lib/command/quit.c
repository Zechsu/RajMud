#include <command.h>

int main(string arg)
{
    object po, login, tp;
    // destruct(tp->query_account_link());
    po = previous_object();
    login = new(LOGIN_OB);
    tp = this_player();
    tp->refresh_play_time();
    tp->save_player();
    write("Bye.\n");
    say(po->query_name() + " leaves this reality.\n");
    login->setup_link(po->query_account_name());
    exec(login, po);
    po->remove();
    login->goto_account_menu();
    return 1;
}
