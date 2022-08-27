#include "postfix.h"
#include <stack>
#include <iostream>

Postfix::Postfix(const std::string &s)
        : Expression(s) {
    toPostfix();
}

int Postfix::calculate(std::unordered_map<std::string, int> &mp) const {
    std::stack<int> st;
    for (const auto &smb: m_postfix) {
        if (smb.isNumber()) {
            st.push(smb.asNumber());
        } else if (smb.isIdentifier()) {
            st.push(mp[smb.asIdentifier()]);
        } else {
            int y = st.top(); st.pop();
            int x = st.top(); st.pop();
            st.push(smb.asOperator().calculateOption(x, y));
        }
    }
    return st.top();
}

void Postfix::toPostfix() {
    std::stack<int> index;
    size_t sz = m_infix.size();
    for (int i = 0; i < sz; ++i) {
        Symbol &s = m_infix[i];
        if (s.isNumber() || s.isIdentifier()) {
            m_postfix.push_back(s);
        } else if (s.isOpenBracket()) {
            index.push(i);
        } else if (s.isCloseBracket()) {
            while (!m_infix[index.top()].isOpenBracket()) {
                m_postfix.push_back(m_infix[index.top()]);
                index.pop();
            }
            index.pop();
        } else if (s.isOperation()) {
            Operation op = s.asOperator();
            while(!index.empty()) {
                Symbol& smb = m_infix[index.top()];
                if(!smb.isOperation() || smb.asOperator().priority() < op.priority()) break;
                m_postfix.push_back(smb);
                index.pop();
            }
            index.push(i);
        }
    }
    while (!index.empty()) {
        m_postfix.push_back(m_infix[index.top()]);
        index.pop();
    }
}

std::ostream &operator<<(std::ostream &out, const Postfix &obj) {
    for (const auto& smb: obj.m_postfix) {
        if (smb.isIdentifier()) {
            out << smb.asIdentifier();
        } else if(smb.isNumber()) {
            out << smb.asNumber();
        } else {
            out << smb.asOperator();
        }
        out << ' ';
    }
    out << std::endl;
    return out;
}