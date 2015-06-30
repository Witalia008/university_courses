import Sample.utils.Database;
import Sample.utils.User;
import org.junit.*;
/**
 * Created by Witalia on 19.11.2014.
 */
public class CloudTest {
    @Test
    public void testDatabaseOperations() throws Exception {
        Database database = Database.getDatabase("Witalia", "password");
        Assert.assertNotNull(database);
        Assert.assertFalse(database.checkCredentials(
                new User("Witalia", "trashpass")
        ));

        User user = new User("Witalia", "password");
        Assert.assertTrue(database.checkCredentials(user));
        Assert.assertFalse(database.addUser(user));
        Assert.assertEquals(user.getUsername(),
                database.getProperty("username", user));
        Assert.assertEquals(user.getPassHash(),
                database.getProperty("passhash", user));
        Assert.assertEquals(user.getSalt(),
                database.getProperty("salt", user));
    }

    @Test
    public void testUser() throws Exception {
        User user = new User("Ivanov", "qwerty");
        user.setSalt();
        Assert.assertTrue(user.getSalt() != null);
        user.hashPass();
        Assert.assertTrue(user.getPassHash() != null);
    }
}
