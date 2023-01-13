
/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */

/**
 *
 * @author mbjeme
 */
public class Circle implements IShapeMetrics {
    private double radius_;
    
    public Circle(double radius) {
        radius_ = radius;
    }
    
    public String toString() {
        String line = String.format("Circle with radius: %.2f", radius_);
        return line;
    }
    
    public String name() {
        String line = "circle";
        return line;
    }
    
    public double area() {
        double answer = (PI)*radius_*radius_;
        
        
        return answer;
    }
    
    public double circumference() {
        double answer = 2*(PI)*radius_;
        return answer;
    }
}
