package SQLSyntax;

import java.sql.SQLException;

interface SQLSyntax {

    String insert(String... data);
    String delete(String... data);
    String modify(String... data);
    String query(String... data) throws SQLException;
}
