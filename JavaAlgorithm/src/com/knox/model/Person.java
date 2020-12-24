package com.knox.model;

import com.knox.hash.HashCode;

import java.util.Objects;

public class Person implements Comparable {
    int age;
    float height;
    String name;

    public Person(int age, float height, String name) {
        this.age = age;
        this.height = height;
        this.name = name;
    }


    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Person person = (Person) o;
        return age == person.age &&
                Float.compare(person.height, height) == 0 &&
                Objects.equals(name, person.name);
    }

    @Override
    public int compareTo(Object o) {
        return age - ((Person)o).age;
    }

    @Override
    public int hashCode() {
        // return Objects.hash(age, height, name); 官方写法
        int hashCode = Integer.hashCode(age);
        hashCode = hashCode * 31 + Float.hashCode(height);
        hashCode = hashCode * 31 + (name != null ? name.hashCode() : 0);
        return hashCode;
    }


}