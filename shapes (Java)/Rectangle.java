/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */

/**
 *
 * @author mbjeme
 */
public class Rectangle implements IShapeMetrics {
    private double height_;
    private double width_;
    
    public Rectangle(double height, double width) {
        height_ = height;
        width_ = width;
    }
    
    public String toString() {
        String line = String.format("Rectangle with height %.2f and width %.2f", 
                height_, width_);
        return line;
    }
    
    public String name() {
        String line = "rectangle";
        return line;
    }

    public double area() {
        double answer = height_*width_;
        return answer;
    }
    
    public double circumference() {
        double answer = 2*height_ + 2*width_;
        return answer;
    }
    
}
