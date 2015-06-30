import org.junit.Assert;
import org.junit.Test;

import java.io.FileOutputStream;

/**
 * Created by Witalia on 29.10.2014.
 */
public class SSHClientTester {
    @Test
    public void testSendCommand() throws Exception {
        SSHManager manager = new SSHManager(
                "username", "127.0.0.1", "password", null
        );
        Assert.assertNull(manager.connect());
        manager.sendCommand("echo 1", null);
        Assert.assertEquals(manager.getCommandResult(), "1\n");
    }
}
