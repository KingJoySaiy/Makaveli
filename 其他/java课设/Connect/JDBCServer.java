package Connect;

import java.util.ArrayList;

interface JDBCServer {

    boolean insert(String... data);

    boolean delete(String... data);

    boolean modify(String... data);

    ArrayList<String> query(String... data);
}
