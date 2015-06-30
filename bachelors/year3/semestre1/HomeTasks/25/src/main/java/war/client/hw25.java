package war.client;

import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.core.client.GWT;
import com.google.gwt.event.dom.client.*;
import com.google.gwt.user.client.Timer;
import com.google.gwt.user.client.rpc.AsyncCallback;
import com.google.gwt.user.client.ui.*;

/**
 * Entry point classes define <code>onModuleLoad()</code>.
 */
public class hw25 implements EntryPoint {
    private VerticalPanel mainPanel = new VerticalPanel();

    private Label errorLabel = new Label();

    private TextBox usernameTextBox = new TextBox();
    private HorizontalPanel loginPanel = new HorizontalPanel();
    private Button loginBtn = new Button("Login");

    private FlexTable roomTable = new FlexTable();
    private VerticalPanel msgPanel = new VerticalPanel();
    private TextArea msgArea = new TextArea();

    private TextArea sendMsgText = new TextArea();
    private Button sendBtn = new Button("Send");
    private HorizontalPanel sendPanel = new HorizontalPanel();

    private Integer roomId = null;

    private MessageServiceAsync msgSvc = GWT.create(MessageService.class);

    /**
     * This is the entry point method.
     */
    public void onModuleLoad() {
        loginPanel.add(usernameTextBox);
        loginPanel.add(loginBtn);
        loginBtn.addClickHandler(new ClickHandler() {
            @Override
            public void onClick(ClickEvent clickEvent) {
                checkUserName(usernameTextBox.getText());
            }
        });
        usernameTextBox.addKeyDownHandler(new KeyDownHandler() {
            @Override
            public void onKeyDown(KeyDownEvent keyDownEvent) {
                if (keyDownEvent.getNativeKeyCode() == KeyCodes.KEY_ENTER) {
                    checkUserName(usernameTextBox.getText());
                }
            }
        });

        sendMsgText.addKeyDownHandler(new KeyDownHandler() {
            @Override
            public void onKeyDown(KeyDownEvent keyDownEvent) {
                if (keyDownEvent.isControlKeyDown() &&
                        keyDownEvent.getNativeKeyCode() == KeyCodes.KEY_ENTER) {
                    sendMessage();
                }
            }
        });
        sendBtn.addClickHandler(new ClickHandler() {
            @Override
            public void onClick(ClickEvent clickEvent) {
                sendMessage();
            }
        });

        sendMsgText.setCharacterWidth(73);
        sendMsgText.setVisibleLines(4);
        sendPanel.add(sendMsgText);
        sendPanel.add(sendBtn);

        msgArea.setCharacterWidth(80);
        msgArea.setVisibleLines(15);
        msgArea.setEnabled(false);
        msgPanel.add(msgArea);
        msgPanel.add(sendPanel);

        roomTable.setVisible(false);
        msgPanel.setVisible(false);

        mainPanel.add(errorLabel);
        mainPanel.add(loginPanel);
        mainPanel.add(roomTable);
        mainPanel.add(msgPanel);

        Timer timer = new Timer() {
            @Override
            public void run() {
                if (roomId != null) {
                    errorLabel.setText("");
                    updateMessages();
                }
            }
        };
        timer.scheduleRepeating(100);

        RootPanel.get("message_panel").add(mainPanel);
    }

    private void sendMessage() {
        AsyncCallback<Void> callback = new AsyncCallback<Void>() {
            @Override
            public void onFailure(Throwable throwable) {
                errorLabel.setText("sendMessage failure\n"
                        + throwable.getMessage());
            }

            @Override
            public void onSuccess(Void aVoid) {
                updateMessages();
                sendMsgText.setText("");
            }
        };
        msgSvc.sendMessage(usernameTextBox.getText(), roomId, sendMsgText.getText(), callback);
    }

    private void updateMessages() {
        AsyncCallback<String[]> callback = new AsyncCallback<String[]>() {
            @Override
            public void onFailure(Throwable throwable) {
                errorLabel.setText("updateMessages failure\n"
                        + throwable.getMessage());
            }

            @Override
            public void onSuccess(String[] strings) {
                updateMsgArea(strings);
            }
        };
        msgSvc.getMessages(roomId, callback);
    }

    private void updateMsgArea(String[] strings) {
        StringBuffer res = new StringBuffer();
        for (int i = 0; i < strings.length; i++) {
            res.append(strings[i] + "\n");
        }
        msgArea.setText(res.toString());
    }

    private void login() {
        roomTable.setVisible(true);

        AsyncCallback<Integer[]> callback = new AsyncCallback<Integer[]>() {
            @Override
            public void onFailure(Throwable throwable) {
                errorLabel.setText("login failure\n"
                        + throwable.getMessage());
            }

            @Override
            public void onSuccess(Integer[] integers) {
                setRoomTable(integers);
            }
        };
        msgSvc.getRooms(callback);
    }

    private void checkUserName(String text) {
        AsyncCallback<Boolean> callback = new AsyncCallback<Boolean>() {
            @Override
            public void onFailure(Throwable throwable) {
                errorLabel.setText("checkUserName failed"
                        + throwable.getMessage());
            }

            @Override
            public void onSuccess(Boolean aBoolean) {
                if (aBoolean) {
                    login();
                } else {
                    errorLabel.setText("wrong username");
                }
            }
        };
        msgSvc.checkName(text, callback);
    }

    private void setRoomTable(Integer[] rooms) {
        for (int i = 0; i < rooms.length; i++) {
            final Integer curRoom = rooms[i];
            Button enterRoomBtn = new Button("" + curRoom);
            roomTable.setWidget(0, i, enterRoomBtn);
            enterRoomBtn.addClickHandler(new ClickHandler() {
                @Override
                public void onClick(ClickEvent clickEvent) {
                    enterRoom(curRoom);
                }
            });
        }
    }

    private void enterRoom(Integer curRoom) {
        msgPanel.setVisible(true);
        roomId = curRoom;
    }

}
