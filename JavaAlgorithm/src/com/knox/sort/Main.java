package com.knox.sort;

import com.knox.tools.Asserts;
import com.knox.tools.Integers;

import java.util.Arrays;

public class Main {

    public static void main(String[] args) {
        test_random();
    }


    static void test_random() {
        Integer[] array = Integers.random(50000, 20, 200000);

        testSorts(array,
                new InsertionSort(),
                // new BubbleSort(),
                // new SelectionSort(),
                new MergeSort(),
                new HeapSort(),
                new QuickSort()
                );
    }

    static void testSorts(Integer[] array, Sort... sorts) {
        for (Sort sort : sorts) {
            Integer[] newArray = Integers.copy(array);
            sort.sort(newArray);
            Asserts.testTrue(Integers.isAscOrder(newArray));
        }
        Arrays.sort(sorts);

        for (Sort sort : sorts) {
            System.out.println(sort);
        }
    }
}
