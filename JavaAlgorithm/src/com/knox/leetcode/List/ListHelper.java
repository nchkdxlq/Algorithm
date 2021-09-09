package com.knox.leetcode.List;

import java.util.ArrayList;
import java.util.List;

public class ListHelper {

    public static List<Integer> listFromArray(int[] array) {
        ArrayList<Integer> list = new ArrayList<>();
        for (int value : array) {
            list.add(value);
        }
        return list;
    }

    public static List<List<Integer>> listFromArray(int[][] array) {
        List<List<Integer>> list = new ArrayList<>();
        for (int[] value : array) {
            list.add(listFromArray(value));
        }
        return list;
    }

}
