package sample;

import com.sun.jna.NativeLibrary;
import uk.co.caprica.vlcj.player.MediaPlayerFactory;
import uk.co.caprica.vlcj.player.embedded.EmbeddedMediaPlayer;

import javax.swing.*;
import java.awt.*;

/**
 * Created by Witalia on 28.11.2014.
 */
public class PlayerPanel extends JPanel {
    protected EmbeddedMediaPlayer player;
    protected String mediaURL;

    public PlayerPanel() {
        setLayout(new BorderLayout());

        NativeLibrary.addSearchPath("libvlc",
                "D:\\Cloud\\OneDrive\\My Computer\\Projects\\ProgInUniv" +
                        "\\3 Course\\1 Sem\\HomeTasks\\26\\vlc-2.1.5");
        MediaPlayerFactory mediaPlayerFactory = new MediaPlayerFactory();
        Canvas canvas = new Canvas();
        player = mediaPlayerFactory.newEmbeddedMediaPlayer();
        player.setVideoSurface(mediaPlayerFactory.newVideoSurface(canvas));
        add(canvas, BorderLayout.CENTER);
    }

    public void setMediaURL(String mediaURL) {
        this.mediaURL = mediaURL;
    }

    public void play() {
        player.playMedia(mediaURL);
    }
}