import javafx.scene.control.ProgressBar;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.*;
import java.nio.channels.FileLock;
import java.util.Random;

/**
 * Created by Witalia on 27.10.2014.
 */
public class FileReaderGUI extends JFrame
        implements PropertyChangeListener, ActionListener {
    private JProgressBar progressBar;
    private JTextArea consoleLog;
    private JButton startButton;
    private JButton stopButton;
    private Task task;
    private JList list;
    private DefaultListModel listModel;
    private Database database = new Database();
    private Report report = new Report();

    @Override
    public void propertyChange(PropertyChangeEvent evt) {
        if (evt.getPropertyName() == "progress") {
            int progress = (Integer) evt.getNewValue();
            progressBar.setValue(progress);

            if (progress == listModel.getSize()) {
                progressBar.setIndeterminate(true);
            }
        }
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        switch (e.getActionCommand()) {
            case "start":
                startButton.setEnabled(false);
                stopButton.setEnabled(true);
                setCursor(Cursor.getPredefinedCursor(Cursor.WAIT_CURSOR));

                consoleLog.setText("");

                task = new Task();
                task.addPropertyChangeListener(this);
                task.execute();
                break;
            case "stop":
                task.interrupt();
                break;
        }
    }

    class Task extends SwingWorker<Void, Void> {
        private boolean interrupted;
        @Override
        protected Void doInBackground() throws Exception {
            interrupted = false;
            progressBar.setMaximum(listModel.getSize());

            for (int i = 0; i < listModel.getSize() && !interrupted; i++) {
                String fileURL = listModel.getElementAt(i).toString();
                consoleLog.append("Reading file "
                                + listModel.getElementAt(i).toString()
                );
                String result = FileReader.readFile(fileURL);
                consoleLog.append(" completed with error "
                                + result + "\n");

                consoleLog.append("Adding record to database\n");
                database.insert(fileURL, result == null, result);

                setProgress(i + 1);
            }

            consoleLog.append("Creating report\n");
            report.print(database);
            consoleLog.append("Exporting to Excel\n");
            report.exportToExcel();

            return null;
        }

        @Override
        protected void done() {
            startButton.setEnabled(true);
            stopButton.setEnabled(false);
            setCursor(null);

            if (interrupted) {
                consoleLog.append("Interrupted.\n");
            }
            else {
                consoleLog.append("Done.\n");
            }

            progressBar.setIndeterminate(false);
        }

        void interrupt() {
            interrupted = true;
        }
    }

    public FileReaderGUI() {
        super("File Loader via HTTP");
        setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        setLayout(new BorderLayout());
        setPreferredSize(new Dimension(600, 400));

        progressBar = new JProgressBar(0, 100);
        progressBar.setValue(0);
        progressBar.setStringPainted(true);

        consoleLog = new JTextArea(5, 20);
        consoleLog.setEditable(false);

        startButton = new JButton("Start");
        startButton.setActionCommand("start");
        startButton.addActionListener(this);

        stopButton = new JButton("Stop");
        stopButton.setActionCommand("stop");
        stopButton.addActionListener(this);
        stopButton.setEnabled(false);

        JButton deleteButton = new JButton("Delete");
        deleteButton.addActionListener(e -> {
            int[] selected = list.getSelectedIndices();
            for (int i = selected.length - 1; i >= 0; i--) {
                listModel.removeElementAt(selected[i]);
            }
        });

        JButton loadButton = new JButton("Load");
        loadButton.addActionListener(e -> {
            FileDialog fileOpen = new FileDialog(this);
            fileOpen.setVisible(true);
            if (fileOpen.getFile() != null) {
                loadListFromFile(fileOpen.getDirectory() + fileOpen.getFile());
            }
        });
        JButton saveButton = new JButton("Save");
        saveButton.addActionListener(e -> {
            FileDialog fileSave = new FileDialog(this);
            fileSave.setVisible(true);
            if (fileSave.getFile() != null) {
                saveListToFile(fileSave.getDirectory() + fileSave.getFile());
            }
        });

        listModel = new DefaultListModel();
        list = new JList(listModel);

        TextField newItemField = new TextField();
        newItemField.addActionListener(e -> {
            listModel.addElement(newItemField.getText());
            newItemField.setText("");
        });

        JPanel listPanel = new JPanel(new BorderLayout());
        listPanel.add(new JScrollPane(list), BorderLayout.CENTER);
        listPanel.add(newItemField, BorderLayout.SOUTH);

        JPanel buttonPanel = new JPanel(new GridLayout(10, 1));
        buttonPanel.add(startButton);
        buttonPanel.add(stopButton);
        buttonPanel.add(deleteButton);
        buttonPanel.add(loadButton);
        buttonPanel.add(saveButton);

        JPanel progressPanel = new JPanel(new BorderLayout());
        progressPanel.add(new JScrollPane(consoleLog), BorderLayout.NORTH);
        progressPanel.add(progressBar, BorderLayout.SOUTH);

        getContentPane().add(listPanel, BorderLayout.CENTER);
        getContentPane().add(progressPanel, BorderLayout.SOUTH);
        getContentPane().add(buttonPanel, BorderLayout.EAST);

        pack();
        setVisible(true);
    }

    private void saveListToFile(String fileName) {
        if (fileName == null) {
            return;
        }
        try {
            PrintWriter out = new PrintWriter(new File(fileName));
            for (int i = 0; i < listModel.getSize(); ++i) {
                out.println(listModel.elementAt(i).toString());
            }
            out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    private void loadListFromFile(String fileName) {
        if (fileName == null) {
            return;
        }
        listModel.clear();
        try {
            BufferedReader in = new BufferedReader(
                    new InputStreamReader(new FileInputStream(fileName))
            );
            String inputLine;
            while ((inputLine = in.readLine()) != null) {
                listModel.addElement(inputLine);
            }
            in.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static void main(String[] args) {
        javax.swing.SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                new FileReaderGUI();
            }
        });
    }
}
