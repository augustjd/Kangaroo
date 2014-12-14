#include "Formatting.hpp"

ostream& operator<<(ostream& out, const sf::Color& obj) {
    return out << BOLD_BLUE("Color")"("
        << BOLD_GREEN("r")"=" << (int)obj.r << ", "
        << BOLD_GREEN("g")"=" << (int)obj.g << ", "
        << BOLD_GREEN("b")"=" << (int)obj.b << ")";
}

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& obj) {
    out << '[';

    bool first = false;
    for (auto& it : obj) {
        if (!first) {
            out << ", ";
        }
        out << it;
        first = false;
    }

    return out << ']';
}


template <typename T>
ostream& operator<<(ostream& out, const vector<unique_ptr<T>>& obj) {
    out << '[';

    bool first = false;
    for (auto& it : obj) {
        if (!first) {
            out << ", ";
        }
        out << *it.get();
        first = false;
    }

    return out << ']';
}

string vector_to_str(const Vector3d& obj) {
  char buffer[64];
  sprintf(buffer, "<%.2f, %.2f, %.2f>", obj[0], obj[1], obj[2]);
  return buffer;
}

string vector_to_str(const Vector2d& obj) {
  char buffer[64];
  sprintf(buffer, "<%.2f, %.2f>", obj[0], obj[1]);
  return buffer;
}
