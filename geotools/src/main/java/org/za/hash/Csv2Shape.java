package org.za.hash;

import com.vividsolutions.jts.geom.Coordinate;
import com.vividsolutions.jts.geom.GeometryFactory;
import com.vividsolutions.jts.geom.Point;
import com.vividsolutions.jts.geom.impl.PackedCoordinateSequence;
import org.geotools.data.DataUtilities;
import org.geotools.data.simple.SimpleFeatureCollection;
import org.geotools.feature.FeatureCollections;
import org.geotools.feature.SchemaException;
import org.geotools.feature.simple.SimpleFeatureBuilder;
import org.geotools.geometry.jts.JTSFactoryFinder;
import org.geotools.swing.data.JFileDataStoreChooser;
import org.opengis.feature.simple.SimpleFeature;
import org.opengis.feature.simple.SimpleFeatureType;

import java.io.*;

/**
 * Hello world!
 *
 */
public class Csv2Shape
{
    public static void main( String[] args ) throws SchemaException, IOException {
        File file = JFileDataStoreChooser.showOpenFile("csv", null);
        if (file == null)
            return;

        SimpleFeatureType TYPE = DataUtilities.createType("Location",
                    "location:Point:srid=4326," +
                            "name=String," +
                            "number:Integer"
                    );

        SimpleFeatureCollection collection = FeatureCollections.newCollection();

        GeometryFactory geometryFactory = JTSFactoryFinder.getGeometryFactory(null);

        SimpleFeatureBuilder featureBuilder = new SimpleFeatureBuilder(TYPE);

        try(BufferedReader reader = new BufferedReader(new FileReader(file))) {

            String line = reader.readLine();
            System.out.println("Header: " + line);

            for (line = reader.readLine(); line != null; line = reader.readLine()) {
                if(line.trim().length() > 0) {
                    String tokens[] = line.split("\\,");

                    double lat = Double.parseDouble(tokens[0]);
                    double lon = Double.parseDouble(tokens[1]);
                    String name = tokens[2].trim();
                    int number = Integer.parseInt(tokens[3].trim());

                    Point point = geometryFactory.createPoint(new Coordinate(lon, lat));

                    featureBuilder.add(point);
                    featureBuilder.add(name);
                    featureBuilder.add(number);

                    SimpleFeature feature = featureBuilder.buildFeature(null);
                    collection.add(feature);
                }
            }

        }
    }
}
