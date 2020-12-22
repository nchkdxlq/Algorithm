package com.knox.hash;

import java.util.Objects;

public class HashCode {

    static class Person {
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
        public int hashCode() {
            return Objects.hash(age, height, name);
        }
    }



    public static void main(String[] args) {

        test_person();
    }

    private static void test_person() {
        Person p1 = new Person(10, 155.0f, "rose");
    }

}
