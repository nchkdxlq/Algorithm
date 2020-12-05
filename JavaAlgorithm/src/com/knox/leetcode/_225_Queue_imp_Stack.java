package com.knox.leetcode;

import java.util.LinkedList;
import java.util.Queue;

public class _225_Queue_imp_Stack {

    private static class MyStack {

        private Queue<Integer> queue = new LinkedList<>();

        /** Initialize your data structure here. */
        public MyStack() {

        }

        /** Push element x onto stack. */
        public void push(int x) {
            queue.add(x);
        }

        /** Removes the element on top of the stack and returns that element. */
        public int pop() {
            int size = queue.size();
            for (int i = 0; i < size -1; i++) {
                queue.add(queue.poll());
            }
            return queue.poll();
        }

        /** Get the top element. */
        public int top() {
            int size = queue.size();
            /*
            * 栈需要FIFO, 栈的top元素, 在队列中为最后一个元素, 所以需要把前size-1元素先出队在入队,
            * 此时队列中的最后一个元素就在队头了, 也就是栈顶元素, 最后把最后一个元素出队再入队就还原了队列
            * */
            for (int i = 0; i < size -1; i++) {
                queue.add(queue.poll());
            }
            int top = queue.poll();
            queue.add(top);
            return top;
        }

        /** Returns whether the stack is empty. */
        public boolean empty() {
            return queue.isEmpty();
        }
    }


    public static void main(String[] args) {

    }
}
