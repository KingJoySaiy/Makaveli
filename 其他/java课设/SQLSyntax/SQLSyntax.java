package SQLSyntax;

interface SQLSyntax {

    String insert(String... data);

    String delete(String... data);

    String modify(String... data);

    String query(String... data);
}
