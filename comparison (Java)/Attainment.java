import java.util.Collections;
import java.util.Comparator;
/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Other/File.java to edit this template
 */

/**
 *
 * @author Jenna
 */
public class Attainment implements Comparable<Attainment> {
    private String code_;
    private String student_num_;
    private int grade_;
    
    public int compareTo(Attainment x) {
        if (!student_num_.equals(x.student_num_)) {
            return student_num_.compareToIgnoreCase(x.student_num_);
        }
        if (!code_.equals(x.code_)) {
            return code_.compareToIgnoreCase(x.code_);
        }
        return 0;
    }
    
    public Attainment(String courseCode, String studentNumber, int grade) {
        code_ = courseCode;
        student_num_ = studentNumber;
        grade_ = grade;
    }
    
    public String getCourseCode() {
        return code_;
    }
    
    public String getStudentNumber() {
        return student_num_;
    }
    
    public int getGrade() {
        return grade_;
    }
    
    public String toString() {
        String line = String.format("%s %s %d\n", code_, student_num_, grade_);
        return line;
    }
    
    public static final Comparator<Attainment> CODE_STUDENT_CMP = new 
        Comparator<Attainment>() {
            @Override
            public int compare(Attainment a, Attainment b) {
                if (!a.code_.equals(b.code_)) {
                    return a.code_.compareToIgnoreCase(b.code_);
                }
                if (!a.student_num_.equals(b.student_num_)) {
                    return a.student_num_.compareToIgnoreCase(b.student_num_);
                }
                return 0;
            }
    };
    
    public static final Comparator<Attainment> CODE_GRADE_CMP = new Comparator<Attainment>() {
            @Override
            public int compare(Attainment a, Attainment b) {
                if (!a.code_.equals(b.code_)) {
                    return a.code_.compareToIgnoreCase(b.code_);
                }
                if (a.grade_ != b.grade_) {
                    int agrade = a.grade_;
                    int bgrade = b.grade_;
                    return bgrade-agrade;
                }
                return 0;
            }
    };
            
    
    

    
}

