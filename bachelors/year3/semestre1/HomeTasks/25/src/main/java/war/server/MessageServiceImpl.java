package war.server;

import com.google.gwt.user.server.rpc.RemoteServiceServlet;
import db.beans.Message;
import db.beans.Room;
import db.beans.User;
import db.dao.DAOFactory;
import war.client.MessageService;

import java.sql.SQLException;
import java.util.Arrays;
import java.util.List;

/**
 * Created by witalia on 11.12.14.
 */
public class MessageServiceImpl extends RemoteServiceServlet
        implements MessageService {

    @Override
    public Boolean checkName(String name) {
        try {
            User user = DAOFactory.getUserDAO().getUserByUsername(name);
            return user != null;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return false;
    }

    @Override
    public Integer[] getRooms() {
        try {
            List rooms = (List<Room>) DAOFactory.getRoomDAO().getAllRooms();
            Integer[] res = new Integer[rooms.size()];
            for (int i = 0; i < res.length; ++i) {
                res[i] = ((Room) rooms.get(i)).getId();
            }
            return res;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public String[] getMessages(Integer room) {
        try {
            Room room1 = DAOFactory.getRoomDAO().getRoomById(room);
            List msg = (List<Message>) DAOFactory.getMessageDAO().getMessagesByRoom(room1);
            String[] res = new String[msg.size()];
            for (int i = 0; i < res.length; i++) {
                Message cur = (Message) msg.get(i);
                res[i] = cur.getUser().getUsername() + ": " + cur.getText();
            }
            System.out.println(Arrays.toString(res));
            return res;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void sendMessage(String username, Integer room, String message) {
        try {
            System.out.println("sendMessage " + username);
            User user = DAOFactory.getUserDAO().getUserByUsername(username);
            System.out.println(user);
            Room room1 = DAOFactory.getRoomDAO().getRoomById(room);
            DAOFactory.getMessageDAO().addMessage(new Message(message, room1, user));
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
