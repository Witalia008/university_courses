package drawing;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.*;
import java.util.List;

/**
 * Created by Witalia on 03.12.2014.
 */
public class DrawablePanel extends JPanel implements MouseListener {
    private ServerSocket serverSocket;
    private Socket clientSocket;
    private ObjectOutputStream oos;
    private ObjectInputStream ois;

    private int width;
    private int height;
    private BufferedImage image;
    private Graphics g;

    private List<Drawable> list = new ArrayList<>();

    public void setCur(String name) {
        this.cur = DrawableFactory.getDrawable(name);
    }

    private Color bgCol;
    private Color fgCol;

    public void setBgCol(Color bgCol) {
        this.bgCol = bgCol;
    }

    public void setFgCol(Color fgCol) {
        this.fgCol = fgCol;
    }

    private Drawable cur;

    public void clean() {
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, width, height);
    }

    public DrawablePanel(int width, int height, boolean isServer) throws IOException {
        if (isServer) {
            serverSocket = new ServerSocket(27015);
            clientSocket = serverSocket.accept();
        } else {
            clientSocket = new Socket("127.0.0.1", 27015);
        }
        oos = new ObjectOutputStream(clientSocket.getOutputStream());
        ois = new ObjectInputStream(clientSocket.getInputStream());
        if (!isServer) {
            new Thread(() -> {
                try {
                    for (;;) {
                        if (ois != null) {
                            draw((Drawable) ois.readObject());
                        }
                        Thread.sleep(100);
                    }
                } catch (InterruptedException | IOException | ClassNotFoundException e) {
                    e.printStackTrace();
                }
            }).start();
        }

        this.width = width;
        this.height = height;
        image = new BufferedImage(width, height, BufferedImage.TYPE_INT_RGB);
        g = image.createGraphics();
        clean();

        addMouseListener(this);
        setPreferredSize(new Dimension(width, height));
        setVisible(true);
    }

    public void draw(Drawable x) {
        if (x != null) {
            list.add(x);
            x.draw(g);
            repaint();
            if (serverSocket != null && clientSocket != null) {
                try {
                    oos.writeObject(cur);
                    oos.reset();
                } catch (IOException e1) {
                    e1.printStackTrace();
                }
            }
        }
    }

    public void save(String filename) {
        try {
            FileOutputStream fos = new FileOutputStream(new File(filename));
            save(fos);
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void save(OutputStream out) {
        try {
            ObjectOutputStream oos = new ObjectOutputStream(out);
            oos.writeObject(list.size());
            for (Drawable cur : list) {
                oos.writeObject(cur);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void read(String filename) {
        try {
            FileInputStream fis = new FileInputStream(new File(filename));
            read(fis);
            fis.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void read(InputStream in) {
        try {
            ObjectInputStream ois = new ObjectInputStream(in);
            int howMany = ((Integer) ois.readObject());
            list = new ArrayList<>();
            clean();
            for (; howMany-- > 0;) {
                Object cur = ois.readObject();
                if (cur instanceof Drawable) {
                    draw((Drawable) cur);
                    list.add((Drawable) cur);
                }
            }
        } catch (ClassNotFoundException | IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    protected void paintComponent(Graphics g) {
        g.drawImage(image, 0, 0, null);
    }

    @Override
    public void mouseClicked(MouseEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {
        if (cur != null) {
            cur.setLu(e.getPoint());
        }
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        if (cur != null) {
            cur.setFgColor(fgCol);
            cur.setBgColor(bgCol);
            cur.setRd(e.getPoint());
            draw(cur);
        }
    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }
}
