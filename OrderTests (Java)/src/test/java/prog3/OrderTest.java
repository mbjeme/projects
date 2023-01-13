/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit4TestClass.java to edit this template
 */
package fi.tuni.prog3.junitorder;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;
import java.util.List;
import java.util.NoSuchElementException;

/**
 *
 * @author mbjeme
 */
public class OrderTest {
    
    @Test
    public void testItemConstructor() {
        System.out.println("Item: constructor");
        Order.Item x = new Order.Item("apple", 3.6);
        assertEquals(x.getName(), "apple");
        Double price = x.getPrice();
        Double expPrice = 3.6;
        assertEquals(price, expPrice);
        
    }
    
    @Test
    public void testItemGetName() {
        System.out.println("Item: getName");
        Order.Item x = new Order.Item("apple", 3.6);
        String expResult = "apple";
        String result = x.getName();
        assertEquals(expResult, result);
    }
    
    @Test
    public void testItemGetPrice() {
        System.out.println("Item: getPrice");
        Order.Item x = new Order.Item("apple", 3.6);
        Double expResult = 3.6;
        Double result = x.getPrice();
        assertEquals(expResult, result);
    }
    
    @Test
    public void testItemToString() {
        System.out.println("Item: toString");
        Order.Item x = new Order.Item("apple", 3.6);
        String expResult = "Item(apple, 3.60)";
        String result = x.toString();
        assertEquals(expResult, result);
        
    }
    
    @Test
    public void testItemEquals() {
        System.out.println("Item: Equals");
        
        Order.Item x = new Order.Item("apple", 3.6);
        Order.Item y = new Order.Item("bpple", 2.0);
        assertEquals(false, x.equals(y));
        
        x = new Order.Item("apple", 3.6);
        y = new Order.Item("apple", 2.0);
        assertEquals(true, x.equals(y));
        
    }
    
    @Test
    public void testEntryConstructor() {
        System.out.println("Entry: constructor");
        Order.Item item = new Order.Item("apple", 3.6);
        Order.Entry x = new Order.Entry(item, 4);
        assertEquals(x.getItem(), item);
        assertEquals(x.getCount(), 4);
        
    }
    
    @Test
    public void testEntryGetItemName() {
        System.out.println("Entry: getItemName");
        Order.Item item = new Order.Item("apple", 3.6);
        Order.Entry x = new Order.Entry(item, 4);
        String expResult = "apple";
        String result = x.getItemName();
        assertEquals(expResult, result);
    }
    
    @Test
    public void testEntryGetUnitPrice() {
        System.out.println("Entry: getUnitPrice");
        Order.Item item = new Order.Item("apple", 3.6);
        Order.Entry x = new Order.Entry(item, 4);
        Double expResult = 3.6;
        Double result = x.getUnitPrice();
        assertEquals(expResult, result);
    }
    
    @Test
    public void testEntryGetItem() {
        System.out.println("Entry: getItem");
        Order.Item item = new Order.Item("apple", 3.6);
        Order.Entry x = new Order.Entry(item, 4);
        Order.Item expResult = item;
        Order.Item result = x.getItem();
        assertEquals(expResult, result);
    }
    
    @Test
    public void testEntryGetCount() {
        System.out.println("Entry: getCount");
        Order.Item item = new Order.Item("apple", 3.6);
        Order.Entry x = new Order.Entry(item, 4);
        Integer expResult = 4;
        Integer result = x.getCount();
        assertEquals(expResult, result);
    }
    
    @Test
    public void testEntryToString() {
        System.out.println("Item: toString");
        Order.Item item = new Order.Item("apple", 3.6);
        Order.Entry x = new Order.Entry(item, 4);
        String expResult = "4 units of Item(apple, 3.60)";
        String result = x.toString();
        assertEquals(expResult, result);
        
    }
    
    @Test
    public void whenIllegalArgumentExceptionThrown() {
        System.out.println("Order: whenIllegalArgument (item)");
        Order x = new Order();
        Order.Item item = new Order.Item("apple", 3.6);
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            x.addItems(item, 0);
        });
    }
    
    @Test
    public void whenIllegalStateExceptionThrown() {
        System.out.println("Order: whenIllegalState (item)");
        Order x = new Order();
        Order.Item item1 = new Order.Item("apple", 3.6);
        Order.Item item2 = new Order.Item("apple", 6.0);
        x.addItems(item2, 3);
        Exception exception = assertThrows(IllegalStateException.class, () -> {
            x.addItems(item1, 2);
        });
    }
    
    @Test
    public void testOrderconstructor() {
        System.out.println("Order: constructor");
        Order x = new Order();
        assertEquals(true, x.isEmpty());
        
        Order.Item item = new Order.Item("apple", 3.6);
        x.addItems(item, 2);
        
        assertEquals(false, x.isEmpty());
    }
    
    @Test
    public void whenIllegalArgumentExceptionThrownName() {
        System.out.println("Order: whenIllegalArgument (name)");
        Order x = new Order();
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            x.addItems("apple", 0);
        });
    }
    
    
    @Test
    public void whenNoSuchElementExceptionName() {
        System.out.println("Order: noSuchElement (name)");
        Order x = new Order();
        Exception exception = assertThrows(NoSuchElementException.class, () -> {
            x.addItems("apple", 2);
        });
        
    }
    
    
    
    @Test
    public void testAddItemsIncrementing() {
        System.out.println("Order: addItems -> Adding");
        Boolean inOrder = false;
        Order x = new Order();
        Order.Item item1 = new Order.Item("apple", 3.6);
        x.addItems(item1, 2);
        x.addItems(item1, 3);
        
        assertEquals(1, x.getEntryCount());
        assertEquals(5, x.getItemCount());
    }
    
    @Test
    public void testgetEntries() {
        System.out.println("Order: getEntries");
        Order x = new Order();
        Order.Item item1 = new Order.Item("apple", 3.6);
        Order.Item item2 = new Order.Item("milk", 6.0);
        Order.Entry entry1 = new Order.Entry(item1, 2);
        Order.Entry entry2 = new Order.Entry(item2, 4);
        x.addItems(item1, 2);
        x.addItems(item2, 4);
        
        List<Order.Entry> list = x.getEntries();
        
        assertEquals(entry1.getItemName(), list.get(0).getItemName());
        assertEquals(entry2.getItemName(), list.get(1).getItemName());
        
    }
    
    @Test
    public void testGetEntryCount() {
        System.out.println("Order: getEntryCount");
        Order x = new Order();
        Order.Item item1 = new Order.Item("apple", 3.6);
        Order.Item item2 = new Order.Item("milk", 6.0);
        x.addItems(item1, 2);
        x.addItems(item2, 4);
        
        Integer expResult = 2;
        Integer result = x.getEntryCount();
        assertEquals(expResult, result);
    }
    
    @Test
    public void testGetItemCount() {
        System.out.println("Order: getItemCount");
        Order x = new Order();
        Order.Item item1 = new Order.Item("apple", 3.6);
        Order.Item item2 = new Order.Item("milk", 6.0);
        x.addItems(item1, 2);
        x.addItems(item2, 4);
        
        Integer expResult = 6;
        Integer result = x.getItemCount();
        assertEquals(expResult, result);
    }
    
    @Test
    public void testGetTotalPrice() {
        System.out.println("Order: getTotalPrice");
        Order x = new Order();
        Order.Item item1 = new Order.Item("apple", 3.6);
        Order.Item item2 = new Order.Item("milk", 6.0);
        x.addItems(item1, 2);
        x.addItems(item2, 4);
        
        Double expResult = 31.2;
        Double result = x.getTotalPrice();
        assertEquals(expResult, result);
    }
    
    @Test
    public void testIsEmpty() {
        System.out.println("Order: isEmpty");
        
        Order x = new Order();
        assertEquals(true, x.isEmpty());
        
        Order.Item item = new Order.Item("apple", 3.6);
        x.addItems(item, 5);
        assertEquals(false, x.isEmpty()); 
    }
    
    @Test
    public void whenNoSuchElementExceptionThrownRemove() {
        System.out.println("Order: noSuchElement (removeItems)");
        Order x = new Order();
        Order.Item item = new Order.Item("apple", 3.6);
        x.addItems(item, 3);
        Exception exception = assertThrows(NoSuchElementException.class, () -> {
            x.removeItems("milk", 2);
        });
        
    }
    
    @Test
    public void whenIllegalArgumentExceptionThrownRemove() {
        System.out.println("Order: whenIllegalArgument (removeItems)");
        Order x = new Order();
        Order.Item item = new Order.Item("apple", 3.6);
        x.addItems(item, 3);
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            x.removeItems("apple", 6);
        });
        
    }
    
    
    @Test
    public void testItemConstructorNullName() {
        System.out.println("Item: Constructor 1");
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            Order.Item item = new Order.Item(null, 3.6);
        });
    }
    
    @Test
    public void testItemConstructorNegValue() {
        System.out.println("Item: Constructor 1");
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            Order.Item item = new Order.Item("apple", -1.0);
        });
    }
    
    @Test
    public void testEntryConstructorNegValue() {
        System.out.println("Item: Constructor 1");
        Order.Item item = new Order.Item("apple", 3.6);
        Exception exception = assertThrows(IllegalArgumentException.class, () -> {
            Order.Entry x = new Order.Entry(item, -1);
        });
    }
    
    @Test
    public void testAddItems1 () {
        Order.Item item1 = new Order.Item("apple", 3.6);
        Order.Item item2 = new Order.Item("milk", 6.0);
        Order x = new Order();
        x.addItems(item1, 2);
        x.addItems(item2, 3);
        
        assertEquals(5,x.getItemCount());
        assertEquals(2, x.getEntryCount());
    }
    
    @Test
    public void testAddItems2 () {
        Order.Item item1 = new Order.Item("apple", 3.6);
        Order x = new Order();
        x.addItems(item1, 2);
        x.addItems("apple", 3);
        
        assertEquals(5,x.getItemCount());
        assertEquals(1, x.getEntryCount());
    }
    
    @Test
    public void testRemove1() {
        Order.Item item1 = new Order.Item("apple", 3.6);
        Order.Item item2 = new Order.Item("milk", 6.0);
        Order x = new Order();
        x.addItems(item1, 2);
        x.addItems(item2, 3);
        
        x.removeItems("apple", 1);
        
        assertEquals(4,x.getItemCount());
        assertEquals(2, x.getEntryCount());
    }
    
    @Test
    public void testRemove2() {
        Order.Item item1 = new Order.Item("apple", 3.6);
        Order.Item item2 = new Order.Item("milk", 6.0);
        Order x = new Order();
        x.addItems(item1, 2);
        x.addItems(item2, 3);
        
        x.removeItems("apple", 2);
        
        assertEquals(3,x.getItemCount());
        assertEquals(1, x.getEntryCount());
    }
    
    
    
    
    
}
