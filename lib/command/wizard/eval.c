int
main(string arg)
{
    object res;
    /* clean up first */
    if (file_size("/tmp_eval_file.c") != -1)
    rm ("/tmp_eval_file.c");
    if (find_object("/tmp_eval_file"))
    destruct(find_object("/tmp_eval_file"));

    write_file("/tmp_eval_file.c","mixed eval() { "+arg+"; }\n");
    res = "/tmp_eval_file"->eval();
    if (stringp(res)) {
        write("Result = " + res + "\n");
        return 1;
    }
    printf("Result = %O\n", res);
    return 1;
}
