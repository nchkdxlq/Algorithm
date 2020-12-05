package com.knox.leetcode;

import com.knox.Asserts;

import java.util.HashMap;
import java.util.Stack;


/*
* 20. 有效的括号 https://leetcode-cn.com/problems/valid-parentheses/
*
* 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
* 有效字符串需满足：
*   1. 左括号必须用相同类型的右括号闭合。
*   2. 左括号必须以正确的顺序闭合。
* 注意空字符串可被认为是有效字符串。
*
* */

public class _020_isValid {

    static class Solution {
        public boolean isValid(String s) {
            return isValid_v3(s);
        }

        private boolean isValid_v3(String s) {
            if (s == null || s.length() == 0) return true;
            if (s.length() % 2 == 1) return false;

            Stack<Character> stack = new Stack<>();
            for (int i = 0; i < s.length(); i++) {
                Character ch = s.charAt(i);
                switch (ch) {
                    case '(':
                    case '[':
                    case '{':
                        stack.push(ch);
                        break;
                    default:
                        // 注意栈判空
                        if (stack.isEmpty()) return false;
                        Character top = stack.peek();
                        if (ch == ')' && top == '('
                                || ch == ']' && top == '['
                                || ch == '}' && top == '{' ) {
                            stack.pop();
                        } else  {
                            return false;
                        }
                }
            }

            return stack.isEmpty();
        }

        private boolean isValid_v2(String s) {
            if (s.length() == 0) return true;

            Stack<Character> left = new Stack<>();
            Stack<Character> right = new Stack<>();

            for (int i = 0; i < s.length(); i++) {
                Character ch = s.charAt(i);
                switch (ch) {
                    case '(' :
                        left.push(ch);
                        right.push(')');
                        break;
                    case '[' :
                        left.push(ch);
                        right.push(']');
                        break;
                    case '{' :
                        left.push(ch);
                        right.push('}');
                        break;
                    default:
                        if (right.isEmpty()) return false;
                        if (ch.equals(right.peek())) {
                            left.pop();
                            right.pop();
                        } else {
                            return false;
                        }
                }
            }

            return left.isEmpty() && right.isEmpty();
        }


        private boolean isValid_v1(String s) {
            if (s.isEmpty()) return true;

            HashMap<Character, Character> map = new HashMap<>();
            map.put('(', ')');
            map.put('[', ']');
            map.put('{', '}');

            Stack<Character> stack = new Stack<>();

            for (int i = 0; i < s.length(); i++) {
                char c = s.charAt(i);
                if (map.containsKey(c)) { // 左括号
                    stack.push(c);
                } else if (stack.isEmpty()) {
                    return false;
                } else {
                    char expected = map.get(stack.peek()); // 栈顶的元素对应的右括号
                    if (c == expected) {
                        stack.pop();
                    } else {
                        return false;
                    }
                }
            }

            return stack.isEmpty();
        }

    }


    public static void main(String[] args) {
        Solution ins = new Solution();

        {
            String str = "";
            Asserts.testTrue(ins.isValid(str));
        }

        {
            String str = "()";
            Asserts.testTrue(ins.isValid(str));
        }

        {
            String str = "()[]{}";
            Asserts.testTrue(ins.isValid(str));
        }

        {
            String str = "([)]";
            Asserts.testFalse(ins.isValid(str));
        }

        {
            String str = "{[]}";
            Asserts.testTrue(ins.isValid(str));
        }

    }

}
