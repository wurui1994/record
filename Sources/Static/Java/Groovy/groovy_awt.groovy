import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;

frame = new Frame()
frame.addWindowListener(new WindowAdapter(){
    public void windowClosing(WindowEvent windowEvent) {
        System.exit(0);
    }
});
frame.setSize(400,400)
frame.setLocationRelativeTo(null);
frame.show()

image = new BufferedImage(400,400,BufferedImage.TYPE_INT_RGB)
frame.paint(image.getGraphics())
g=frame.graphics
g.setPaint(Color.cyan)
g.drawLine(0,0,100,100)
// :q