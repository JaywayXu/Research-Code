package clock;

import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class Main {
    public static void main(String[] args) {
        Frame win = new Frame();
        win.add(new Clock(),BorderLayout.CENTER);
        win.setVisible(true);
        win.setSize(250,300);
        win.validate();
        win.addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent windowEvent) {
                System.exit(0);
            }
        });
    }
}
