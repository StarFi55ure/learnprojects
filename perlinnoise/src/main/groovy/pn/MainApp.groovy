package pn

import com.flowpowered.noise.module.Module
import com.flowpowered.noise.module.combiner.Select
import com.flowpowered.noise.module.modifier.ScaleBias
import com.flowpowered.noise.module.modifier.Turbulence
import com.flowpowered.noise.module.source.Billow
import com.flowpowered.noise.module.source.Perlin
import com.flowpowered.noise.module.source.RidgedMulti
import groovy.swing.SwingBuilder
import javax.swing.*
import java.awt.Color
import java.awt.Graphics
import java.awt.image.BufferedImage

<<<<<<< HEAD

=======
>>>>>>> a0ab4e45f88528bfbe03eeb260783957ebf8bf7e
class Main {
    static void main(String[] args) {
        println "Learning Perlin Noise Project";

        RidgedMulti mountainTerrain = new RidgedMulti();

        Billow baseFlatTerrain = new Billow();
        baseFlatTerrain.setFrequency(2.0d);

        ScaleBias flatTerrain = new ScaleBias();
        flatTerrain.setSourceModule(0, baseFlatTerrain);
        flatTerrain.setScale(0.125d);
        flatTerrain.setBias(-0.75d);

        Perlin terrainType = new Perlin();
        terrainType.setFrequency(1d);
        terrainType.setPersistence(0.25d);

        Select terrainSelector = new Select();
        terrainSelector.setSourceModule(0, flatTerrain);
        terrainSelector.setSourceModule(1, mountainTerrain);
        terrainSelector.setControlModule(terrainType);
        terrainSelector.setBounds(1000.0, 0.0);
        terrainSelector.setEdgeFalloff(0.125);

        Turbulence finalTerrain = new Turbulence();
        finalTerrain.setSourceModule(0, terrainSelector);
        finalTerrain.setFrequency(2.0);
        finalTerrain.setPower(0.125);

        int windowsize = 512;
        println "Generating noise map"
        NoiseMap noiseMap = new NoiseMap();
        noiseMap.source = finalTerrain;
        noiseMap.setSize(windowsize, windowsize);
        noiseMap.setBounds(2.0, 6.0, 1.0, 5.0);
        noiseMap.build();

        println "Rendering image map from noise map"
        ImageRenderer imageRnd = new ImageRenderer();
        imageRnd.noiseMap = noiseMap;
        imageRnd.clearRampPoints();
//        imageRnd.addRampPoint(-1.0d, new Color(0, 0, 128));
//        imageRnd.addRampPoint(-0.25d, new Color(0, 0, 255));
//        imageRnd.addRampPoint(0d, new Color(0, 128, 255));
//        imageRnd.addRampPoint(0.0625d, new Color(240, 240, 64));
//        imageRnd.addRampPoint(0.125d, new Color(32, 160, 0));
//        imageRnd.addRampPoint(0.375d, new Color(224, 224, 0));
//        imageRnd.addRampPoint(0.75d, new Color(128, 128, 128));
//        imageRnd.addRampPoint(1.0d, Color.WHITE);

        imageRnd.addRampPoint(-1.0d, new Color(32, 160, 0));
        imageRnd.addRampPoint(-0.25d, new Color(224, 224, 0));
        imageRnd.addRampPoint(0.25d, new Color(128, 128, 128));
        imageRnd.addRampPoint(1.0d, new Color(255, 255, 255));

        BufferedImage img = imageRnd.renderImage();

        // Show the image
        println "Showing interface"
        def myapp = new SwingBuilder();

        def myframe = myapp.dialog(title: "Test bench",
            location: [100, 100], size: [windowsize, windowsize],
            defaultCloseOperation: WindowConstants.DISPOSE_ON_CLOSE) {

            panel(new ImagePanel(img))
        }

        myframe.setVisible(true);

    }
}

class NoiseMap {

    Module source;
    int x;
    int z;
    double x_lower;
    double x_higher;
    double z_lower;
    double z_higher;

    double[][] nMap;


    void setSize(int x, int y) {
        this.x = x;
        this.z = y;
    }

    void setBounds(double x_lower, double x_higher, double z_lower, double z_higher) {
        this.x_lower = x_lower;
        this.x_higher = x_higher;
        this.z_lower = z_lower;
        this.z_higher = z_higher;
    }

    double getPixelValue(int x, int z) {
        return nMap[x][z];
    }

    void build() {

        if (nMap == null) {
            nMap = new double[x][z];
        }

        // fill map with data
        for (int x = 0; x < this.x; x++) {
            for (int z = 0; z < this.z; z++) {
                nMap[x][z] = source.getValue(mapX(x), 0.0, mapZ(z));
            }
        }
    }

    double mapX(int xVal) {
        return x_lower + ((xVal / (double)this.x) * (x_higher - x_lower));
    }

    double mapZ(int zVal) {
        return z_lower + ((zVal / (double)this.z) * (z_higher - z_lower));
    }
}

class ImageRenderer {

    NoiseMap noiseMap;

    Map<Double, Color> rampPoints;

    ImageRenderer() {
        rampPoints = new HashMap<>();
    }

    BufferedImage renderImage() {
        BufferedImage destImage = new BufferedImage(noiseMap.x, noiseMap.z, BufferedImage.TYPE_INT_RGB);

        for (int x = 0; x < noiseMap.x; x++) {
            for (int z = 0; z < noiseMap.z; z++) {
                def c = getGradientColorValue(noiseMap.getPixelValue(x, z));
                int rgb = c.getRGB();
                destImage.setRGB(x, z, rgb);
            }
        }

        return destImage;
    }

    void clearRampPoints() {
        rampPoints.clear();
    }

    void addRampPoint(Double d, Color c) {
        rampPoints.put(d, c);
    }

    Color getGradientColorValue(double value) {

        value = Math.max(value, -1.0d);
        value = Math.min(value, 1.0d);

        if (value < -1.0d || value > 1.0d) {
            println "error value $value"
        }

        Set<Double> rampPointKeyValues = rampPoints.keySet();

        double higherVal = 1.0d;
        for(Double d: rampPointKeyValues) {
            if ((d.doubleValue() > value) && (d.doubleValue() < higherVal)) {
                higherVal = d.doubleValue()
            }
        }

        double lowerVal = -1.0d;
        for (Double d: rampPointKeyValues) {
            if ((d.doubleValue() < value) && (d.doubleValue() > lowerVal)) {
                lowerVal = d.doubleValue();
            }
        }

        double lerpRatio = (value - lowerVal) / (higherVal - lowerVal);

        Color lowerCol = rampPoints.get(lowerVal);
        int x0_red = lowerCol.getRed();
        int x0_green = lowerCol.getGreen();
        int x0_blue = lowerCol.getBlue();

        Color higherCol = rampPoints.get(higherVal);
        int x1_red = higherCol.getRed();
        int x1_green = higherCol.getGreen();
        int x1_blue = higherCol.getBlue();

        int x_red = x0_red + (lerpRatio * (x1_red - x0_red));
        int x_green = x0_green + (lerpRatio * (x1_green - x0_green));
        int x_blue = x0_blue + (lerpRatio * (x1_blue - x0_blue));
        //println "r $x_red g $x_green b $x_blue lr $lerpRatio diff ${x1_blue - x0_blue}"

        Color xL = new Color(x_red, x_green, x_blue);
        return xL;
    }
}

class ImagePanel extends JPanel {

    BufferedImage img;

    ImagePanel(BufferedImage img) {
        this.img = img
    }

    @Override
    protected void paintComponent(Graphics graphics) {
        super.paintComponent(graphics);
        graphics.drawImage(img, 0, 0, null);
    }
}