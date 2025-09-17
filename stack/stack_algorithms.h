#ifndef STACK_ALGORITHMS_H
#define STACK_ALGORITHMS_H

#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <cctype>
#include <optional>
#include <sstream>
#include <algorithm>

/*
  stack_algorithms.h
  Implements:
    • Balanced parentheses check
    • Next greater element
    • MinStack (O(1) min)
    • Evaluate postfix expression
    • Evaluate prefix expression
    • Largest rectangle in histogram
    • Monotonic stack (generic utility)
    • Infix → Postfix conversion
*/

namespace stackalgo {

    // ================================
    // Balanced parentheses
    // ================================
    inline bool balanced_parentheses(const std::string &s) {
        std::stack<char> st;
        std::unordered_map<char,char> match = {{')','('}, {']','['}, {'}','{'}};
        for (char c : s) {
            if (c=='('||c=='['||c=='{') st.push(c);
            else if (c==')'||c==']'||c=='}') {
                if (st.empty() || st.top()!=match[c]) return false;
                st.pop();
            }
        }
        return st.empty();
    }

    // ================================
    // Next Greater Element
    // ================================
    template<typename T>
    std::vector<std::optional<T>> next_greater(const std::vector<T> &arr) {
        std::vector<std::optional<T>> res(arr.size());
        std::stack<T> st;
        for (int i=(int)arr.size()-1; i>=0; --i) {
            while (!st.empty() && st.top() <= arr[i]) st.pop();
            res[i] = st.empty()? std::optional<T>() : std::optional<T>(st.top());
            st.push(arr[i]);
        }
        return res;
    }

    // ================================
    // MinStack (support O(1) min)
    // ================================
    template<typename T>
    class MinStack {
    private:
        std::stack<T> st, minSt;
    public:
        void push(const T &x) {
            st.push(x);
            if (minSt.empty() || x <= minSt.top()) minSt.push(x);
        }
        void pop() {
            if (st.empty()) return;
            if (st.top() == minSt.top()) minSt.pop();
            st.pop();
        }
        T top() const { return st.top(); }
        bool empty() const { return st.empty(); }
        size_t size() const { return st.size(); }
        T getMin() const { return minSt.top(); }
    };

    // ================================
    // Evaluate Postfix Expression
    // ================================
    inline int eval_postfix(const std::string &expr) {
        std::stack<int> st;
        std::istringstream iss(expr);
        std::string token;
        while (iss >> token) {
            if (isdigit(token[0]) || 
                (token.size()>1 && (token[0]=='-'||token[0]=='+') && isdigit(token[1]))) {
                st.push(std::stoi(token));
            } else {
                int b = st.top(); st.pop();
                int a = st.top(); st.pop();
                if (token=="+") st.push(a+b);
                else if (token=="-") st.push(a-b);
                else if (token=="*") st.push(a*b);
                else if (token=="/") st.push(a/b);
            }
        }
        return st.top();
    }

    // ================================
    // Evaluate Prefix Expression
    // ================================
    inline int eval_prefix(const std::string &expr) {
        std::stack<int> st;
        std::istringstream iss(expr);
        std::vector<std::string> tokens;
        std::string token;
        while (iss >> token) tokens.push_back(token);
        for (int i=(int)tokens.size()-1; i>=0; --i) {
            const std::string &tok = tokens[i];
            if (isdigit(tok[0]) || 
                (tok.size()>1 && (tok[0]=='-'||tok[0]=='+') && isdigit(tok[1]))) {
                st.push(std::stoi(tok));
            } else {
                int a = st.top(); st.pop();
                int b = st.top(); st.pop();
                if (tok=="+") st.push(a+b);
                else if (tok=="-") st.push(a-b);
                else if (tok=="*") st.push(a*b);
                else if (tok=="/") st.push(a/b);
            }
        }
        return st.top();
    }

    // ================================
    // Largest Rectangle in Histogram
    // ================================
    inline int largest_rectangle_histogram(const std::vector<int> &heights) {
        std::stack<int> st; // store indices
        int maxArea = 0;
        int n = heights.size();
        for (int i=0; i<=n; ++i) {
            int h = (i==n ? 0 : heights[i]);
            while (!st.empty() && h < heights[st.top()]) {
                int height = heights[st.top()]; st.pop();
                int width = st.empty() ? i : i - st.top() - 1;
                maxArea = std::max(maxArea, height*width);
            }
            st.push(i);
        }
        return maxArea;
    }

    // ================================
    // Monotonic Stack Utility
    // ================================
    template<typename T, typename Compare>
    std::vector<int> monotonic_stack_indices(const std::vector<T> &arr, Compare cmp) {
        std::vector<int> res(arr.size(), -1);
        std::stack<int> st;
        for (int i=0; i<(int)arr.size(); ++i) {
            while (!st.empty() && cmp(arr[i], arr[st.top()])) {
                res[st.top()] = i;
                st.pop();
            }
            st.push(i);
        }
        return res;
    }

    // ================================
    // Infix → Postfix conversion
    // (Shunting Yard algorithm)
    // ================================
    inline int precedence(char op) {
        if (op=='+'||op=='-') return 1;
        if (op=='*'||op=='/') return 2;
        if (op=='^') return 3;
        return 0;
    }
    inline bool is_left_assoc(char op) {
        return op != '^'; // ^ is right-associative
    }

    inline std::string infix_to_postfix(const std::string &expr) {
        std::stack<char> st;
        std::ostringstream out;
        for (size_t i=0; i<expr.size(); ++i) {
            char c = expr[i];
            if (isspace(c)) continue;
            if (isalnum(c)) {
                out << c << ' ';
            } else if (c=='(') {
                st.push(c);
            } else if (c==')') {
                while (!st.empty() && st.top()!='(') {
                    out << st.top() << ' ';
                    st.pop();
                }
                if (!st.empty() && st.top()=='(') st.pop();
            } else { // operator
                while (!st.empty() && precedence(st.top()) >= precedence(c) &&
                       (is_left_assoc(c) || precedence(st.top()) > precedence(c))) {
                    out << st.top() << ' ';
                    st.pop();
                }
                st.push(c);
            }
        }
        while (!st.empty()) {
            out << st.top() << ' ';
            st.pop();
        }
        return out.str();
    }

} // namespace stackalgo

#endif // STACK_ALGORITHMS_H
