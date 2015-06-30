package war.client;

import com.google.gwt.user.client.rpc.RemoteService;
import com.google.gwt.user.client.rpc.RemoteServiceRelativePath;

/**
 * Created by witalia on 11.12.14.
 */
@RemoteServiceRelativePath("messages")
public interface MessageService extends RemoteService {
    Boolean checkName(String name);

    Integer[] getRooms();

    String[] getMessages(Integer room);

    void sendMessage(String username, Integer room, String message);
}
